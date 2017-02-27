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
    tmc26x.setStepDirInput();
    tmc26x.setDefaultChopperConfig();
    tmc26x.disableCoolStep();
    // tmc26X.setMicrostepsPerStepTo256();
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

  for (size_t tmc26x_i=0; tmc26x_i<constants::TMC26X_COUNT; ++tmc26x_i)
  {
    setCurrentScaleHandler(tmc26x_i);
  }

  // Parameters

  // Functions

  // Callbacks
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