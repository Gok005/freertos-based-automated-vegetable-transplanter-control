#ifndef TASK_CONFIG_H
#define TASK_CONFIG_H

/**
 * @file task_config.h
 * @brief FreeRTOS task configuration for automated vegetable transplanter
 *
 * Defines task priorities, stack sizes, and core timing intent.
 * These values are chosen based on motor criticality and sequencing constraints.
 */

#include "FreeRTOS.h"

/* Task priorities (higher number = higher priority) */
#define SERVO_TASK_PRIORITY        ( tskIDLE_PRIORITY + 3 )
#define PICKUP_TASK_PRIORITY       ( tskIDLE_PRIORITY + 2 )
#define LEADSCREW_TASK_PRIORITY    ( tskIDLE_PRIORITY + 2 )
#define CONVEYOR_TASK_PRIORITY     ( tskIDLE_PRIORITY + 1 )

/* Stack sizes (words, not bytes) */
#define SERVO_TASK_STACK_SIZE      ( 256 )
#define PICKUP_TASK_STACK_SIZE     ( 256 )
#define LEADSCREW_TASK_STACK_SIZE  ( 256 )
#define CONVEYOR_TASK_STACK_SIZE   ( 192 )

/* System-level timing parameters */
#define TRANSPLANT_CYCLE_COUNT     ( 7 )

#endif /* TASK_CONFIG_H */
