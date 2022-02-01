// ----------------------------------------------------------------------------
// StepperController.cpp
//
//
// Authors:
// Peter Polidoro peter@polidoro.io
// ----------------------------------------------------------------------------
#include "../StepperController.h"


using namespace stepper_controller;

void StepperController::setup()
{
  // Parent Setup
  StepDirController::setup();
  setControllerCountLimit(constants::controller_count);

  // Reset Watchdog
  resetWatchdog();

  // Drivers Setup
  check_drivers_time_ = millis();
  for (size_t channel=0; channel<constants::CHANNEL_COUNT_MAX; ++channel)
  {
    drivers_setup_[channel] = false;
  }

  // Pin Setup

  // Set Device ID
  modular_server_.setDeviceName(constants::device_name);

  // Add Hardware
  modular_server_.removeHardware();
  modular_server_.addHardware(constants::hardware_info,
    pins_);

  // Pins

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
  invert_driver_direction_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<size_t> *)0,*this,&StepperController::invertDriverDirectionHandler));

  modular_server::Property & run_current_property = modular_server_.createProperty(constants::run_current_property_name,constants::run_current_default);
  run_current_property.setUnits(constants::percent_units);
  run_current_property.setRange(constants::percent_min,constants::percent_max);
  run_current_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<size_t> *)0,*this,&StepperController::setRunCurrentHandler));

  modular_server::Property & hold_current_property = modular_server_.createProperty(constants::hold_current_property_name,constants::hold_current_default);
  hold_current_property.setUnits(constants::percent_units);
  hold_current_property.setRange(constants::percent_min,constants::percent_max);
  hold_current_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<size_t> *)0,*this,&StepperController::setHoldCurrentHandler));

  modular_server::Property & hold_delay_property = modular_server_.createProperty(constants::hold_delay_property_name,constants::hold_delay_default);
  hold_delay_property.setUnits(constants::percent_units);
  hold_delay_property.setRange(constants::percent_min,constants::percent_max);
  hold_delay_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<size_t> *)0,*this,&StepperController::setHoldDelayHandler));

  modular_server::Property & microsteps_per_step_property = modular_server_.createProperty(constants::microsteps_per_step_property_name,constants::microsteps_per_step_default);
  microsteps_per_step_property.setSubset(constants::microsteps_per_step_subset);
  microsteps_per_step_property.attachPreSetElementValueFunctor(makeFunctor((Functor1<size_t> *)0,*this,&StepperController::preSetMicrostepsPerStepHandler));
  microsteps_per_step_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<size_t> *)0,*this,&StepperController::postSetMicrostepsPerStepHandler));

  modular_server::Property & standstill_mode_property = modular_server_.createProperty(constants::standstill_mode_property_name,constants::standstill_mode_ptr_default);
  standstill_mode_property.setSubset(constants::standstill_mode_ptr_subset);
  standstill_mode_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<size_t> *)0,*this,&StepperController::setStandstillModeHandler));

  modular_server::Property & automatic_current_scaling_property = modular_server_.createProperty(constants::automatic_current_scaling_property_name,constants::automatic_current_scaling_default);
  automatic_current_scaling_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<size_t> *)0,*this,&StepperController::automaticCurrentScalingHandler));

  modular_server::Property & automatic_gradient_adaptation_property = modular_server_.createProperty(constants::automatic_gradient_adaptation_property_name,constants::automatic_gradient_adaptation_default);
  automatic_gradient_adaptation_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<size_t> *)0,*this,&StepperController::automaticGradientAdaptationHandler));

  modular_server::Property & cool_step_lower_threshold_property = modular_server_.createProperty(constants::cool_step_lower_threshold_property_name,constants::cool_step_lower_threshold_default);
  cool_step_lower_threshold_property.setRange(constants::cool_step_lower_threshold_min,constants::cool_step_lower_threshold_max);

  modular_server::Property & cool_step_upper_threshold_property = modular_server_.createProperty(constants::cool_step_upper_threshold_property_name,constants::cool_step_upper_threshold_default);
  cool_step_upper_threshold_property.setRange(constants::cool_step_upper_threshold_min,constants::cool_step_upper_threshold_max);

  modular_server::Property & cool_step_duration_threshold_property = modular_server_.createProperty(constants::cool_step_duration_threshold_property_name,constants::cool_step_duration_threshold_default);
  cool_step_duration_threshold_property.setRange(constants::cool_step_duration_threshold_min,constants::cool_step_duration_threshold_max);
  cool_step_duration_threshold_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<size_t> *)0,*this,&StepperController::coolStepDurationThresholdHandler));

  modular_server::Property & cool_step_current_increment_property = modular_server_.createProperty(constants::cool_step_current_increment_property_name,constants::cool_step_current_increment_ptr_default);
  cool_step_current_increment_property.setSubset(constants::cool_step_current_increment_ptr_subset);
  cool_step_current_increment_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<size_t> *)0,*this,&StepperController::coolStepCurrentIncrementHandler));

  modular_server::Property & cool_step_measurement_count_property = modular_server_.createProperty(constants::cool_step_measurement_count_property_name,constants::cool_step_measurement_count_ptr_default);
  cool_step_measurement_count_property.setSubset(constants::cool_step_measurement_count_ptr_subset);
  cool_step_measurement_count_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<size_t> *)0,*this,&StepperController::coolStepMeasurementCountHandler));

  modular_server::Property & cool_step_enabled_property = modular_server_.createProperty(constants::cool_step_enabled_property_name,constants::cool_step_enabled_default);
  cool_step_enabled_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<size_t> *)0,*this,&StepperController::coolStepEnabledHandler));

  // Parameters
  modular_server::Parameter & channel_parameter = modular_server_.parameter(step_dir_controller::constants::channel_parameter_name);

  modular_server::Parameter & pwm_amplitude_parameter = modular_server_.createParameter(constants::pwm_amplitude_parameter_name);
  pwm_amplitude_parameter.setRange(constants::percent_min,constants::percent_max);

  modular_server::Parameter & current_parameter = modular_server_.createParameter(constants::current_parameter_name);
  current_parameter.setUnits(constants::percent_units);
  current_parameter.setRange(constants::percent_min,constants::percent_max);

  setChannelCountHandler();

  // Functions
  modular_server::Function & get_drivers_status_function = modular_server_.createFunction(constants::get_drivers_status_function_name);
  get_drivers_status_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepperController::getDriversStatusHandler));
  get_drivers_status_function.setResultTypeArray();
  get_drivers_status_function.setResultTypeObject();

  modular_server::Function & get_drivers_settings_function = modular_server_.createFunction(constants::get_drivers_settings_function_name);
  get_drivers_settings_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepperController::getDriversSettingsHandler));
  get_drivers_settings_function.setResultTypeArray();
  get_drivers_settings_function.setResultTypeObject();

  modular_server::Function & get_drivers_measurements_function = modular_server_.createFunction(constants::get_drivers_measurements_function_name);
  get_drivers_measurements_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepperController::getDriversMeasurementsHandler));
  get_drivers_measurements_function.setResultTypeArray();
  get_drivers_measurements_function.setResultTypeObject();

  modular_server::Function & standstill_function = modular_server_.createFunction(constants::standstill_function_name);
  standstill_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepperController::standstillHandler));
  standstill_function.addParameter(channel_parameter);

  modular_server::Function & maximize_hold_current_function = modular_server_.createFunction(constants::maximize_hold_current_function_name);
  maximize_hold_current_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepperController::maximizeHoldCurrentHandler));
  maximize_hold_current_function.addParameter(channel_parameter);

  modular_server::Function & modify_hold_current_function = modular_server_.createFunction(constants::modify_hold_current_function_name);
  modify_hold_current_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepperController::modifyHoldCurrentHandler));
  modify_hold_current_function.addParameter(channel_parameter);
  modify_hold_current_function.addParameter(current_parameter);

  modular_server::Function & restore_hold_current_function = modular_server_.createFunction(constants::restore_hold_current_function_name);
  restore_hold_current_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepperController::restoreHoldCurrentHandler));
  restore_hold_current_function.addParameter(channel_parameter);

  modular_server::Function & modify_run_current_function = modular_server_.createFunction(constants::modify_run_current_function_name);
  modify_run_current_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepperController::modifyRunCurrentHandler));
  modify_run_current_function.addParameter(channel_parameter);
  modify_run_current_function.addParameter(current_parameter);

  modular_server::Function & restore_run_current_function = modular_server_.createFunction(constants::restore_run_current_function_name);
  restore_run_current_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepperController::restoreRunCurrentHandler));
  restore_run_current_function.addParameter(channel_parameter);

  modular_server::Function & set_pwm_offset_function = modular_server_.createFunction(constants::set_pwm_offset_function_name);
  set_pwm_offset_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepperController::setPwmOffsetHandler));
  set_pwm_offset_function.addParameter(channel_parameter);
  set_pwm_offset_function.addParameter(pwm_amplitude_parameter);

  modular_server::Function & set_pwm_gradient_function = modular_server_.createFunction(constants::set_pwm_gradient_function_name);
  set_pwm_gradient_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepperController::setPwmGradientHandler));
  set_pwm_gradient_function.addParameter(channel_parameter);
  set_pwm_gradient_function.addParameter(pwm_amplitude_parameter);

  // Callbacks

}

