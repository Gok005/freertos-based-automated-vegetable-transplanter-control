#ifndef MOTION_PROFILE_H
#define MOTION_PROFILE_H

#include <stdint.h>

typedef struct
{
    uint32_t start_delay_us;   // slow start
    uint32_t min_delay_us;     // max speed
    uint32_t accel_step_us;    // acceleration rate
} motion_profile_t;

#endif
