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
  setControllerCount(constants::controller_count);

  // Driver Setup
  for (size_t channel=0; channel<constants::CHANNEL_COUNT_MAX; ++channel)
  {
    Driver & driver = drivers_[channel];
    driver.setup(constants::cs_pins[channel]);
  }

  // Pin Setup

  // Set Device ID
  modular_server_.setDeviceName(constants::device_name);

  // Add Hardware
  modular_server_.removeHardware();
  modular_server_.addHardware(constants::hardware_info,
                              interrupts_);

  // Interrupts

  // Add Firmware
  modular_server_.addFirmware(constants::firmware_info,
                              properties_,
                              parameters_,
                              functions_,
                              callbacks_);

  // Properties
  modular_server::Property & channel_count_property = modular_server_.property(step_dir_controller::constants::channel_count_property_name);
  channel_count_property.disableFunctors();
  channel_count_property.setDefaultValue(constants::channel_count_default);
  channel_count_property.setRange(step_dir_controller::constants::channel_count_min,constants::CHANNEL_COUNT_MAX);
  channel_count_property.attachPostSetValueFunctor(makeFunctor((Functor0 *)0,*this,&StepperController::setChannelCountHandler));
  channel_count_property.reenableFunctors();

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

  modular_server::Property & invert_driver_direction_property = modular_server_.createProperty(constants::invert_driver_direction_property_name,constants::invert_driver_direction_default);
  invert_driver_direction_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<const size_t> *)0,*this,&StepperController::invertDriverDirectionHandler));

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

  // Parameters
  modular_server::Parameter & channel_parameter = modular_server_.parameter(step_dir_controller::constants::channel_parameter_name);

  modular_server::Parameter & pwm_amplitude_parameter = modular_server_.createParameter(constants::pwm_amplitude_parameter_name);
  pwm_amplitude_parameter.setUnits(constants::percent_units);
  pwm_amplitude_parameter.setRange(constants::percent_min,constants::percent_max);

  setChannelCountHandler();
  reinitialize();

  // Functions
  modular_server::Function & get_drivers_status_function = modular_server_.createFunction(constants::get_drivers_status_function_name);
  get_drivers_status_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepperController::getDriversStatusHandler));
  get_drivers_status_function.setResultTypeArray();
  get_drivers_status_function.setResultTypeObject();

  modular_server::Function & get_drivers_settings_function = modular_server_.createFunction(constants::get_drivers_settings_function_name);
  get_drivers_settings_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepperController::getDriversSettingsHandler));
  get_drivers_settings_function.setResultTypeArray();
  get_drivers_settings_function.setResultTypeObject();

  modular_server::Function & enable_automatic_current_scaling_function = modular_server_.createFunction(constants::enable_automatic_current_scaling_function_name);
  enable_automatic_current_scaling_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepperController::enableAutomaticCurrentScalingHandler));
  enable_automatic_current_scaling_function.addParameter(channel_parameter);

  modular_server::Function & disable_automatic_current_scaling_function = modular_server_.createFunction(constants::disable_automatic_current_scaling_function_name);
  disable_automatic_current_scaling_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepperController::disableAutomaticCurrentScalingHandler));
  disable_automatic_current_scaling_function.addParameter(channel_parameter);

  modular_server::Function & set_pwm_offset_function = modular_server_.createFunction(constants::set_pwm_offset_function_name);
  set_pwm_offset_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepperController::setPwmOffsetHandler));
  set_pwm_offset_function.addParameter(channel_parameter);
  set_pwm_offset_function.addParameter(pwm_amplitude_parameter);

  modular_server::Function & set_pwm_gradient_function = modular_server_.createFunction(constants::set_pwm_gradient_function_name);
  set_pwm_gradient_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepperController::setPwmGradientHandler));
  set_pwm_gradient_function.addParameter(channel_parameter);
  set_pwm_gradient_function.addParameter(pwm_amplitude_parameter);

  modular_server::Function & set_zero_hold_current_operation_function = modular_server_.createFunction(constants::set_zero_hold_current_operation_function_name);
  set_zero_hold_current_operation_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepperController::setZeroHoldCurrentOperationHandler));
  set_zero_hold_current_operation_function.addParameter(channel_parameter);

  modular_server::Function & zero_hold_current_function = modular_server_.createFunction(constants::zero_hold_current_function_name);
  zero_hold_current_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepperController::zeroHoldCurrentHandler));
  zero_hold_current_function.addParameter(channel_parameter);

  modular_server::Function & restore_hold_current_function = modular_server_.createFunction(constants::restore_hold_current_function_name);
  restore_hold_current_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepperController::restoreHoldCurrentHandler));
  restore_hold_current_function.addParameter(channel_parameter);

  // Callbacks

}

