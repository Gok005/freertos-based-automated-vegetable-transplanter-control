/**
 * @file sequencer.c
 * @brief Central transplant sequencing logic
 */

#include "sequencer.h"
#include "servo_task.h"
#include "pickup_task.h"
#include "leadscrew_task.h"
#include "conveyor_task.h"
#include "task_config.h"

/* RTOS objects */
TaskHandle_t SequencerTaskHandle = NULL;
EventGroupHandle_t SystemEventGroup = NULL;

Pickup_RequestForward(&pickupProfile);


motion_profile_t pickupProfile = {
    .start_delay_us = 2000,
    .min_delay_us   = 500,
    .accel_step_us  = 50
};


void SequencerTask(void *argument)
{
    uint8_t cycleCount = 0;

    /* Create event group */
    SystemEventGroup = xEventGroupCreate();

    for (;;)
    {
        /* ---- Planting phase ---- */

        /* 1. Close servo */
        Servo_RequestClose();
        xEventGroupWaitBits(SystemEventGroup,
                            EVT_SERVO_DONE,
                            pdTRUE,
                            pdTRUE,
                            portMAX_DELAY);

        /* 2. Pickup forward + leadscrew start */
        Pickup_RequestForward();
        Leadscrew_RequestStart();

        xEventGroupWaitBits(SystemEventGroup,
                            EVT_PICKUP_DONE | EVT_LEADSCREW_DONE,
                            pdTRUE,
                            pdTRUE,
                            portMAX_DELAY);

        /* 3. Open servo */
        Servo_RequestOpen();
        xEventGroupWaitBits(SystemEventGroup,
                            EVT_SERVO_DONE,
                            pdTRUE,
                            pdTRUE,
                            portMAX_DELAY);

        /* 4. Pickup retract (leadscrew idle) */
        Pickup_RequestBackward();
        xEventGroupWaitBits(SystemEventGroup,
                            EVT_PICKUP_DONE,
                            pdTRUE,
                            pdTRUE,
                            portMAX_DELAY);

        cycleCount++;

        /* ---- Batch handling ---- */
        if (cycleCount >= TRANSPLANT_CYCLE_COUNT)
        {
            Conveyor_RequestMove();
            xEventGroupWaitBits(SystemEventGroup,
                                EVT_CONVEYOR_DONE,
                                pdTRUE,
                                pdTRUE,
                                portMAX_DELAY);

            Leadscrew_ReverseDirection();
            cycleCount = 0;
        }
    }
}
