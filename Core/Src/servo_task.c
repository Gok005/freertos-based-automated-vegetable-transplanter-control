/**
 * @file servo_task.c
 * @brief FreeRTOS task for servo-based gripper control
 */

#include "servo_task.h"

/* RTOS objects */
TaskHandle_t ServoTaskHandle = NULL;

/* Internal state */
static system_state_t currentState = SYSTEM_INIT;

/* Servo command flags */
static volatile uint8_t servoCloseRequested = 0;
static volatile uint8_t servoOpenRequested  = 0;

void ServoTask(void *argument)
{
    for (;;)
    {
        /* Block until a command is received */
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        if (servoCloseRequested)
        {
            /* TODO: Drive servo to CLOSE position */
            servoCloseRequested = 0;
            currentState = SERVO_CLOSE;
        }

        if (servoOpenRequested)
        {
            /* TODO: Drive servo to OPEN position */
            servoOpenRequested = 0;
            currentState = SERVO_OPEN;
        }
    }
}

/* API used by other tasks to request servo actions */

void Servo_RequestClose(void)
{
    servoCloseRequested = 1;
    xTaskNotifyGive(ServoTaskHandle);
}

void Servo_RequestOpen(void)
{
    servoOpenRequested = 1;
    xTaskNotifyGive(ServoTaskHandle);
}

