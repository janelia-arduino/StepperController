// ----------------------------------------------------------------------------
// 3x2.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef STEPPER_CONTROLLER_3X2_CONSTANTS_H
#define STEPPER_CONTROLLER_3X2_CONSTANTS_H
#include "Constants.h"


#if defined(__MK20DX256__)

namespace stepper_controller
{
namespace constants
{
//MAX values must be >= 1, >= created/copied count, < RAM limit
enum{INTERRUPT_COUNT_MAX=1};

enum{CHANNEL_COUNT_MAX=1};

extern const size_t cs_pins[CHANNEL_COUNT_MAX];

// Interrupts

// Units

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]
extern const long steps_per_position_units_default[CHANNEL_COUNT_MAX];

extern const long velocity_max_default[CHANNEL_COUNT_MAX];

extern const long velocity_min_default[CHANNEL_COUNT_MAX];

extern const long acceleration_max_default[CHANNEL_COUNT_MAX];

extern const ConstantString * const enable_polarity_default[CHANNEL_COUNT_MAX];

extern const bool left_switch_stop_enabled_default[CHANNEL_COUNT_MAX];

extern const bool right_switch_stop_enabled_default[CHANNEL_COUNT_MAX];

extern const bool switch_soft_stop_enabled_default[CHANNEL_COUNT_MAX];

extern const long home_velocity_default[CHANNEL_COUNT_MAX];

extern const bool invert_driver_direction_default[CHANNEL_COUNT_MAX];

extern const long run_current_default[CHANNEL_COUNT_MAX];

extern const long hold_current_default[CHANNEL_COUNT_MAX];

extern const long hold_delay_default[CHANNEL_COUNT_MAX];

extern const long microsteps_per_step_default[CHANNEL_COUNT_MAX];

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
#endif
