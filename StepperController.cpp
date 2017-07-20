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

  modular_server::Property & velocity_max_property = modular_server_.property(step_dir_controller::constants::velocity_max_property_name);
  velocity_max_property.setDefaultValue(constants::velocity_max_default);

  modular_server::Property & velocity_min_property = modular_server_.property(step_dir_controller::constants::velocity_min_property_name);
  velocity_min_property.setDefaultValue(constants::velocity_min_default);

  modular_server::Property & acceleration_max_property = modular_server_.property(step_dir_controller::constants::acceleration_max_property_name);
  acceleration_max_property.setDefaultValue(constants::acceleration_max_default);

  modular_server::Property & enable_polarity_property = modular_server_.property(step_dir_controller::constants::enable_polarity_property_name);
  enable_polarity_property.setDefaultValue(constants::enable_polarity_default);

  modular_server::Property & left_switch_stop_enabled_property = modular_server_.property(step_dir_controller::constants::left_switch_stop_enabled_property_name);
  left_switch_stop_enabled_property.setDefaultValue(constants::left_switch_stop_enabled_default);

  modular_server::Property & right_switch_stop_enabled_property = modular_server_.property(step_dir_controller::constants::right_switch_stop_enabled_property_name);
  right_switch_stop_enabled_property.setDefaultValue(constants::right_switch_stop_enabled_default);

  modular_server::Property & switch_soft_stop_enabled_property = modular_server_.property(step_dir_controller::constants::switch_soft_stop_enabled_property_name);
  switch_soft_stop_enabled_property.setDefaultValue(constants::switch_soft_stop_enabled_default);

  modular_server::Property & home_velocity_property = modular_server_.property(step_dir_controller::constants::home_velocity_property_name);
  home_velocity_property.setDefaultValue(constants::home_velocity_default);

  modular_server::Property & run_current_property = modular_server_.createProperty(constants::run_current_property_name,constants::run_current_default);
  run_current_property.setUnits(constants::percent_units);
  run_current_property.setRange(constants::percent_min,constants::percent_max);
  run_current_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<const size_t> *)0,*this,&StepperController::setRunCurrentHandler));

  modular_server::Property & hold_current_property = modular_server_.createProperty(constants::hold_current_property_name,constants::hold_current_default);
  hold_current_property.setUnits(constants::percent_units);
  hold_current_property.setRange(constants::percent_min,constants::percent_max);
  hold_current_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<const size_t> *)0,*this,&StepperController::setHoldCurrentHandler));

  modular_server::Property & hold_delay_property = modular_server_.createProperty(constants::hold_delay_property_name,constants::hold_delay_default);
  hold_delay_property.setUnits(constants::percent_units);
  hold_delay_property.setRange(constants::percent_min,constants::percent_max);
  hold_delay_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<const size_t> *)0,*this,&StepperController::setHoldDelayHandler));

  modular_server::Property & microsteps_per_step_property = modular_server_.createProperty(constants::microsteps_per_step_property_name,constants::microsteps_per_step_default);
  microsteps_per_step_property.setSubset(constants::microsteps_per_step_subset);
  microsteps_per_step_property.attachPreSetElementValueFunctor(makeFunctor((Functor1<const size_t> *)0,*this,&StepperController::preSetMicrostepsPerStepHandler));
  microsteps_per_step_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<const size_t> *)0,*this,&StepperController::postSetMicrostepsPerStepHandler));

  reinitialize();

  // Parameters
  modular_server::Parameter & channel_parameter = modular_server_.parameter(step_dir_controller::constants::channel_parameter_name);

  // Functions
  modular_server::Function & minimize_hold_current_function = modular_server_.createFunction(constants::minimize_hold_current_function_name);
  minimize_hold_current_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepperController::minimizeHoldCurrentHandler));
  minimize_hold_current_function.addParameter(channel_parameter);

  modular_server::Function & restore_hold_current_function = modular_server_.createFunction(constants::restore_hold_current_function_name);
  restore_hold_current_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepperController::restoreHoldCurrentHandler));
  restore_hold_current_function.addParameter(channel_parameter);

  // Callbacks

}

void StepperController::reinitialize()
{
  StepDirController::reinitialize();
  for (size_t driver_i=0; driver_i<constants::DRIVER_COUNT; ++driver_i)
  {
    setMicrostepsPerStepHandler(driver_i);
    setRunCurrentHandler(driver_i);
    setHoldCurrentHandler(driver_i);
    setHoldDelayHandler(driver_i);
  }
}

void StepperController::minimizeHoldCurrent(const size_t channel)
{
  if (channel < constants::DRIVER_COUNT)
  {
    drivers_[channel].setHoldCurrent(constants::percent_min);
  }
}

void StepperController::restoreHoldCurrent(const size_t channel)
{
  if (channel < constants::DRIVER_COUNT)
  {
    setHoldCurrentHandler(channel);
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

void StepperController::setRunCurrentHandler(const size_t channel)
{
  modular_server::Property & run_current_property = modular_server_.property(constants::run_current_property_name);
  long run_current;
  run_current_property.getElementValue(channel,run_current);

  drivers_[channel].setRunCurrent(run_current);
}

void StepperController::setHoldCurrentHandler(const size_t channel)
{
  modular_server::Property & hold_current_property = modular_server_.property(constants::hold_current_property_name);
  long hold_current;
  hold_current_property.getElementValue(channel,hold_current);

  drivers_[channel].setHoldCurrent(hold_current);
}

void StepperController::setHoldDelayHandler(const size_t channel)
{
  modular_server::Property & hold_delay_property = modular_server_.property(constants::hold_delay_property_name);
  long hold_delay;
  hold_delay_property.getElementValue(channel,hold_delay);

  drivers_[channel].setHoldDelay(hold_delay);
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

void StepperController::minimizeHoldCurrentHandler()
{
  long channel;
  modular_server_.parameter(step_dir_controller::constants::channel_parameter_name).getValue(channel);
  minimizeHoldCurrent(channel);
}

void StepperController::restoreHoldCurrentHandler()
{
  long channel;
  modular_server_.parameter(step_dir_controller::constants::channel_parameter_name).getValue(channel);
  restoreHoldCurrent(channel);
}
