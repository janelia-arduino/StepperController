// ----------------------------------------------------------------------------
// Constants.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef STEPPER_CONTROLLER_CONSTANTS_H
#define STEPPER_CONTROLLER_CONSTANTS_H
#include <ConstantVariable.h>
#include <StepDirController.h>


namespace stepper_controller
{
namespace constants
{
//MAX values must be >= 1, >= created/copied count, < RAM limit
enum{PROPERTY_COUNT_MAX=6};
enum{PARAMETER_COUNT_MAX=1};
enum{FUNCTION_COUNT_MAX=10};
enum{CALLBACK_COUNT_MAX=1};

extern ConstantString device_name;

extern ConstantString firmware_name;
extern const modular_server::FirmwareInfo firmware_info;

extern ConstantString hardware_name;
extern const modular_server::HardwareInfo hardware_info;

extern const size_t controller_count;

extern ConstantString communicating_string;

// Status Strings
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

// Setting Strings
extern ConstantString stealth_chop_enabled_string;
extern ConstantString automatic_current_scaling_enabled_string;
extern ConstantString pwm_offset_string;
extern ConstantString pwm_gradient_string;
extern ConstantString irun_string;
extern ConstantString ihold_string;
extern ConstantString iholddelay_string;

// Pins

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
extern const long microsteps_per_step_element_default;

extern ConstantString zero_hold_current_mode_property_name;
enum{ZERO_HOLD_CURRENT_MODE_SUBSET_LENGTH=4};
extern ConstantString zero_hold_current_mode_normal;
extern ConstantString zero_hold_current_mode_freewheeling;
extern ConstantString zero_hold_current_mode_braking;
extern ConstantString zero_hold_current_mode_strong_braking;
extern modular_server::SubsetMemberType zero_hold_current_mode_ptr_subset[ZERO_HOLD_CURRENT_MODE_SUBSET_LENGTH];
extern const ConstantString * const zero_hold_current_mode_ptr_element_default;

// Parameters
extern ConstantString pwm_amplitude_parameter_name;
extern const long pwm_amplitude_min;
extern const long pwm_amplitude_max;

// Functions
extern ConstantString get_drivers_status_function_name;
extern ConstantString get_drivers_settings_function_name;
extern ConstantString enable_automatic_current_scaling_function_name;
extern ConstantString disable_automatic_current_scaling_function_name;
extern ConstantString zero_hold_current_function_name;
extern ConstantString maximize_hold_current_function_name;
extern ConstantString restore_hold_current_function_name;
extern ConstantString set_pwm_offset_function_name;
extern ConstantString set_pwm_gradient_function_name;
extern ConstantString get_pwm_scales_function_name;

// Callbacks

// Errors
}
}
#include "5x3.h"
#include "3x2.h"
#endif
