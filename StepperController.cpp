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

  // TMC26X Setup
  for (size_t tmc26x_i=0; tmc26x_i<constants::TMC26X_COUNT; ++tmc26x_i)
  {
    TMC26X & tmc26x = tmc26xs_[tmc26x_i];
    tmc26x.setup(constants::cs_pins[tmc26x_i]);
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
  modular_server::Property & current_scale_property = modular_server_.createProperty(constants::current_scale_property_name,constants::current_scale_default);
  current_scale_property.setUnits(constants::percent_unit);
  current_scale_property.setRange(constants::current_scale_min,constants::current_scale_max);
  current_scale_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<const size_t> *)0,*this,&StepperController::setCurrentScaleHandler));

  modular_server::Property & microsteps_per_step_property = modular_server_.createProperty(constants::microsteps_per_step_property_name,constants::microsteps_per_step_default);
  microsteps_per_step_property.setSubset(constants::microsteps_per_step_subset);
  microsteps_per_step_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<const size_t> *)0,*this,&StepperController::setMicrostepsPerStepHandler));

  reinitialize();

  // Parameters

  // Functions

  // Callbacks
}

void StepperController::reinitialize()
{
  StepDirController::reinitialize();
  for (size_t tmc26x_i=0; tmc26x_i<constants::TMC26X_COUNT; ++tmc26x_i)
  {
    TMC26X & tmc26x = tmc26xs_[tmc26x_i];
    tmc26x.setStepDirInput();
    tmc26x.setDefaultChopperConfig();
    tmc26x.disableCoolStep();
    setCurrentScaleHandler(tmc26x_i);
    setMicrostepsPerStepHandler(tmc26x_i);
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
// modular_server_.property(property_name).getElementValue(value) value type must match the property array element default type
// modular_server_.property(property_name).setElementValue(value) value type must match the property array element default type

void StepperController::setCurrentScaleHandler(const size_t driver)
{
  modular_server::Property & current_scale_property = modular_server_.property(constants::current_scale_property_name);
  long current_scale;
  current_scale_property.getElementValue(driver,current_scale);

  current_scale = tmc26xs_[driver].setCurrentScalePercent(current_scale);

  current_scale_property.disableFunctors();

  current_scale_property.setElementValue(driver,current_scale);

  current_scale_property.reenableFunctors();
}

void StepperController::setMicrostepsPerStepHandler(const size_t driver)
{
  modular_server::Property & microsteps_per_step_property = modular_server_.property(constants::microsteps_per_step_property_name);
  long microsteps_per_step;
  microsteps_per_step_property.getElementValue(driver,microsteps_per_step);

  TMC26X & tmc26x = tmc26xs_[driver];

  switch (microsteps_per_step)
  {
    case 1:
    {
      tmc26x.setMicrostepsPerStepTo1();
      break;
    }
    case 2:
    {
      tmc26x.setMicrostepsPerStepTo2();
      break;
    }
    case 4:
    {
      tmc26x.setMicrostepsPerStepTo4();
      break;
    }
    case 8:
    {
      tmc26x.setMicrostepsPerStepTo8();
      break;
    }
    case 16:
    {
      tmc26x.setMicrostepsPerStepTo16();
      break;
    }
    case 32:
    {
      tmc26x.setMicrostepsPerStepTo32();
      break;
    }
    case 64:
    {
      tmc26x.setMicrostepsPerStepTo64();
      break;
    }
    case 128:
    {
      tmc26x.setMicrostepsPerStepTo128();
      break;
    }
    case 256:
    {
      tmc26x.setMicrostepsPerStepTo256();
      break;
    }
  }
}
