#ifndef PICKUP_TASK_H
#define PICKUP_TASK_H

/**
 * @file pickup_task.h
 * @brief FreeRTOS task for pickup arm motion control
 *
 * Controls forward and backward motion of the pickup arm
 * and synchronizes with servo and leadscrew tasks.
 */

#include "FreeRTOS.h"
#include "task.h"
#include "system_state.h"
#include "motion_profile.h"

/* Pickup task handle */
extern TaskHandle_t PickupTaskHandle;

/* Pickup task entry function */
void PickupTask(void *argument);

/* Control interface */
#include "motion_profile.h"

/* Motion commands */
void Pickup_RequestForward(const motion_profile_t *profile);
void Pickup_RequestBackward(const motion_profile_t *profile);
void Pickup_RequestStop(void);


#endif /* PICKUP_TASK_H */