void StepperController::update()
{
  // Parent Update
  StepDirController::update();

  unsigned long update_time = millis();
  if ((update_time - check_drivers_time_) >= constants::check_drivers_duration)
  {
    check_drivers_time_ = update_time;
    for (size_t channel=0; channel<getChannelCount(); ++channel)
    {
      // handle case where driver power is cycled after controller
      if (not drivers_[channel].communicating())
      {
        drivers_setup_[channel] = false;
      }
      if (not drivers_setup_[channel])
      {
        setupDriver(channel);
      }
    }
  }
}

void StepperController::reinitialize()
{
  StepDirController::reinitialize();

  for (size_t channel=0; channel<getChannelCount(); ++channel)
  {
    reinitializeDriver(channel);
  }
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

void StepperController::enable(size_t channel)
{
  if (channel >= getChannelCount())
  {
    return;
  }
  Driver & driver = drivers_[channel];
  driver.enable();

  enabled_[channel] = true;
}

void StepperController::disable(size_t channel)
{
  if (channel >= getChannelCount())
  {
    return;
  }
  Driver & driver = drivers_[channel];
  driver.disable();

  enabled_[channel] = false;
}

void StepperController::standstill(size_t channel)
{
  if (channel < getChannelCount())
  {
    drivers_[channel].setHoldCurrent(constants::percent_min);
  }
}

void StepperController::maximizeHoldCurrent(size_t channel)
{
  if (channel < getChannelCount())
  {
    drivers_[channel].setHoldCurrent(constants::percent_max);
  }
}

void StepperController::modifyHoldCurrent(size_t channel,
  uint8_t current)
{
  if (channel < getChannelCount())
  {
    drivers_[channel].setHoldCurrent(current);
  }
}

void StepperController::restoreHoldCurrent(size_t channel)
{
  if (channel < getChannelCount())
  {
    setHoldCurrentHandler(channel);
  }
}

void StepperController::modifyRunCurrent(size_t channel,
  uint8_t current)
{
  if (channel < getChannelCount())
  {
    drivers_[channel].setRunCurrent(current);
  }
}

void StepperController::restoreRunCurrent(size_t channel)
{
  if (channel < getChannelCount())
  {
    setRunCurrentHandler(channel);
  }
}

void StepperController::setPwmOffset(size_t channel,
  uint8_t pwm_amplitude)
{
  if (channel < getChannelCount())
  {
    drivers_[channel].setPwmOffset(pwm_amplitude);
  }
}

void StepperController::setPwmGradient(size_t channel,
  uint8_t pwm_amplitude)
{
  if (channel < getChannelCount())
  {
    drivers_[channel].setPwmGradient(pwm_amplitude);
  }
}

HardwareSerial & StepperController::getDriverSerial(size_t driver)
{
  return *(constants::driver_serial_ptrs[driver]);
}

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

  modular_server::Property & standstill_mode_property = modular_server_.property(constants::standstill_mode_property_name);
  standstill_mode_property.setArrayLengthRange(channel_count,channel_count);

  modular_server::Property & automatic_current_scaling_property = modular_server_.property(constants::automatic_current_scaling_property_name);
  automatic_current_scaling_property.setArrayLengthRange(channel_count,channel_count);

  modular_server::Property & automatic_gradient_adaptation_property = modular_server_.property(constants::automatic_gradient_adaptation_property_name);
  automatic_gradient_adaptation_property.setArrayLengthRange(channel_count,channel_count);

  modular_server::Property & cool_step_lower_threshold_property = modular_server_.property(constants::cool_step_lower_threshold_property_name);
  cool_step_lower_threshold_property.setArrayLengthRange(channel_count,channel_count);

  modular_server::Property & cool_step_upper_threshold_property = modular_server_.property(constants::cool_step_upper_threshold_property_name);
  cool_step_upper_threshold_property.setArrayLengthRange(channel_count,channel_count);

  modular_server::Property & cool_step_duration_threshold_property = modular_server_.property(constants::cool_step_duration_threshold_property_name);
  cool_step_duration_threshold_property.setArrayLengthRange(channel_count,channel_count);

  modular_server::Property & cool_step_current_increment_property = modular_server_.property(constants::cool_step_current_increment_property_name);
  cool_step_current_increment_property.setArrayLengthRange(channel_count,channel_count);

  modular_server::Property & cool_step_measurement_count_property = modular_server_.property(constants::cool_step_measurement_count_property_name);
  cool_step_measurement_count_property.setArrayLengthRange(channel_count,channel_count);

  modular_server::Property & cool_step_enabled_property = modular_server_.property(constants::cool_step_enabled_property_name);
  cool_step_enabled_property.setArrayLengthRange(channel_count,channel_count);

}

