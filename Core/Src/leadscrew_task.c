/**
 * @file leadscrew_task.c
 * @brief FreeRTOS task for leadscrew motor control
 */

#include "leadscrew_task.h"
#include "sequencer.h"
#include "motor_hal.h"
#include "motion_profile.h"




/* RTOS objects */
TaskHandle_t LeadscrewTaskHandle = NULL;

/* Internal state */
static motion_profile_t activeProfile;
static uint32_t currentDelayUs;

static uint8_t motionActive = 0;
static uint8_t stopRequested = 0;

static motor_dir_t currentDirection = MOTOR_DIR_FORWARD;


/* Control flags */
static volatile uint8_t leadscrewRunRequested = 0;
static volatile uint8_t leadscrewStopRequested = 0;
static volatile uint8_t leadscrewReverseRequested = 0;

void LeadscrewTask(void *argument)
{
    TickType_t lastWakeTime;

    for (;;)
    {
        /* Wait for start command */
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        /* Apply direction */
        MotorHAL_Start(MOTOR_LEADSCREW, currentDirection);

        lastWakeTime = xTaskGetTickCount();

        while (motionActive)
        {
            /* Generate step pulse */
            MotorHAL_GeneratePulse(MOTOR_LEADSCREW);

            /* Acceleration */
            if (!stopRequested &&
                currentDelayUs > activeProfile.min_delay_us)
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

        MotorHAL_Stop(MOTOR_LEADSCREW);

        /* Signal completion */
        xEventGroupSetBits(SystemEventGroup, EVT_LEADSCREW_DONE);
    }
}


/* API used by other tasks */

void Leadscrew_RequestStart(motor_dir_t dir,
                            const motion_profile_t *profile)
{
    currentDirection = dir;
    activeProfile = *profile;
    currentDelayUs = activeProfile.start_delay_us;

    motionActive = 1;
    stopRequested = 0;

    xTaskNotifyGive(LeadscrewTaskHandle);
}

void Leadscrew_RequestStop(void)
{
    stopRequested = 1;
}

void Leadscrew_ReverseDirection(void)
{
    leadscrewReverseRequested = 1;
    xTaskNotifyGive(LeadscrewTaskHandle);
}

if (leadscrewReverseRequested)
{
    /* TODO: Reverse motor direction */
    leadscrewReverseRequested = 0;
    currentState = LEADSCREW_DIRECTION_CHANGE;

    xEventGroupSetBits(SystemEventGroup, EVT_LEADSCREW_DONE);
}

if (leadscrewRunRequested)
{
    /* TODO: Start leadscrew motion */
    leadscrewRunRequested = 0;

    xEventGroupSetBits(SystemEventGroup, EVT_LEADSCREW_DONE);
}

