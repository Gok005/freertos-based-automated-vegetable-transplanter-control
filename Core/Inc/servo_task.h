#ifndef SERVO_TASK_H
#define SERVO_TASK_H

/**
 * @file servo_task.h
 * @brief FreeRTOS task for servo-based gripper control
 *
 * Handles gripper open/close actions based on system state
 * and synchronization events from other tasks.
 */

#include "FreeRTOS.h"
#include "task.h"
#include "system_state.h"

/* Servo task handle */
extern TaskHandle_t ServoTaskHandle;

/* Servo task entry function */
void ServoTask(void *argument);

/* Servo control interface */
void Servo_RequestClose(void);
void Servo_RequestOpen(void);

#endif /* SERVO_TASK_H */
