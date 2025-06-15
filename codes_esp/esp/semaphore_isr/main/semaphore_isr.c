#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#define BUTTON_TASK_PRIORITY 1
#define ISR_DELAY 2000
#define BUTTON_GPIO GPIO_NUM_27
#define LED_GPIO GPIO_NUM_26

#define ISR_FLAG 0

SemaphoreHandle_t buttonState;

void taskButton(void *pvParameters);
void taskWaitingClick(void *pvParameters);

void app_main(void)
{
  buttonState = xSemaphoreCreateBinary();

  /* Initializing GPIO26 as input with a pull up to detects button press (GPIO_INTR_NEGEDGE)*/
  gpio_config_t buttonConfig = {
    .pin_bit_mask = (1ULL << BUTTON_GPIO),
    .mode = GPIO_MODE_INPUT,
    .pull_up_en = GPIO_PULLUP_ENABLE,
    .pull_down_en = GPIO_PULLDOWN_DISABLE,
    .intr_type = GPIO_INTR_NEGEDGE
  };
  gpio_config(&buttonConfig);

  gpio_config_t ledConfig = {
    .pin_bit_mask = (1ULL << LED_GPIO),
    .mode = GPIO_MODE_OUTPUT,
    .pull_up_en = GPIO_PULLUP_DISABLE,
    .pull_down_en = GPIO_PULLDOWN_DISABLE,
    .intr_type = GPIO_INTR_DISABLE
  };
  gpio_config(&ledConfig);

  /* Install the interruption GPIO driver*/
  gpio_install_isr_service(ISR_FLAG);
  /* Function is automatically called when the electrical transition configured in the pin's intr_type occurs */
  gpio_isr_handler_add(BUTTON_GPIO, taskButton, NULL);

  xTaskCreate(
    taskWaitingClick,         // Task function
    "taskWaitingClick",       // Task name (for debbuging)
    2048,                     // Stack size in words (1 word = 4 bytes)
    NULL,                     // Parameters to the task
    BUTTON_TASK_PRIORITY,     // Task priority
    NULL                      // Task handle
  );
}

/* IRAM is a attribute to indicate that a funcion should be placed in internal RAM */
void IRAM_ATTR taskButton(void *pvParameters)
{
  /* Indicates if the task that was waiting for the semaphore has a higher priority than the current task */
  BaseType_t xHigherPriorityTaskWoken = pdFALSE; 

  xSemaphoreGiveFromISR(buttonState, &xHigherPriorityTaskWoken);
  if(xHigherPriorityTaskWoken)
  {
    /* If the task that received the semaphore has higher priority, forces a context switch */
    portYIELD_FROM_ISR();
  }
}

void taskWaitingClick(void *pvParameters)
{
  while (1)
  {
    if(xSemaphoreTake(buttonState, portMAX_DELAY))
    {
      printf("Button clicked\n");

      gpio_set_level(LED_GPIO, 1);
      vTaskDelay(pdMS_TO_TICKS(500));
      gpio_set_level(LED_GPIO, 0);
    }
  }  
}