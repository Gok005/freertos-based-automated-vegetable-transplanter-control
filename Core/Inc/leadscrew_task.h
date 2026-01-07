#ifndef LEADSCREW_TASK_H
#define LEADSCREW_TASK_H

/**
 * @file leadscrew_task.h
 * @brief FreeRTOS task for leadscrew motor control
 *
 * Controls linear motion of the leadscrew and supports
 * direction reversal based on transplant cycles.
 */

#include "FreeRTOS.h"
#include "task.h"
#include "system_state.h"

/* Leadscrew task handle */
extern TaskHandle_t LeadscrewTaskHandle;

/* Leadscrew task entry function */
void LeadscrewTask(void *argument);

/* Control interface */
void Leadscrew_RequestStart(void);
void Leadscrew_RequestStop(void);
void Leadscrew_ReverseDirection(void);

#endif /* LEADSCREW_TASK_H */
