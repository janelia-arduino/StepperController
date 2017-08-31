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
const long steps_per_position_units_default[DRIVER_COUNT] =
  {
    steps_per_position_units_element_default,
  };

const long velocity_max_default[DRIVER_COUNT] =
  {
    velocity_max_element_default,
  };

const long velocity_min_default[DRIVER_COUNT] =
  {
    velocity_min_element_default,
  };

const long acceleration_max_default[DRIVER_COUNT] =
  {
    acceleration_max_element_default,
  };

const ConstantString * const enable_polarity_default[DRIVER_COUNT] =
  {
    enable_polarity_element_default,
  };

const bool left_switch_stop_enabled_default[DRIVER_COUNT] =
  {
    left_switch_stop_enabled_element_default,
  };

const bool right_switch_stop_enabled_default[DRIVER_COUNT] =
  {
    right_switch_stop_enabled_element_default,
  };

const bool switch_soft_stop_enabled_default[DRIVER_COUNT] =
  {
    switch_soft_stop_enabled_element_default,
  };

const long home_velocity_default[DRIVER_COUNT] =
  {
    home_velocity_element_default,
  };

const bool invert_driver_direction_default[DRIVER_COUNT] =
  {
    invert_driver_direction_element_default,
  };

const long run_current_default[DRIVER_COUNT] =
  {
    run_current_element_default,
  };

const long hold_current_default[DRIVER_COUNT] =
  {
    hold_current_element_default,
  };

const long hold_delay_default[DRIVER_COUNT] =
  {
    hold_delay_element_default,
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
