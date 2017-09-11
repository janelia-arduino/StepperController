// ----------------------------------------------------------------------------
// Constants.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "Constants.h"


namespace stepper_controller
{
namespace constants
{
CONSTANT_STRING(device_name,"stepper_controller");

CONSTANT_STRING(firmware_name,"StepperController");
// Use semantic versioning http://semver.org/
const modular_server::FirmwareInfo firmware_info =
  {
    .name_ptr=&firmware_name,
    .version_major=2,
    .version_minor=1,
    .version_patch=1,
  };

CONSTANT_STRING(hardware_name,"stepper_controller");

CONSTANT_STRING(communicating_string,"communicating");
CONSTANT_STRING(load_string,"load");
CONSTANT_STRING(full_step_active_string,"full_step_active");
CONSTANT_STRING(current_scaling_string,"current_scaling");
CONSTANT_STRING(stall_string,"stall");
CONSTANT_STRING(over_temperature_shutdown_string,"over_temperature_shutdown");
CONSTANT_STRING(over_temperature_warning_string,"over_temperature_warning");
CONSTANT_STRING(short_to_ground_a_string,"short_to_ground_a");
CONSTANT_STRING(short_to_ground_b_string,"short_to_ground_b");
CONSTANT_STRING(open_load_a_string,"open_load_a");
CONSTANT_STRING(open_load_b_string,"open_load_b");
CONSTANT_STRING(standstill_string,"standstill");

// Interrupts

// Units
CONSTANT_STRING(percent_units,"%");

// Properties
// 1600 steps per rev with a 200 step count motor at 256 microsteps per step
const long steps_per_position_units_element_default = 32;

const long velocity_max_element_default = 6250;

const long velocity_min_element_default = 625;

const long acceleration_max_element_default = 6250;

const ConstantString * const enable_polarity_element_default = &step_dir_controller::constants::polarity_low;

const bool left_switch_stop_enabled_element_default = false;

const bool right_switch_stop_enabled_element_default = false;

const bool switch_soft_stop_enabled_element_default = false;

const long home_velocity_element_default = -1600;

CONSTANT_STRING(invert_driver_direction_property_name,"invertDriverDirection");
const bool invert_driver_direction_element_default = false;

CONSTANT_STRING(run_current_property_name,"runCurrent");
const long percent_min = 0;
const long percent_max = 100;
const long run_current_element_default = 20;

CONSTANT_STRING(hold_current_property_name,"holdCurrent");
const long hold_current_element_default = 10;

CONSTANT_STRING(hold_delay_property_name,"holdDelay");
const long hold_delay_element_default = 50;

CONSTANT_STRING(microsteps_per_step_property_name,"microstepsPerStep");
modular_server::SubsetMemberType microsteps_per_step_subset[MICROSTEPS_PER_STEP_SUBSET_LENGTH] =
  {
    {.l=1},
    {.l=2},
    {.l=4},
    {.l=8},
    {.l=16},
    {.l=32},
    {.l=64},
    {.l=128},
    {.l=256},
  };

// Parameters

// Functions
CONSTANT_STRING(get_drivers_status_function_name,"getDriversStatus");
CONSTANT_STRING(minimize_hold_current_function_name,"minimizeHoldCurrent");
CONSTANT_STRING(restore_hold_current_function_name,"restoreHoldCurrent");

// Callbacks

// Errors
}
}
