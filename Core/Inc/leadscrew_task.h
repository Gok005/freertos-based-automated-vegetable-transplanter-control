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
#include "motion_profile.h"

/* Leadscrew task handle */
extern TaskHandle_t LeadscrewTaskHandle;

/* Leadscrew task entry function */
void LeadscrewTask(void *argument);


/* Motion commands */
void Leadscrew_RequestStart(motor_dir_t dir,
                            const motion_profile_t *profile);
void Leadscrew_RequestStop(void);

#endif /* LEADSCREW_TASK_H */
