// ----------------------------------------------------------------------------
// Constants.cpp
//
//
// Authors:
// Peter Polidoro peter@polidoro.io
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
  .version_major=4,
  .version_minor=1,
  .version_patch=0,
};

CONSTANT_STRING(hardware_name,"stepper_controller");

extern const size_t check_drivers_duration = 2000;

CONSTANT_STRING(communicating_string,"communicating");

// Status Strings
CONSTANT_STRING(over_temperature_warning_string,"over_temperature_warning");
CONSTANT_STRING(over_temperature_shutdown_string,"over_temperature_shutdown");
CONSTANT_STRING(short_to_ground_a_string,"short_to_ground_a");
CONSTANT_STRING(short_to_ground_b_string,"short_to_ground_b");
CONSTANT_STRING(low_side_short_a_string,"low_side_short_a");
CONSTANT_STRING(low_side_short_b_string,"low_side_short_b");
CONSTANT_STRING(open_load_a_string,"open_load_a");
CONSTANT_STRING(open_load_b_string,"open_load_b");
CONSTANT_STRING(over_temperature_120c_string,"over_temperature_120c");
CONSTANT_STRING(over_temperature_143c_string,"over_temperature_143c");
CONSTANT_STRING(over_temperature_150c_string,"over_temperature_150c");
CONSTANT_STRING(over_temperature_157c_string,"over_temperature_157c");
CONSTANT_STRING(current_scaling_string,"current_scaling");
CONSTANT_STRING(stealth_chop_mode_string,"stealth_chop_mode");
CONSTANT_STRING(standstill_string,"standstill");

// Setting Strings
CONSTANT_STRING(is_setup_string,"is_setup");
CONSTANT_STRING(enabled_string,"enabled");
CONSTANT_STRING(microsteps_per_step_string,"microsteps_per_step");
CONSTANT_STRING(inverse_motor_direction_enabled_string,"inverse_motor_direction_enabled");
CONSTANT_STRING(stealth_chop_enabled_string,"stealth_chop_enabled");
CONSTANT_STRING(irun_percent_string,"irun_percent");
CONSTANT_STRING(irun_register_value_string,"irun_register_value");
CONSTANT_STRING(ihold_percent_string,"ihold_percent");
CONSTANT_STRING(ihold_register_value_string,"ihold_register_value");
CONSTANT_STRING(iholddelay_percent_string,"iholddelay_percent");
CONSTANT_STRING(iholddelay_register_value_string,"iholddelay_register_value");
CONSTANT_STRING(automatic_current_scaling_enabled_string,"automatic_current_scaling_enabled");
CONSTANT_STRING(automatic_gradient_adaptation_enabled_string,"automatic_gradient_adaptation_enabled");
CONSTANT_STRING(cool_step_enabled_string,"cool_step_enabled");
CONSTANT_STRING(analog_current_scaling_enabled_string,"analog_current_scaling_enabled");
CONSTANT_STRING(internal_sense_resistors_enabled_string,"internal_sense_resistors_enabled");

// Measurement Strings
CONSTANT_STRING(interstep_duration_string,"interstep_duration");
CONSTANT_STRING(stall_guard_result_string,"stall_guard_result");
CONSTANT_STRING(pwm_scale_sum_string,"pwm_scale_sum");
CONSTANT_STRING(pwm_scale_auto_string,"pwm_scale_auto");
CONSTANT_STRING(pwm_offset_auto_string,"pwm_offset_auto");
CONSTANT_STRING(pwm_gradient_auto_string,"pwm_gradient_auto");

// Pins

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
const long run_current_element_default = 40;

CONSTANT_STRING(hold_current_property_name,"holdCurrent");
const long hold_current_element_default = 0;

CONSTANT_STRING(hold_delay_property_name,"holdDelay");
const long hold_delay_element_default = 0;

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
const long microsteps_per_step_element_default = 256;

CONSTANT_STRING(standstill_mode_property_name,"standstillMode");
CONSTANT_STRING(standstill_mode_normal,"NORMAL");
CONSTANT_STRING(standstill_mode_freewheeling,"FREEWHEELING");
CONSTANT_STRING(standstill_mode_strong_braking,"STRONG_BRAKING");
CONSTANT_STRING(standstill_mode_braking,"BRAKING");
modular_server::SubsetMemberType standstill_mode_ptr_subset[STANDSTILL_MODE_SUBSET_LENGTH] =
{
  {.cs_ptr=&standstill_mode_normal},
  {.cs_ptr=&standstill_mode_freewheeling},
  {.cs_ptr=&standstill_mode_strong_braking},
  {.cs_ptr=&standstill_mode_braking},
};
const ConstantString * const standstill_mode_ptr_element_default = &standstill_mode_strong_braking;

CONSTANT_STRING(pwm_offset_property_name,"pwmOffset");
const long pwm_offset_element_default = 36;

