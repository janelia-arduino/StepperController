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
extern const double steps_per_position_units_default[step_dir_controller::constants::CHANNEL_COUNT];

extern const long current_scale_default[DRIVER_COUNT];

extern const long microsteps_per_step_default[DRIVER_COUNT];

// Parameters

// Functions

// Callbacks

// Errors
}
}

#endif
#endif
