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

/* Pickup task handle */
extern TaskHandle_t PickupTaskHandle;

/* Pickup task entry function */
void PickupTask(void *argument);

/* Control interface */
void Pickup_RequestForward(void);
void Pickup_RequestBackward(void);

#endif /* PICKUP_TASK_H */
