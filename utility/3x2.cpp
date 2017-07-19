// ----------------------------------------------------------------------------
// 3x2.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "3x2.h"


#if defined(__MK20DX256__)

namespace stepper_controller
{
namespace constants
{
const size_t cs_pins[DRIVER_COUNT] =
  {
    14,
  };

// Interrupts

// Units

// Properties
const double steps_per_position_units_default[DRIVER_COUNT] =
  {
    steps_per_position_units_element_default,
  };

const double velocity_max_default[DRIVER_COUNT] =
  {
    step_dir_controller::constants::velocity_max_element_default,
  };

const double velocity_min_default[DRIVER_COUNT] =
  {
    step_dir_controller::constants::velocity_min_element_default,
  };

const double acceleration_max_default[DRIVER_COUNT] =
  {
    step_dir_controller::constants::acceleration_max_element_default,
  };

const ConstantString * const enable_polarity_default[DRIVER_COUNT] =
  {
    &step_dir_controller::constants::polarity_low,
  };

const ConstantString * const step_polarity_default[DRIVER_COUNT] =
  {
    &step_dir_controller::constants::polarity_high,
  };

const ConstantString * const dir_polarity_default[DRIVER_COUNT] =
  {
    &step_dir_controller::constants::polarity_high,
  };

const bool left_switch_stop_enabled_default[DRIVER_COUNT] =
  {
    false,
  };

const bool right_switch_stop_enabled_default[DRIVER_COUNT] =
  {
    false,
  };

const bool switch_soft_stop_enabled_default[DRIVER_COUNT] =
  {
    false,
  };

const double home_velocity_default[DRIVER_COUNT] =
  {
    step_dir_controller::constants::home_velocity_element_default,
  };

const long current_scale_default[DRIVER_COUNT] =
  {
    20,
  };

const long microsteps_per_step_default[DRIVER_COUNT] =
  {
    microsteps_per_step_subset[MICROSTEPS_PER_STEP_SUBSET_LENGTH - 1].l,
  };

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
