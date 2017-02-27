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
enum{PROPERTY_COUNT_MAX=6};
enum{PARAMETER_COUNT_MAX=1};
enum{FUNCTION_COUNT_MAX=1};
enum{CALLBACK_COUNT_MAX=1};

extern ConstantString device_name;

extern ConstantString firmware_name;
extern const modular_server::FirmwareInfo firmware_info;

// Interrupts

// Units
extern ConstantString percent_unit;

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]
extern ConstantString current_scale_property_name;
extern const long current_scale_min;
extern const long current_scale_max;

extern ConstantString microsteps_per_step_property_name;
enum{MICROSTEPS_PER_STEP_SUBSET_LENGTH=9};
extern modular_server::SubsetMemberType microsteps_per_step_subset[MICROSTEPS_PER_STEP_SUBSET_LENGTH];

// Parameters

// Functions

// Callbacks

// Errors
}
}
#include "5x3.h"
#include "3x2.h"
#endif
