#ifndef SEQUENCER_H
#define SEQUENCER_H

/**
 * @file sequencer.h
 * @brief Central sequencing controller for transplant operation
 *
 * Coordinates all actuator tasks using FreeRTOS Event Groups
 * and enforces deterministic transplant sequencing.
 */

#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"
#include "system_state.h"

/* Sequencer task handle */
extern TaskHandle_t SequencerTaskHandle;

/* Event group handle */
extern EventGroupHandle_t SystemEventGroup;

/* Sequencer task entry */
void SequencerTask(void *argument);

#endif /* SEQUENCER_H */
