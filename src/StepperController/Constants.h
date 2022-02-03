// ----------------------------------------------------------------------------
// Constants.h
//
//
// Authors:
// Peter Polidoro peter@polidoro.io
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
enum{PROPERTY_COUNT_MAX=14};
enum{PARAMETER_COUNT_MAX=2};
enum{FUNCTION_COUNT_MAX=11};
enum{CALLBACK_COUNT_MAX=1};

extern ConstantString device_name;

extern ConstantString firmware_name;
extern const modular_server::FirmwareInfo firmware_info;

extern ConstantString hardware_name;
extern const modular_server::HardwareInfo hardware_info;

extern const size_t controller_count;

extern const size_t check_drivers_duration;

extern ConstantString communicating_string;

// Status Strings
extern ConstantString over_temperature_warning_string;
extern ConstantString over_temperature_shutdown_string;
extern ConstantString short_to_ground_a_string;
extern ConstantString short_to_ground_b_string;
extern ConstantString low_side_short_a_string;
extern ConstantString low_side_short_b_string;
extern ConstantString open_load_a_string;
extern ConstantString open_load_b_string;
extern ConstantString over_temperature_120c_string;
extern ConstantString over_temperature_143c_string;
extern ConstantString over_temperature_150c_string;
extern ConstantString over_temperature_157c_string;
extern ConstantString current_scaling_string;
extern ConstantString stealth_chop_mode_string;
extern ConstantString standstill_string;

// Setting Strings
extern ConstantString is_setup_string;
extern ConstantString enabled_string;
extern ConstantString microsteps_per_step_string;
extern ConstantString inverse_motor_direction_enabled_string;
extern ConstantString stealth_chop_enabled_string;
extern ConstantString irun_percent_string;
extern ConstantString irun_register_value_string;
extern ConstantString ihold_percent_string;
extern ConstantString ihold_register_value_string;
extern ConstantString iholddelay_percent_string;
extern ConstantString iholddelay_register_value_string;
extern ConstantString automatic_current_scaling_enabled_string;
extern ConstantString automatic_gradient_adaptation_enabled_string;
extern ConstantString pwm_offset_string;
extern ConstantString pwm_gradient_string;
extern ConstantString cool_step_enabled_string;
extern ConstantString analog_current_scaling_enabled_string;
extern ConstantString internal_sense_resistors_enabled_string;

// Measurement Strings
extern ConstantString interstep_duration_string;
extern ConstantString stall_guard_result_string;
extern ConstantString pwm_scale_sum_string;
extern ConstantString pwm_scale_auto_string;
extern ConstantString pwm_offset_auto_string;
extern ConstantString pwm_gradient_auto_string;

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

extern ConstantString standstill_mode_property_name;
enum{STANDSTILL_MODE_SUBSET_LENGTH=4};
extern ConstantString standstill_mode_normal;
extern ConstantString standstill_mode_freewheeling;
extern ConstantString standstill_mode_braking;
extern ConstantString standstill_mode_strong_braking;
extern modular_server::SubsetMemberType standstill_mode_ptr_subset[STANDSTILL_MODE_SUBSET_LENGTH];
extern const ConstantString * const standstill_mode_ptr_element_default;

extern ConstantString automatic_current_scaling_property_name;
extern const bool automatic_current_scaling_element_default;

extern ConstantString automatic_gradient_adaptation_property_name;
extern const bool automatic_gradient_adaptation_element_default;

extern ConstantString cool_step_lower_threshold_property_name;
extern const long cool_step_lower_threshold_min;
extern const long cool_step_lower_threshold_max;
extern const long cool_step_lower_threshold_element_default;

extern ConstantString cool_step_upper_threshold_property_name;
extern const long cool_step_upper_threshold_min;
extern const long cool_step_upper_threshold_max;
extern const long cool_step_upper_threshold_element_default;

extern ConstantString cool_step_duration_threshold_property_name;
extern const long cool_step_duration_threshold_min;
extern const long cool_step_duration_threshold_max;
extern const long cool_step_duration_threshold_element_default;

extern ConstantString cool_step_current_increment_property_name;
enum{COOL_STEP_CURRENT_INCREMENT_SUBSET_LENGTH=4};
extern ConstantString cool_step_current_increment_1;
extern ConstantString cool_step_current_increment_2;
extern ConstantString cool_step_current_increment_4;
extern ConstantString cool_step_current_increment_8;
extern modular_server::SubsetMemberType cool_step_current_increment_ptr_subset[COOL_STEP_CURRENT_INCREMENT_SUBSET_LENGTH];
extern const ConstantString * const cool_step_current_increment_ptr_element_default;

extern ConstantString cool_step_measurement_count_property_name;
enum{COOL_STEP_MEASUREMENT_COUNT_SUBSET_LENGTH=4};
extern ConstantString cool_step_measurement_count_32;
extern ConstantString cool_step_measurement_count_8;
extern ConstantString cool_step_measurement_count_2;
extern ConstantString cool_step_measurement_count_1;
extern modular_server::SubsetMemberType cool_step_measurement_count_ptr_subset[COOL_STEP_MEASUREMENT_COUNT_SUBSET_LENGTH];
extern const ConstantString * const cool_step_measurement_count_ptr_element_default;

extern ConstantString cool_step_enabled_property_name;
extern const bool cool_step_enabled_element_default;

// Parameters
extern ConstantString pwm_amplitude_parameter_name;
extern const long pwm_amplitude_min;
extern const long pwm_amplitude_max;

extern ConstantString current_parameter_name;

// Functions
extern ConstantString get_drivers_status_function_name;
extern ConstantString get_drivers_settings_function_name;
extern ConstantString get_drivers_measurements_function_name;
extern ConstantString standstill_function_name;
extern ConstantString maximize_hold_current_function_name;
extern ConstantString modify_hold_current_function_name;
extern ConstantString restore_hold_current_function_name;
extern ConstantString modify_run_current_function_name;
extern ConstantString restore_run_current_function_name;
extern ConstantString set_pwm_offset_function_name;
extern ConstantString set_pwm_gradient_function_name;

// Callbacks

// Errors
}
}
#include "TEENSY40.h"
#endif
