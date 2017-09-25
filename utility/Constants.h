// ----------------------------------------------------------------------------
// Constants.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef STEPPER_CONTROLLER_CONSTANTS_H
#define STEPPER_CONTROLLER_CONSTANTS_H
#include "ConstantVariable.h"
#include "StepDirController.h"


namespace stepper_controller
{
namespace constants
{
//MAX values must be >= 1, >= created/copied count, < RAM limit
enum{PROPERTY_COUNT_MAX=5};
enum{PARAMETER_COUNT_MAX=1};
enum{FUNCTION_COUNT_MAX=9};
enum{CALLBACK_COUNT_MAX=1};

extern ConstantString device_name;

extern ConstantString firmware_name;
extern const modular_server::FirmwareInfo firmware_info;

extern ConstantString hardware_name;
extern const modular_server::HardwareInfo hardware_info;

extern const size_t controller_count;

extern ConstantString communicating_string;
extern ConstantString load_string;
extern ConstantString full_step_active_string;
extern ConstantString current_scaling_string;
extern ConstantString stall_string;
extern ConstantString over_temperature_shutdown_string;
extern ConstantString over_temperature_warning_string;
extern ConstantString short_to_ground_a_string;
extern ConstantString short_to_ground_b_string;
extern ConstantString open_load_a_string;
extern ConstantString open_load_b_string;
extern ConstantString standstill_string;

// Interrupts

// Units
extern ConstantString percent_units;

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]
extern const long channel_count_default;

extern const long steps_per_position_units_element_default;

extern const long velocity_max_element_default;

extern const long velocity_min_element_default;

extern const long acceleration_max_element_default;

extern const ConstantString * const enable_polarity_element_default;

extern const bool left_switch_stop_enabled_element_default;

extern const bool right_switch_stop_enabled_element_default;

extern const bool switch_soft_stop_enabled_element_default;

extern const long home_velocity_element_default;

extern ConstantString invert_driver_direction_property_name;
extern const bool invert_driver_direction_element_default;

extern ConstantString run_current_property_name;
extern const long percent_min;
extern const long percent_max;
extern const long run_current_element_default;

extern ConstantString hold_current_property_name;
extern const long hold_current_element_default;

extern ConstantString hold_delay_property_name;
extern const long hold_delay_element_default;

extern ConstantString microsteps_per_step_property_name;
enum{MICROSTEPS_PER_STEP_SUBSET_LENGTH=9};
extern modular_server::SubsetMemberType microsteps_per_step_subset[MICROSTEPS_PER_STEP_SUBSET_LENGTH];

// Parameters

// Functions
extern ConstantString get_drivers_status_function_name;
extern ConstantString enable_automatic_current_scaling_function_name;
extern ConstantString disable_automatic_current_scaling_function_name;
extern ConstantString zero_hold_current_function_name;
extern ConstantString restore_hold_current_function_name;
extern ConstantString set_zero_hold_current_normal_operation_function_name;
extern ConstantString set_zero_hold_current_freewheeling_function_name;
extern ConstantString set_zero_hold_current_braking_function_name;
extern ConstantString set_zero_hold_current_intense_braking_function_name;

// Callbacks

// Errors
}
}
#include "5x3.h"
#include "3x2.h"
#endif