CONSTANT_STRING(pwm_gradient_property_name,"pwmGradient");
const long pwm_gradient_element_default = 0;

CONSTANT_STRING(automatic_current_scaling_property_name,"automaticCurrentScaling");
const bool automatic_current_scaling_element_default = false;

CONSTANT_STRING(automatic_gradient_adaptation_property_name,"automaticGradientAdaptation");
const bool automatic_gradient_adaptation_element_default = false;

CONSTANT_STRING(cool_step_lower_threshold_property_name,"coolStepLowerThreshold");
const long cool_step_lower_threshold_min = 1;
const long cool_step_lower_threshold_max = 15;
const long cool_step_lower_threshold_element_default = 1;

CONSTANT_STRING(cool_step_upper_threshold_property_name,"coolStepUpperThreshold");
const long cool_step_upper_threshold_min = 0;
const long cool_step_upper_threshold_max = 15;
const long cool_step_upper_threshold_element_default = 0;

CONSTANT_STRING(cool_step_duration_threshold_property_name,"coolStepDurationThreshold");
const long cool_step_duration_threshold_min = 0;
const long cool_step_duration_threshold_max = 1048576;
const long cool_step_duration_threshold_element_default = 2000;

CONSTANT_STRING(cool_step_current_increment_property_name,"coolStepCurrentIncrement");
CONSTANT_STRING(cool_step_current_increment_1,"CURRENT_INCREMENT_1");
CONSTANT_STRING(cool_step_current_increment_2,"CURRENT_INCREMENT_2");
CONSTANT_STRING(cool_step_current_increment_4,"CURRENT_INCREMENT_4");
CONSTANT_STRING(cool_step_current_increment_8,"CURRENT_INCREMENT_8");
modular_server::SubsetMemberType cool_step_current_increment_ptr_subset[COOL_STEP_CURRENT_INCREMENT_SUBSET_LENGTH] =
{
  {.cs_ptr=&cool_step_current_increment_1},
  {.cs_ptr=&cool_step_current_increment_2},
  {.cs_ptr=&cool_step_current_increment_4},
  {.cs_ptr=&cool_step_current_increment_8},
};
const ConstantString * const cool_step_current_increment_ptr_element_default = &cool_step_current_increment_4;

CONSTANT_STRING(cool_step_measurement_count_property_name,"coolStepMeasurementCount");
CONSTANT_STRING(cool_step_measurement_count_32,"MEASUREMENT_COUNT_32");
CONSTANT_STRING(cool_step_measurement_count_8,"MEASUREMENT_COUNT_8");
CONSTANT_STRING(cool_step_measurement_count_2,"MEASUREMENT_COUNT_2");
CONSTANT_STRING(cool_step_measurement_count_1,"MEASUREMENT_COUNT_1");
modular_server::SubsetMemberType cool_step_measurement_count_ptr_subset[COOL_STEP_MEASUREMENT_COUNT_SUBSET_LENGTH] =
{
  {.cs_ptr=&cool_step_measurement_count_32},
  {.cs_ptr=&cool_step_measurement_count_8},
  {.cs_ptr=&cool_step_measurement_count_2},
  {.cs_ptr=&cool_step_measurement_count_1},
};
const ConstantString * const cool_step_measurement_count_ptr_element_default = &cool_step_measurement_count_2;

CONSTANT_STRING(cool_step_enabled_property_name,"coolStepEnabled");
const bool cool_step_enabled_element_default = true;

// Parameters
CONSTANT_STRING(pwm_amplitude_parameter_name,"pwm_amplitude");
const long pwm_amplitude_min = 0;
const long pwm_amplitude_max = 255;

CONSTANT_STRING(current_parameter_name,"current");

// Functions
CONSTANT_STRING(get_drivers_status_function_name,"getDriversStatus");
CONSTANT_STRING(get_drivers_settings_function_name,"getDriversSettings");
CONSTANT_STRING(get_drivers_measurements_function_name,"getDriversMeasurements");
CONSTANT_STRING(standstill_function_name,"standstill");
CONSTANT_STRING(maximize_hold_current_function_name,"maximizeHoldCurrent");
CONSTANT_STRING(modify_hold_current_function_name,"modifyHoldCurrent");
CONSTANT_STRING(restore_hold_current_function_name,"restoreHoldCurrent");
CONSTANT_STRING(modify_run_current_function_name,"modifyRunCurrent");
CONSTANT_STRING(restore_run_current_function_name,"restoreRunCurrent");
CONSTANT_STRING(modify_pwm_offset_function_name,"modifyPwmOffset");
CONSTANT_STRING(restore_pwm_offset_function_name,"restorePwmOffset");
CONSTANT_STRING(modify_pwm_gradient_function_name,"modifyPwmGradient");
CONSTANT_STRING(restore_pwm_gradient_function_name,"restorePwmGradient");

// Callbacks

// Errors
}
}
