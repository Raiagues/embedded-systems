#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define FIRST_TASK_PRIORITY 1
#define SECOND_TASK_PRIORITY 2
#define THIRD_TASK_PRIORITY 3

void firstTask(void *pvParameter);
void secondTask(void *pvParameter);
void thirdTask(void *pvParameter);

typedef struct {
  int id;
  const char *name;
} ThirdTaskParams;

static ThirdTaskParams thirdTaskParams = {
  .id = 1,
  .name = "thirdTask"
};

void app_main(void)
{
  xTaskCreate(
    firstTask,              // Task function
    "firstTask",            // Task name (for debbuging)
    2048,                   // Stack size in words (1 word = 4 bytes)
    NULL,                   // Parameters to the task
    FIRST_TASK_PRIORITY,    // Task priority
    NULL                    // Task handle
  );

  xTaskCreate(
    secondTask,             // Task function
    "secondTask",           // Task name (for debbuging)
    2048,                   // Stack size in words (1 word = 4 bytes)
    (void *)"secondTask",   // Parameters to the task
    SECOND_TASK_PRIORITY,   // Task priority
    NULL                    // Task handle
  );

  xTaskCreate(
    thirdTask,              // Task function
    "thirdTask",            // Task name (for debbuging)
    2048,                   // Stack size in words (1 word = 4 bytes)
    &thirdTaskParams,       // Parameters to the task
    THIRD_TASK_PRIORITY,    // Task priority
    NULL                    // Task handle
  );
}

void firstTask(void *pvParameter)
{
  while (1)
  {
    printf("Running first task\n");

    /* Delay of 1000ms = 1s*/
    vTaskDelay(pdMS_TO_TICKS(1000)); 
  }
}

void secondTask(void *pvParameter)
{
  /* Cast the void* to a char */
  const char *taskName = (const char *)pvParameter;

  while (1)
  {
    printf("Running %s\n", taskName);

    /* Delay of 1500ms = 1,5s*/
    vTaskDelay(pdMS_TO_TICKS(1500));
  }
}

void thirdTask(void *pvParameter)
{
  /* Cast the void* to a struct */
  ThirdTaskParams *params = (ThirdTaskParams *) pvParameter;
  
  while (1)
  {
    printf("Running %s\n", params->name);

    /* Delay of 2000ms= 2s*/
    vTaskDelay(pdMS_TO_TICKS(2000));
  }
  
}
