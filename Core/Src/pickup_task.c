/**
 * @file pickup_task.c
 * @brief FreeRTOS task for pickup arm control
 */

#include "motor_hal.h"
#include "motion_profile.h"
#include "sequencer.h"



/* RTOS objects */
TaskHandle_t PickupTaskHandle = NULL;

/* Internal state */
static system_state_t currentState = SYSTEM_INIT;

/* Motion requests */
static volatile uint8_t pickupForwardRequested  = 0;
static volatile uint8_t pickupBackwardRequested = 0;

void PickupTask(void *argument)
{
    TickType_t lastWakeTime;

    for (;;)
    {
        /* Wait for motion command */
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        lastWakeTime = xTaskGetTickCount();

        while (motionActive)
        {
            /* Generate one step pulse */
            MotorHAL_GeneratePulse(MOTOR_PICKUP);

            /* Acceleration */
            if (!stopRequested && currentDelayUs > activeProfile.min_delay_us)
            {
                currentDelayUs -= activeProfile.accel_step_us;
            }

            /* Deceleration */
            if (stopRequested)
            {
                currentDelayUs += activeProfile.accel_step_us;
                if (currentDelayUs >= activeProfile.start_delay_us)
                {
                    motionActive = 0;
                }
            }

            vTaskDelayUntil(&lastWakeTime,
                             pdUS_TO_TICKS(currentDelayUs));
        }

        /* Motion complete */
        xEventGroupSetBits(SystemEventGroup, EVT_PICKUP_DONE);
    }
}


/* API used by other tasks */

void Pickup_RequestForward(const motion_profile_t *profile)
{
    activeProfile = *profile;
    currentDelayUs = activeProfile.start_delay_us;
    motionActive = 1;
    stopRequested = 0;

    xTaskNotifyGive(PickupTaskHandle);
}

void Pickup_RequestBackward(const motion_profile_t *profile)
{
    activeProfile = *profile;
    currentDelayUs = activeProfile.start_delay_us;
    motionActive = 1;
    stopRequested = 0;

    xTaskNotifyGive(PickupTaskHandle);
}

void Pickup_RequestStop(void)
{
    stopRequested = 1;
}


if (pickupForwardRequested)
{
    /* TODO: Drive pickup arm forward */
    pickupForwardRequested = 0;
    currentState = PICKUP_FORWARD;

    xEventGroupSetBits(SystemEventGroup, EVT_PICKUP_DONE);
}

if (pickupBackwardRequested)
{
    /* TODO: Drive pickup arm backward */
    pickupBackwardRequested = 0;
    currentState = PICKUP_RETRACT;

    xEventGroupSetBits(SystemEventGroup, EVT_PICKUP_DONE);
}
