// ----------------------------------------------------------------------------
// 5x3.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "5x3.h"


#if defined(__MK64FX512__)

namespace stepper_controller
{
namespace constants
{
const size_t cs_pins[DRIVER_COUNT] =
  {
    14,
    15,
    16,
  };

// Interrupts

// Units

// Properties
const double steps_per_position_units_default[step_dir_controller::constants::CHANNEL_COUNT] =
  {
    steps_per_position_units_element_default,
    steps_per_position_units_element_default,
    steps_per_position_units_element_default,
  };

const long current_scale_default[DRIVER_COUNT] =
  {
    20,
    20,
    20
  };

const long microsteps_per_step_default[DRIVER_COUNT] =
  {
    microsteps_per_step_subset[MICROSTEPS_PER_STEP_SUBSET_LENGTH - 1].l,
    microsteps_per_step_subset[MICROSTEPS_PER_STEP_SUBSET_LENGTH - 1].l,
    microsteps_per_step_subset[MICROSTEPS_PER_STEP_SUBSET_LENGTH - 1].l,
  };

// Parameters

// Functions

// Callbacks

// Errors
}
}

#endif
