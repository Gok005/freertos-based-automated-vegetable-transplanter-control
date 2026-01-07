#ifndef CONVEYOR_TASK_H
#define CONVEYOR_TASK_H

/**
 * @file conveyor_task.h
 * @brief FreeRTOS task for conveyor motion control
 *
 * Advances the sapling tray after completion of a transplant batch.
 */

#include "FreeRTOS.h"
#include "task.h"
#include "system_state.h"

/* Conveyor task handle */
extern TaskHandle_t ConveyorTaskHandle;

/* Conveyor task entry function */
void ConveyorTask(void *argument);

/* Control interface */
void Conveyor_RequestMove(void);

#endif /* CONVEYOR_TASK_H */