void StepperController::setupDriver(size_t channel)
{
  drivers_[channel].setup(getDriverSerial(channel));
  reinitializeDriver(channel);
  disable(channel);
  drivers_setup_[channel] = true;
}

 void StepperController::reinitializeDriver(size_t channel)
{
  resetWatchdog();
  if (not drivers_[channel].communicating())
  {
    return;
  }
  invertDriverDirectionHandler(channel);
  setRunCurrentHandler(channel);
  setHoldCurrentHandler(channel);
  setHoldDelayHandler(channel);
  setMicrostepsPerStepHandler(channel);
  setStandstillModeHandler(channel);
  automaticCurrentScalingHandler(channel);
  coolStepDurationThresholdHandler(channel);
  coolStepCurrentIncrementHandler(channel);
  coolStepEnabledHandler(channel);
}

void StepperController::invertDriverDirectionHandler(size_t channel)
{
  modular_server::Property & invert_driver_direction_property = modular_server_.property(constants::invert_driver_direction_property_name);
  bool invert_driver_direction;
  invert_driver_direction_property.getElementValue(channel,invert_driver_direction);

  if (invert_driver_direction)
  {
    drivers_[channel].enableInverseMotorDirection();
  }
  else
  {
    drivers_[channel].disableInverseMotorDirection();
  }
}

