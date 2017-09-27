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
const modular_server::HardwareInfo hardware_info =
  {
    .name_ptr=&hardware_name,
    .part_number=1141,
    .version_major=1,
    .version_minor=0,
  };

const size_t controller_count = 1;

const size_t cs_pins[CHANNEL_COUNT_MAX] =
  {
    14,
  };

// Interrupts

// Units

// Properties
const long channel_count_default = CHANNEL_COUNT_MAX;

const long steps_per_position_units_default[CHANNEL_COUNT_MAX] =
  {
    steps_per_position_units_element_default,
  };

const long velocity_max_default[CHANNEL_COUNT_MAX] =
  {
    velocity_max_element_default,
  };

const long velocity_min_default[CHANNEL_COUNT_MAX] =
  {
    velocity_min_element_default,
  };

const long acceleration_max_default[CHANNEL_COUNT_MAX] =
  {
    acceleration_max_element_default,
  };

const ConstantString * const enable_polarity_default[CHANNEL_COUNT_MAX] =
  {
    enable_polarity_element_default,
  };

const bool left_switch_stop_enabled_default[CHANNEL_COUNT_MAX] =
  {
    left_switch_stop_enabled_element_default,
  };

const bool right_switch_stop_enabled_default[CHANNEL_COUNT_MAX] =
  {
    right_switch_stop_enabled_element_default,
  };

const bool switch_soft_stop_enabled_default[CHANNEL_COUNT_MAX] =
  {
    switch_soft_stop_enabled_element_default,
  };

const long home_velocity_default[CHANNEL_COUNT_MAX] =
  {
    home_velocity_element_default,
  };

const bool invert_driver_direction_default[CHANNEL_COUNT_MAX] =
  {
    invert_driver_direction_element_default,
  };

const long run_current_default[CHANNEL_COUNT_MAX] =
  {
    run_current_element_default,
  };

const long hold_current_default[CHANNEL_COUNT_MAX] =
  {
    hold_current_element_default,
  };

const long hold_delay_default[CHANNEL_COUNT_MAX] =
  {
    hold_delay_element_default,
  };

const long microsteps_per_step_default[CHANNEL_COUNT_MAX] =
  {
    microsteps_per_step_subset[MICROSTEPS_PER_STEP_SUBSET_LENGTH - 1].l,
  };

const ConstantString * const zero_hold_current_mode_ptr_default[CHANNEL_COUNT_MAX] =
  {
   &zero_hold_current_mode_freewheeling,
  };

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