void StepperController::reinitialize()
{
  StepDirController::reinitialize();

  for (size_t channel=0; channel<getChannelCount(); ++channel)
  {
    drivers_[channel].initialize();
    setMicrostepsPerStepHandler(channel);
    invertDriverDirectionHandler(channel);
    setRunCurrentHandler(channel);
    setHoldCurrentHandler(channel);
    setHoldDelayHandler(channel);
  }
  enableAll();
}

size_t StepperController::getChannelCount()
{
  size_t channel_count = StepDirController::getChannelCount();
  if (channel_count > constants::CHANNEL_COUNT_MAX)
  {
    channel_count = constants::CHANNEL_COUNT_MAX;
  }

  return channel_count;
}

void StepperController::enableAutomaticCurrentScaling(const size_t channel)
{
  if (channel < getChannelCount())
  {
    drivers_[channel].enableAutomaticCurrentScaling();
  }
}

void StepperController::disableAutomaticCurrentScaling(const size_t channel)
{
  if (channel < getChannelCount())
  {
    drivers_[channel].disableAutomaticCurrentScaling();
  }
}

void StepperController::setPwmOffset(const size_t channel,
                                     const uint8_t percent)
{
  if (channel < getChannelCount())
  {
    drivers_[channel].setPwmOffset(percent);
  }
}

void StepperController::setPwmGradient(const size_t channel,
                                       const uint8_t percent)
{
  if (channel < getChannelCount())
  {
    drivers_[channel].setPwmGradient(percent);
  }
}

void StepperController::zeroHoldCurrent(const size_t channel)
{
  if (channel < getChannelCount())
  {
    drivers_[channel].setHoldCurrent(constants::percent_min);
  }
}

void StepperController::restoreHoldCurrent(const size_t channel)
{
  if (channel < getChannelCount())
  {
    setHoldCurrentHandler(channel);
  }
}