void StepperController::setRunCurrentHandler(size_t channel)
{
  modular_server::Property & run_current_property = modular_server_.property(constants::run_current_property_name);
  long run_current;
  run_current_property.getElementValue(channel,run_current);

  drivers_[channel].setRunCurrent(run_current);
}

void StepperController::setHoldCurrentHandler(size_t channel)
{
  modular_server::Property & hold_current_property = modular_server_.property(constants::hold_current_property_name);
  long hold_current;
  hold_current_property.getElementValue(channel,hold_current);

  drivers_[channel].setHoldCurrent(hold_current);
}

void StepperController::setHoldDelayHandler(size_t channel)
{
  modular_server::Property & hold_delay_property = modular_server_.property(constants::hold_delay_property_name);
  long hold_delay;
  hold_delay_property.getElementValue(channel,hold_delay);

  drivers_[channel].setHoldDelay(hold_delay);
}

void StepperController::preSetMicrostepsPerStepHandler(size_t channel)
{
  preUpdateScaledPropertiesHandler(channel);
}

void StepperController::postSetMicrostepsPerStepHandler(size_t channel)
{
  postUpdateScaledPropertiesHandler(channel);
  setMicrostepsPerStepHandler(channel);
}

void StepperController::setMicrostepsPerStepHandler(size_t channel)
{
  modular_server::Property & microsteps_per_step_property = modular_server_.property(constants::microsteps_per_step_property_name);
  long microsteps_per_step;
  microsteps_per_step_property.getElementValue(channel,microsteps_per_step);

  Driver & driver = drivers_[channel];
  driver.setMicrostepsPerStep(microsteps_per_step);
}

