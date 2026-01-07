/**
 * @file conveyor_task.c
 * @brief FreeRTOS task for conveyor control
 */

#include "conveyor_task.h"

/* RTOS objects */
TaskHandle_t ConveyorTaskHandle = NULL;

/* Internal state */
static system_state_t currentState = SYSTEM_INIT;

/* Control flag */
static volatile uint8_t conveyorMoveRequested = 0;

void ConveyorTask(void *argument)
{
    for (;;)
    {
        /* Block until a move request is received */
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        if (conveyorMoveRequested)
        {
            /* TODO: Drive conveyor motor */
            conveyorMoveRequested = 0;
            currentState = CONVEYOR_MOVE;
        }
    }
}

/* API used by sequencing logic */

void Conveyor_RequestMove(void)
{
    conveyorMoveRequested = 1;
    xTaskNotifyGive(ConveyorTaskHandle);
}
