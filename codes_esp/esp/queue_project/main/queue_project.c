#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

#define SENDER_TASK_PRIORITY 1
#define RECEIVER_TASK_PRIORITY 1

void senderTask(void *pvParameter);
void receiverTask(void *pvParameter);

QueueHandle_t queue;

void app_main(void)
{
  queue = xQueueCreate(
    10,                       // Maximum number of items that queue can contain
    sizeof(int)               // Number of byte of each item
  );

  xTaskCreate(
    senderTask,               // Task function
    "senderTask",             // Task name (for debbuging)
    2048,                     // Stack size in words (1 word = 4 bytes)
    NULL,                     // Parameters to the task
    SENDER_TASK_PRIORITY,     // Task priority
    NULL                      // Task handle
  );

  xTaskCreate(
    receiverTask,             // Task function
    "receiverTask",           // Task name (for debbuging)
    2048,                     // Stack size in words (1 word = 4 bytes)
    NULL,                     // Parameters to the task
    RECEIVER_TASK_PRIORITY,   // Task priority
    NULL                      // Task handle
  );
}

void senderTask(void *pvParameter)
{
  int sentValue = 0;
  while (1)
  {
    xQueueSend(
      queue,                  // Queue on which the item is to be posted
      &sentValue,             // Item to be placed on the queue
      portMAX_DELAY           // Maximum amount of time the task whould waiting
    );
    
    sentValue++;
    
    vTaskDelay(pdMS_TO_TICKS(500)); 
  }
}

void receiverTask(void *pvParameter)
{
  int receivedValue;
  while (1)
  {
    if(xQueueReceive(queue, &receivedValue, portMAX_DELAY))
    {
      printf("Received : %d\n", receivedValue);
    }
  } 
}