void StepperController::setStandstillModeHandler(size_t channel)
{
  const ConstantString * mode_ptr;
  modular_server_.property(constants::standstill_mode_property_name).getElementValue(channel,mode_ptr);

  TMC2209::StandstillMode standstill_mode = TMC2209::NORMAL;
  if (mode_ptr == &constants::standstill_mode_normal)
  {
    standstill_mode = TMC2209::NORMAL;
  }
  else if (mode_ptr == &constants::standstill_mode_freewheeling)
  {
    standstill_mode = TMC2209::FREEWHEELING;
  }
  else if (mode_ptr == &constants::standstill_mode_strong_braking)
  {
    standstill_mode = TMC2209::STRONG_BRAKING;
  }
  else if (mode_ptr == &constants::standstill_mode_braking)
  {
    standstill_mode = TMC2209::BRAKING;
  }
  Driver & driver = drivers_[channel];
  driver.setStandstillMode(standstill_mode);
}

void StepperController::automaticCurrentScalingHandler(size_t channel)
{
  modular_server::Property & automatic_current_scaling_property = modular_server_.property(constants::automatic_current_scaling_property_name);
  bool automatic_current_scaling;
  automatic_current_scaling_property.getElementValue(channel,automatic_current_scaling);

  if (automatic_current_scaling)
  {
    drivers_[channel].enableAutomaticCurrentScaling();
  }
  else
  {
    drivers_[channel].disableAutomaticCurrentScaling();
  }
}

void StepperController::automaticGradientAdaptationHandler(size_t channel)
{
  modular_server::Property & automatic_gradient_adaptation_property = modular_server_.property(constants::automatic_gradient_adaptation_property_name);
  bool automatic_gradient_adaptation;
  automatic_gradient_adaptation_property.getElementValue(channel,automatic_gradient_adaptation);

  if (automatic_gradient_adaptation)
  {
    drivers_[channel].enableAutomaticGradientAdaptation();
  }
  else
  {
    drivers_[channel].disableAutomaticGradientAdaptation();

  }
}

void StepperController::coolStepDurationThresholdHandler(size_t channel)
{
  modular_server::Property & cool_step_duration_threshold_property = modular_server_.property(constants::cool_step_duration_threshold_property_name);
  long cool_step_duration_threshold;
  cool_step_duration_threshold_property.getElementValue(channel,cool_step_duration_threshold);

  drivers_[channel].setCoolStepDurationThreshold(cool_step_duration_threshold);
}

void StepperController::coolStepCurrentIncrementHandler(size_t channel)
{
  const ConstantString * cool_step_current_increment_ptr;
  modular_server_.property(constants::cool_step_current_increment_property_name).getElementValue(channel,cool_step_current_increment_ptr);

  TMC2209::CurrentIncrement cool_step_current_increment = TMC2209::CURRENT_INCREMENT_4;
  if (cool_step_current_increment_ptr == &constants::cool_step_current_increment_1)
  {
    cool_step_current_increment = TMC2209::CURRENT_INCREMENT_1;
  }
  else if (cool_step_current_increment_ptr == &constants::cool_step_current_increment_2)
  {
    cool_step_current_increment = TMC2209::CURRENT_INCREMENT_2;
  }
  else if (cool_step_current_increment_ptr == &constants::cool_step_current_increment_4)
  {
    cool_step_current_increment = TMC2209::CURRENT_INCREMENT_4;
  }
  else if (cool_step_current_increment_ptr == &constants::cool_step_current_increment_8)
  {
    cool_step_current_increment = TMC2209::CURRENT_INCREMENT_8;
  }
  Driver & driver = drivers_[channel];
  driver.setCoolStepCurrentIncrement(cool_step_current_increment);
}

void StepperController::coolStepMeasurementCountHandler(size_t channel)
{
  const ConstantString * cool_step_measurement_count_ptr;
  modular_server_.property(constants::cool_step_measurement_count_property_name).getElementValue(channel,cool_step_measurement_count_ptr);

  TMC2209::MeasurementCount cool_step_measurement_count = TMC2209::MEASUREMENT_COUNT_2;
  if (cool_step_measurement_count_ptr == &constants::cool_step_measurement_count_32)
  {
    cool_step_measurement_count = TMC2209::MEASUREMENT_COUNT_32;
  }
  else if (cool_step_measurement_count_ptr == &constants::cool_step_measurement_count_8)
  {
    cool_step_measurement_count = TMC2209::MEASUREMENT_COUNT_8;
  }
  else if (cool_step_measurement_count_ptr == &constants::cool_step_measurement_count_2)
  {
    cool_step_measurement_count = TMC2209::MEASUREMENT_COUNT_2;
  }
  else if (cool_step_measurement_count_ptr == &constants::cool_step_measurement_count_1)
  {
    cool_step_measurement_count = TMC2209::MEASUREMENT_COUNT_1;
  }
  Driver & driver = drivers_[channel];
  driver.setCoolStepMeasurementCount(cool_step_measurement_count);
}

