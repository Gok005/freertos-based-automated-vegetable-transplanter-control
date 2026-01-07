/**
 * @file main.c
 * @brief System entry point for FreeRTOS-based automated vegetable transplanter
 *
 * Responsible only for:
 *  - Hardware init (later)
 *  - RTOS object creation
 *  - Task creation
 *  - Scheduler start
 */

#include "FreeRTOS.h"
#include "task.h"

/* Task headers */
#include "servo_task.h"
#include "pickup_task.h"
#include "leadscrew_task.h"
#include "conveyor_task.h"
#include "sequencer.h"
#include "task_config.h"

int main(void)
{
    /* TODO: Hardware initialization (GPIO, PWM, Timers) */

    /* Create actuator tasks */

    xTaskCreate(ServoTask,
                "ServoTask",
                SERVO_TASK_STACK_SIZE,
                NULL,
                SERVO_TASK_PRIORITY,
                &ServoTaskHandle);

    xTaskCreate(PickupTask,
                "PickupTask",
                PICKUP_TASK_STACK_SIZE,
                NULL,
                PICKUP_TASK_PRIORITY,
                &PickupTaskHandle);

    xTaskCreate(LeadscrewTask,
                "LeadscrewTask",
                LEADSCREW_TASK_STACK_SIZE,
                NULL,
                LEADSCREW_TASK_PRIORITY,
                &LeadscrewTaskHandle);

    xTaskCreate(ConveyorTask,
                "ConveyorTask",
                CONVEYOR_TASK_STACK_SIZE,
                NULL,
                CONVEYOR_TASK_PRIORITY,
                &ConveyorTaskHandle);

    /* Create sequencer task (system brain) */

    xTaskCreate(SequencerTask,
                "SequencerTask",
                384,
                NULL,
                tskIDLE_PRIORITY + 4,
                &SequencerTaskHandle);

    /* Start scheduler */
    vTaskStartScheduler();

    /* Should never reach here */
    for (;;)
    {
    }
}