void StepperController::setZeroHoldCurrentOperation(const size_t channel,
                                                    const TMC2130::ZeroHoldCurrentOperation operation)
{
  if (channel < getChannelCount())
  {
    drivers_[channel].setZeroHoldCurrentOperation(operation);
  }
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

void StepperController::setChannelCountHandler()
{
  StepDirController::setChannelCountHandler();

  size_t channel_count = getChannelCount();

  modular_server::Property & invert_driver_direction_property = modular_server_.property(constants::invert_driver_direction_property_name);
  invert_driver_direction_property.setArrayLengthRange(channel_count,channel_count);

  modular_server::Property & run_current_property = modular_server_.property(constants::run_current_property_name);
  run_current_property.setArrayLengthRange(channel_count,channel_count);

  modular_server::Property & hold_current_property = modular_server_.property(constants::hold_current_property_name);
  hold_current_property.setArrayLengthRange(channel_count,channel_count);

  modular_server::Property & hold_delay_property = modular_server_.property(constants::hold_delay_property_name);
  hold_delay_property.setArrayLengthRange(channel_count,channel_count);

  modular_server::Property & microsteps_per_step_property = modular_server_.property(constants::microsteps_per_step_property_name);
  microsteps_per_step_property.setArrayLengthRange(channel_count,channel_count);

}

void StepperController::invertDriverDirectionHandler(const size_t channel)
{
  modular_server::Property & invert_driver_direction_property = modular_server_.property(constants::invert_driver_direction_property_name);
  bool invert_driver_direction;
  invert_driver_direction_property.getElementValue(channel,invert_driver_direction);

  // TMC2130 direction is backwards from other drivers
  if (invert_driver_direction)
  {
    drivers_[channel].disableInverseMotorDirection();
  }
  else
  {
    drivers_[channel].enableInverseMotorDirection();
  }
}

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

void StepperController::getDriversStatusHandler()
{
  modular_server_.response().writeResultKey();

  modular_server_.response().beginArray();

  for (size_t channel=0; channel<getChannelCount(); ++channel)
  {
    modular_server_.response().beginObject();

    Driver & driver = drivers_[channel];
    modular_server_.response().write(constants::communicating_string,driver.communicating());

    TMC2130::Status status = driver.getStatus();
    long load_percent = map(status.load,0,TMC2130::LOAD_MAX,constants::percent_min,constants::percent_max);
    modular_server_.response().write(constants::load_string,load_percent);
    modular_server_.response().write(constants::full_step_active_string,status.full_step_active);
    long current_scaling_percent = map(status.current_scaling,0,TMC2130::CURRENT_SCALING_MAX,constants::percent_min,constants::percent_max);
    modular_server_.response().write(constants::current_scaling_string,current_scaling_percent);
    modular_server_.response().write(constants::stall_string,status.stall);
    modular_server_.response().write(constants::over_temperature_shutdown_string,status.over_temperature_shutdown);
    modular_server_.response().write(constants::over_temperature_warning_string,status.over_temperature_warning);
    modular_server_.response().write(constants::short_to_ground_a_string,status.short_to_ground_a);
    modular_server_.response().write(constants::short_to_ground_b_string,status.short_to_ground_b);
    modular_server_.response().write(constants::open_load_a_string,status.open_load_a);
    modular_server_.response().write(constants::open_load_b_string,status.open_load_b);
    modular_server_.response().write(constants::standstill_string,status.standstill);

    modular_server_.response().endObject();
  }

  modular_server_.response().endArray();
}

void StepperController::getDriversSettingsHandler()
{
  modular_server_.response().writeResultKey();

  modular_server_.response().beginArray();

  for (size_t channel=0; channel<getChannelCount(); ++channel)
  {
    modular_server_.response().beginObject();

    Driver & driver = drivers_[channel];
    modular_server_.response().write(constants::communicating_string,driver.communicating());

    TMC2130::Settings settings = driver.getSettings();
    modular_server_.response().write(constants::stealth_chop_enabled_string,settings.stealth_chop_enabled);
    modular_server_.response().write(constants::automatic_current_scaling_enabled_string,settings.automatic_current_scaling_enabled);
    modular_server_.response().write(constants::pwm_offset_string,settings.pwm_offset);
    modular_server_.response().write(constants::pwm_gradient_string,settings.pwm_gradient);
    modular_server_.response().write(constants::zero_hold_current_operation_string,settings.zero_hold_current_operation);

    modular_server_.response().endObject();
  }

  modular_server_.response().endArray();
}

void StepperController::enableAutomaticCurrentScalingHandler()
{
  long channel;
  modular_server_.parameter(step_dir_controller::constants::channel_parameter_name).getValue(channel);
  enableAutomaticCurrentScaling(channel);
}

void StepperController::disableAutomaticCurrentScalingHandler()
{
  long channel;
  modular_server_.parameter(step_dir_controller::constants::channel_parameter_name).getValue(channel);
  disableAutomaticCurrentScaling(channel);
}

void StepperController::setPwmOffsetHandler()
{
  long channel;
  modular_server_.parameter(step_dir_controller::constants::channel_parameter_name).getValue(channel);

  long pwm_amplitude;
  modular_server_.parameter(constants::pwm_amplitude_parameter_name).getValue(pwm_amplitude);

  setPwmOffset(channel,pwm_amplitude);
}

void StepperController::setPwmGradientHandler()
{
  long channel;
  modular_server_.parameter(step_dir_controller::constants::channel_parameter_name).getValue(channel);

  long pwm_amplitude;
  modular_server_.parameter(constants::pwm_amplitude_parameter_name).getValue(pwm_amplitude);

  setPwmGradient(channel,pwm_amplitude);
}

void StepperController::setZeroHoldCurrentOperationHandler()
{
  long channel;
  modular_server_.parameter(step_dir_controller::constants::channel_parameter_name).getValue(channel);
  setZeroHoldCurrentOperation(channel,TMC2130::NORMAL);
}

void StepperController::zeroHoldCurrentHandler()
{
  long channel;
  modular_server_.parameter(step_dir_controller::constants::channel_parameter_name).getValue(channel);
  zeroHoldCurrent(channel);
}

void StepperController::restoreHoldCurrentHandler()
{
  long channel;
  modular_server_.parameter(step_dir_controller::constants::channel_parameter_name).getValue(channel);
  restoreHoldCurrent(channel);
}