void StepperController::coolStepEnabledHandler(size_t channel)
{
  modular_server::Property & cool_step_enabled_property = modular_server_.property(constants::cool_step_enabled_property_name);
  bool cool_step_enabled;
  cool_step_enabled_property.getElementValue(channel,cool_step_enabled);

  if (cool_step_enabled)
  {
    modular_server::Property & cool_step_lower_threshold_property = modular_server_.property(constants::cool_step_lower_threshold_property_name);
    long cool_step_lower_threshold;
    cool_step_lower_threshold_property.getElementValue(channel,cool_step_lower_threshold);
    modular_server::Property & cool_step_upper_threshold_property = modular_server_.property(constants::cool_step_upper_threshold_property_name);
    long cool_step_upper_threshold;
    cool_step_upper_threshold_property.getElementValue(channel,cool_step_upper_threshold);
    drivers_[channel].enableCoolStep(cool_step_lower_threshold,cool_step_upper_threshold);
  }
  else
  {
    drivers_[channel].disableCoolStep();

  }
}

void StepperController::getDriversStatusHandler()
{
  modular_server_.response().writeResultKey();

  modular_server_.response().beginArray();

  for (size_t channel=0; channel<getChannelCount(); ++channel)
  {
    modular_server_.response().beginObject();

    Driver & driver = drivers_[channel];

    bool communicating = driver.communicating();
    modular_server_.response().write(constants::communicating_string,communicating);
    if (not communicating)
    {
      modular_server_.response().endObject();
      continue;
    }

    TMC2209::Status status = driver.getStatus();
    modular_server_.response().write(constants::over_temperature_warning_string,status.over_temperature_warning);
    modular_server_.response().write(constants::over_temperature_shutdown_string,status.over_temperature_shutdown);
    modular_server_.response().write(constants::short_to_ground_a_string,status.short_to_ground_a);
    modular_server_.response().write(constants::short_to_ground_b_string,status.short_to_ground_b);
    modular_server_.response().write(constants::low_side_short_a_string,status.low_side_short_a);
    modular_server_.response().write(constants::low_side_short_b_string,status.low_side_short_b);
    modular_server_.response().write(constants::open_load_a_string,status.open_load_a);
    modular_server_.response().write(constants::open_load_b_string,status.open_load_b);
    modular_server_.response().write(constants::over_temperature_120c_string,status.over_temperature_120c);
    modular_server_.response().write(constants::over_temperature_143c_string,status.over_temperature_143c);
    modular_server_.response().write(constants::over_temperature_150c_string,status.over_temperature_150c);
    modular_server_.response().write(constants::over_temperature_157c_string,status.over_temperature_157c);
    modular_server_.response().write(constants::current_scaling_string,status.current_scaling);
    modular_server_.response().write(constants::stealth_chop_mode_string,status.stealth_chop_mode);
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

    bool communicating = driver.communicating();
    modular_server_.response().write(constants::communicating_string,communicating);

    if (not communicating)
    {
      modular_server_.response().endObject();
      continue;
    }

    TMC2209::Settings settings = driver.getSettings();

    modular_server_.response().write(constants::enabled_string,settings.enabled);
    modular_server_.response().write(constants::microsteps_per_step_string,settings.microsteps_per_step);
    modular_server_.response().write(constants::inverse_motor_direction_enabled_string,settings.inverse_motor_direction_enabled);
    modular_server_.response().write(constants::stealth_chop_enabled_string,settings.stealth_chop_enabled);
    const ConstantString * standstill_mode_ptr = NULL;
    if (settings.standstill_mode == TMC2209::NORMAL)
    {
      standstill_mode_ptr = &constants::standstill_mode_normal;
    }
    else if (settings.standstill_mode == TMC2209::FREEWHEELING)
    {
      standstill_mode_ptr = &constants::standstill_mode_freewheeling;
    }
    else if (settings.standstill_mode == TMC2209::BRAKING)
    {
      standstill_mode_ptr = &constants::standstill_mode_braking;
    }
    else if (settings.standstill_mode == TMC2209::STRONG_BRAKING)
    {
      standstill_mode_ptr = &constants::standstill_mode_strong_braking;
    }
    modular_server_.response().write(constants::standstill_mode_property_name,*standstill_mode_ptr);
    modular_server_.response().write(constants::irun_percent_string,settings.irun_percent);
    modular_server_.response().write(constants::irun_register_value_string,settings.irun_register_value);
    modular_server_.response().write(constants::ihold_percent_string,settings.ihold_percent);
    modular_server_.response().write(constants::ihold_register_value_string,settings.ihold_register_value);
    modular_server_.response().write(constants::iholddelay_percent_string,settings.iholddelay_percent);
    modular_server_.response().write(constants::iholddelay_register_value_string,settings.iholddelay_register_value);
    modular_server_.response().write(constants::automatic_current_scaling_enabled_string,settings.automatic_current_scaling_enabled);
    modular_server_.response().write(constants::automatic_gradient_adaptation_enabled_string,settings.automatic_gradient_adaptation_enabled);
    modular_server_.response().write(constants::pwm_offset_string,settings.pwm_offset);
    modular_server_.response().write(constants::pwm_gradient_string,settings.pwm_gradient);
    modular_server_.response().write(constants::cool_step_enabled_string,settings.cool_step_enabled);
    modular_server_.response().write(constants::analog_current_scaling_enabled_string,settings.analog_current_scaling_enabled);
    modular_server_.response().write(constants::internal_sense_resistors_enabled_string,settings.internal_sense_resistors_enabled);

    modular_server_.response().endObject();
  }

  modular_server_.response().endArray();
}

