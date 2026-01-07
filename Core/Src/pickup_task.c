/**
 * @file pickup_task.c
 * @brief FreeRTOS task for pickup arm control
 */

#include "pickup_task.h"

/* RTOS objects */
TaskHandle_t PickupTaskHandle = NULL;

/* Internal state */
static system_state_t currentState = SYSTEM_INIT;

/* Motion requests */
static volatile uint8_t pickupForwardRequested  = 0;
static volatile uint8_t pickupBackwardRequested = 0;

void PickupTask(void *argument)
{
    for (;;)
    {
        /* Block until a motion request is received */
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        if (pickupForwardRequested)
        {
            /* TODO: Drive pickup arm forward */
            pickupForwardRequested = 0;
            currentState = PICKUP_FORWARD;
        }

        if (pickupBackwardRequested)
        {
            /* TODO: Drive pickup arm backward */
            pickupBackwardRequested = 0;
            currentState = PICKUP_RETRACT;
        }
    }
}

/* API used by other tasks */

void Pickup_RequestForward(void)
{
    pickupForwardRequested = 1;
    xTaskNotifyGive(PickupTaskHandle);
}

void Pickup_RequestBackward(void)
{
    pickupBackwardRequested = 1;
    xTaskNotifyGive(PickupTaskHandle);
}
