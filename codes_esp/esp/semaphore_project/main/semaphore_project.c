#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#define PRODUCER_DELAY    1000  // Time between the producer events
#define CONSUMER_DELAY    4000  // Time between the consumer events
#define MAX_EVENT_NUMBER  5     // Maximum number of events 
#define INIT_EVENT_NUMBER 0     // Initialize the number as 0

#define PRODUCER_TASK_PRIORITY 1
#define CONSUMER_TASK_PRIORITY 1

SemaphoreHandle_t semaphoreNumber;

void producerTask(void *pvParameters);
void consumerTask(void *pvParameters);

void app_main(void)
{
  semaphoreNumber = xSemaphoreCreateCounting(MAX_EVENT_NUMBER, INIT_EVENT_NUMBER);

  xTaskCreate(
    producerTask,             // Task function
    "producerTask",           // Task name (for debbuging)
    2048,                     // Stack size in words (1 word = 4 bytes)
    NULL,                     // Parameters to the task
    PRODUCER_TASK_PRIORITY,   // Task priority
    NULL                      // Task handle
  );

  xTaskCreate(
    consumerTask,             // Task function
    "consumerTask",           // Task name (for debbuging)
    2048,                     // Stack size in words (1 word = 4 bytes)
    NULL,                     // Parameters to the task
    CONSUMER_TASK_PRIORITY,   // Task priority
    NULL                      // Task handle
  );
}

void producerTask(void *pvParameters)
{
  static int eventCounter = 0;

  while (1)
  {
    /* If the number of events has not yet been reached */
    if(xSemaphoreGive(semaphoreNumber))
    {
      eventCounter++;
      printf("Event %d produced\n", eventCounter);
    }
    else
    {
      printf("Semaphore full\n");
    }
    vTaskDelay(pdMS_TO_TICKS(PRODUCER_DELAY));
  }
}

void consumerTask(void *pvParameters)
{
  static int consumed = 0;
  while (1)
  {
    if(xSemaphoreTake(semaphoreNumber, portMAX_DELAY))
    {
      consumed++;
      printf("Event %d consumed\n", consumed);
      vTaskDelay(pdMS_TO_TICKS(CONSUMER_DELAY));
    }
  }
}