void StepperController::getDriversMeasurementsHandler()
{
  modular_server_.response().writeResultKey();

  modular_server_.response().beginArray();

  for (size_t channel=0; channel<getChannelCount(); ++channel)
  {
    modular_server_.response().beginObject();

    Driver & driver = drivers_[channel];

    bool communicating = driver.communicating();
    modular_server_.response().write(constants::communicating_string,communicating);
    if (not communicating)
    {
      modular_server_.response().endObject();
      continue;
    }

    uint32_t interstep_duration = driver.getInterstepDuration();
    modular_server_.response().write(constants::interstep_duration_string,interstep_duration);

    uint16_t stall_guard_result = driver.getStallGuardResult();
    modular_server_.response().write(constants::stall_guard_result_string,stall_guard_result);

    uint8_t pwm_scale_sum = driver.getPwmScaleSum();
    modular_server_.response().write(constants::pwm_scale_sum_string,pwm_scale_sum);

    int16_t pwm_scale_auto = driver.getPwmScaleAuto();
    modular_server_.response().write(constants::pwm_scale_auto_string,pwm_scale_auto);

    uint8_t pwm_offset_auto = driver.getPwmOffsetAuto();
    modular_server_.response().write(constants::pwm_offset_auto_string,pwm_offset_auto);

    uint8_t pwm_gradient_auto = driver.getPwmGradientAuto();
    modular_server_.response().write(constants::pwm_gradient_auto_string,pwm_gradient_auto);

    modular_server_.response().endObject();
  }

  modular_server_.response().endArray();
}

void StepperController::standstillHandler()
{
  long channel;
  modular_server_.parameter(step_dir_controller::constants::channel_parameter_name).getValue(channel);

  standstill(channel);
}

void StepperController::maximizeHoldCurrentHandler()
{
  long channel;
  modular_server_.parameter(step_dir_controller::constants::channel_parameter_name).getValue(channel);

  maximizeHoldCurrent(channel);
}

void StepperController::modifyHoldCurrentHandler()
{
  long channel;
  modular_server_.parameter(step_dir_controller::constants::channel_parameter_name).getValue(channel);

  long current;
  modular_server_.parameter(constants::current_parameter_name).getValue(current);

  modifyHoldCurrent(channel,current);
}

void StepperController::restoreHoldCurrentHandler()
{
  long channel;
  modular_server_.parameter(step_dir_controller::constants::channel_parameter_name).getValue(channel);

  restoreHoldCurrent(channel);
}

void StepperController::modifyRunCurrentHandler()
{
  long channel;
  modular_server_.parameter(step_dir_controller::constants::channel_parameter_name).getValue(channel);

  long current;
  modular_server_.parameter(constants::current_parameter_name).getValue(current);

  modifyRunCurrent(channel,current);
}

void StepperController::restoreRunCurrentHandler()
{
  long channel;
  modular_server_.parameter(step_dir_controller::constants::channel_parameter_name).getValue(channel);

  restoreRunCurrent(channel);
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
