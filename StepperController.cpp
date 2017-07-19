// ----------------------------------------------------------------------------
// StepperController.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "StepperController.h"


using namespace stepper_controller;

StepperController::StepperController()
{
}

void StepperController::setup()
{
  // Parent Setup
  StepDirController::setup();

  // Driver Setup
  for (size_t driver_i=0; driver_i<constants::DRIVER_COUNT; ++driver_i)
  {
    Driver & driver = drivers_[driver_i];
    driver.setup(constants::cs_pins[driver_i]);
  }

  // Pin Setup

  // Set Device ID
  modular_server_.setDeviceName(constants::device_name);

  // Add Hardware

  // Interrupts

  // Add Firmware
  modular_server_.addFirmware(constants::firmware_info,
                              properties_,
                              parameters_,
                              functions_,
                              callbacks_);

  // Properties
  modular_server::Property & steps_per_position_units_property = modular_server_.property(step_dir_controller::constants::steps_per_position_units_property_name);
  steps_per_position_units_property.setDefaultValue(constants::steps_per_position_units_default);

  modular_server::Property & current_scale_property = modular_server_.createProperty(constants::current_scale_property_name,constants::current_scale_default);
  current_scale_property.setUnits(constants::percent_units);
  current_scale_property.setRange(constants::current_scale_min,constants::current_scale_max);
  current_scale_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<const size_t> *)0,*this,&StepperController::setCurrentScaleHandler));

  modular_server::Property & microsteps_per_step_property = modular_server_.createProperty(constants::microsteps_per_step_property_name,constants::microsteps_per_step_default);
  microsteps_per_step_property.setSubset(constants::microsteps_per_step_subset);
  microsteps_per_step_property.attachPreSetElementValueFunctor(makeFunctor((Functor1<const size_t> *)0,*this,&StepperController::preSetMicrostepsPerStepHandler));
  microsteps_per_step_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<const size_t> *)0,*this,&StepperController::postSetMicrostepsPerStepHandler));

  reinitialize();

  // Parameters
  modular_server::Parameter & channel_parameter = modular_server_.parameter(step_dir_controller::constants::channel_parameter_name);

  // Functions
  modular_server::Function & minimize_current_function = modular_server_.createFunction(constants::minimize_current_function_name);
  minimize_current_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepperController::minimizeCurrentHandler));
  minimize_current_function.addParameter(channel_parameter);

  modular_server::Function & restore_current_function = modular_server_.createFunction(constants::restore_current_function_name);
  restore_current_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepperController::restoreCurrentHandler));
  restore_current_function.addParameter(channel_parameter);

  // Callbacks
}

void StepperController::reinitialize()
{
  StepDirController::reinitialize();
  for (size_t driver_i=0; driver_i<constants::DRIVER_COUNT; ++driver_i)
  {
    Driver & driver = drivers_[driver_i];
    driver.setStepDirInput();
    driver.setDefaultChopperConfig();
    driver.disableCoolStep();
    setCurrentScaleHandler(driver_i);
    setMicrostepsPerStepHandler(driver_i);
  }
}

void StepperController::minimizeCurrent(const size_t channel)
{
  if (channel < constants::DRIVER_COUNT)
  {
    drivers_[channel].setCurrentScalePercent(constants::current_scale_min);
  }
}

void StepperController::restoreCurrent(const size_t channel)
{
  if (channel < constants::DRIVER_COUNT)
  {
    setCurrentScaleHandler(channel);
  }
}

double StepperController::stepsToPositionUnits(const size_t channel, const double steps)
{
  double position_units = StepDirController::stepsToPositionUnits(channel,steps);

  modular_server::Property & microsteps_per_step_property = modular_server_.property(constants::microsteps_per_step_property_name);
  long microsteps_per_step;
  microsteps_per_step_property.getElementValue(channel,microsteps_per_step);

  return position_units/microsteps_per_step;
}

double StepperController::positionUnitsToSteps(const size_t channel, const double position_units)
{
  double steps = StepDirController::positionUnitsToSteps(channel,position_units);

  modular_server::Property & microsteps_per_step_property = modular_server_.property(constants::microsteps_per_step_property_name);
  long microsteps_per_step;
  microsteps_per_step_property.getElementValue(channel,microsteps_per_step);

  return steps*microsteps_per_step;
}

// Handlers must be non-blocking (avoid 'delay')
//
// modular_server_.parameter(parameter_name).getValue(value) value type must be either:
// fixed-point number (int, long, etc.)
// floating-point number (float, double)
// bool
// const char *
// ArduinoJson::JsonArray *
// ArduinoJson::JsonObject *
//
// For more info read about ArduinoJson parsing https://github.com/janelia-arduino/ArduinoJson
//
// modular_server_.property(property_name).getValue(value) value type must match the property default type
// modular_server_.property(property_name).setValue(value) value type must match the property default type
// modular_server_.property(property_name).getElementValue(element_index,value) value type must match the property array element default type
// modular_server_.property(property_name).setElementValue(element_index,value) value type must match the property array element default type

void StepperController::setCurrentScaleHandler(const size_t channel)
{
  modular_server::Property & current_scale_property = modular_server_.property(constants::current_scale_property_name);
  long current_scale;
  current_scale_property.getElementValue(channel,current_scale);

  drivers_[channel].setCurrentScalePercent(current_scale);
}

void StepperController::preSetMicrostepsPerStepHandler(const size_t channel)
{
  preUpdateScaledPropertiesHandler(channel);
}

void StepperController::postSetMicrostepsPerStepHandler(const size_t channel)
{
  postUpdateScaledPropertiesHandler(channel);
  setMicrostepsPerStepHandler(channel);
}

void StepperController::setMicrostepsPerStepHandler(const size_t channel)
{
  modular_server::Property & microsteps_per_step_property = modular_server_.property(constants::microsteps_per_step_property_name);
  long microsteps_per_step;
  microsteps_per_step_property.getElementValue(channel,microsteps_per_step);

  Driver & driver = drivers_[channel];
  driver.setMicrostepsPerStep(microsteps_per_step);
}

void StepperController::minimizeCurrentHandler()
{
  long channel;
  modular_server_.parameter(step_dir_controller::constants::channel_parameter_name).getValue(channel);
  minimizeCurrent(channel);
}

void StepperController::restoreCurrentHandler()
{
  long channel;
  modular_server_.parameter(step_dir_controller::constants::channel_parameter_name).getValue(channel);
  restoreCurrent(channel);
}
