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
    .version_major=1,
    .version_minor=0,
    .version_patch=0,
  };

const uint32_t flipper_channels = B11;
const ConstantString * const polarity_up_ptr =  &h_bridge_controller::constants::polarity_positive;
const ConstantString * const polarity_down_ptr =  &h_bridge_controller::constants::polarity_negative;

// Interrupts

// Units

// Properties
CONSTANT_STRING(flipper_delay_property_name,"flipperDelay");
const long flipper_delay_min = 0;
const long flipper_delay_max = 10000;
const long flipper_delay_default = 10;

CONSTANT_STRING(flipper_period_property_name,"flipperPeriod");
const long flipper_period_min = 2;
const long flipper_period_max = 1000;
const long flipper_period_default = 25;

CONSTANT_STRING(flipper_on_duration_property_name,"flipperOnDuration");
const long flipper_on_duration_min = 1;
const long flipper_on_duration_max = 10;
const long flipper_on_duration_default = 4;

CONSTANT_STRING(rung_up_count_lower_property_name,"rungUpCountLower");
const long rung_count_min = 0;
const long rung_count_max = 1000;
const long rung_up_count_lower_default = 1;

CONSTANT_STRING(rung_up_count_upper_property_name,"rungUpCountUpper");
const long rung_up_count_upper_default = 10;

CONSTANT_STRING(rung_down_count_property_name,"rungDownCount");
const long rung_down_count_default = 1;

// Parameters

// Functions
CONSTANT_STRING(flip_enabled_function_name,"flipEnabled");

// Callbacks
CONSTANT_STRING(flip_callback_name,"flip");

CONSTANT_STRING(enable_flip_callback_name,"enableFlip");

CONSTANT_STRING(disable_flip_callback_name,"disableFlip");

// Errors
}
}
