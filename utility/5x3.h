// ----------------------------------------------------------------------------
// 5x3.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef STEPPER_CONTROLLER_5X3_CONSTANTS_H
#define STEPPER_CONTROLLER_5X3_CONSTANTS_H
#include "Constants.h"


#if defined(__MK64FX512__)

namespace stepper_controller
{
namespace constants
{
enum{DRIVER_COUNT=3};

extern const size_t cs_pins[DRIVER_COUNT];

// Interrupts

// Units

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]
extern const long steps_per_position_units_default[DRIVER_COUNT];

extern const long velocity_max_default[DRIVER_COUNT];

extern const long velocity_min_default[DRIVER_COUNT];

extern const long acceleration_max_default[DRIVER_COUNT];

extern const ConstantString * const enable_polarity_default[DRIVER_COUNT];

extern const bool left_switch_stop_enabled_default[DRIVER_COUNT];

extern const bool right_switch_stop_enabled_default[DRIVER_COUNT];

extern const bool switch_soft_stop_enabled_default[DRIVER_COUNT];

extern const long home_velocity_default[DRIVER_COUNT];

extern const bool invert_driver_direction_default[DRIVER_COUNT];

extern const long run_current_default[DRIVER_COUNT];

extern const long hold_current_default[DRIVER_COUNT];

extern const long hold_delay_default[DRIVER_COUNT];

extern const long microsteps_per_step_default[DRIVER_COUNT];

// Parameters

// Functions

// Callbacks

// Errors
}
}

#endif
#endif
