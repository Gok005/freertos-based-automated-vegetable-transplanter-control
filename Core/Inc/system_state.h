#ifndef SYSTEM_STATE_H
#define SYSTEM_STATE_H

/**
 * @file system_state.h
 * @brief System-wide state definitions for automated vegetable transplanter
 *
 * Defines the operational states and fault conditions used by all FreeRTOS tasks
 * to coordinate deterministic motor sequencing.
 */

/* Main operational states */
typedef enum
{
    SYSTEM_INIT = 0,
    SYSTEM_IDLE,

    SERVO_CLOSE,
    PICKUP_FORWARD,
    SERVO_OPEN,
    PICKUP_RETRACT,

    CONVEYOR_MOVE,
    LEADSCREW_DIRECTION_CHANGE,

    SYSTEM_ERROR,
    SYSTEM_EMERGENCY_STOP

} system_state_t;

/* Fault codes for diagnostics and safe handling */
typedef enum
{
    FAULT_NONE = 0,
    FAULT_TIMEOUT,
    FAULT_LIMIT_SWITCH,
    FAULT_MOTOR_STALL,
    FAULT_EMERGENCY_STOP

} fault_code_t;

#endif /* SYSTEM_STATE_H */

