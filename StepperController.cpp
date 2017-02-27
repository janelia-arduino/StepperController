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

  // Variable Setup
  flipping_ = false;
  flip_enabled_ = true;

  // Pin Setup
  for (int digital_input=0; digital_input<constants::DIGITAL_INPUT_COUNT; ++digital_input)
  {
    pinMode(constants::di_pins[digital_input],INPUT_PULLUP);
  }

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
  modular_server_.property(h_bridge_controller::constants::polarity_reversed_property_name).setDefaultValue(constants::polarity_reversed_default);

  modular_server_.property(h_bridge_controller::constants::channels_enabled_property_name).setDefaultValue(constants::channels_enabled_default);

  modular_server::Property & flipper_delay_property = modular_server_.createProperty(constants::flipper_delay_property_name,constants::flipper_delay_default);
  flipper_delay_property.setRange(constants::flipper_delay_min,constants::flipper_delay_max);
  flipper_delay_property.setUnits(h_bridge_controller::constants::ms_unit);

  modular_server::Property & flipper_period_property = modular_server_.createProperty(constants::flipper_period_property_name,constants::flipper_period_default);
  flipper_period_property.setRange(constants::flipper_period_min,constants::flipper_period_max);
  flipper_period_property.setUnits(h_bridge_controller::constants::ms_unit);

  modular_server::Property & flipper_on_duration_property = modular_server_.createProperty(constants::flipper_on_duration_property_name,constants::flipper_on_duration_default);
  flipper_on_duration_property.setRange(constants::flipper_on_duration_min,constants::flipper_on_duration_max);
  flipper_on_duration_property.setUnits(h_bridge_controller::constants::ms_unit);

  modular_server::Property & rung_up_count_lower_property = modular_server_.createProperty(constants::rung_up_count_lower_property_name,constants::rung_up_count_lower_default);
  rung_up_count_lower_property.setRange(constants::rung_count_min,constants::rung_count_max);

  modular_server::Property & rung_up_count_upper_property = modular_server_.createProperty(constants::rung_up_count_upper_property_name,constants::rung_up_count_upper_default);
  rung_up_count_upper_property.setRange(constants::rung_count_min,constants::rung_count_max);

  modular_server::Property & rung_down_count_property = modular_server_.createProperty(constants::rung_down_count_property_name,constants::rung_down_count_default);
  rung_down_count_property.setRange(constants::rung_count_min,constants::rung_count_max);

  // Parameters

  // Functions
  modular_server::Function & flip_enabled_function = modular_server_.createFunction(constants::flip_enabled_function_name);
  flip_enabled_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepperController::flipEnabledHandler));
  flip_enabled_function.setReturnTypeBool();

  // Callbacks
  modular_server::Callback & flip_callback = modular_server_.createCallback(constants::flip_callback_name);
  flip_callback.attachFunctor(makeFunctor((Functor1<modular_server::Interrupt *> *)0,*this,&StepperController::flipHandler));
  flip_callback.addProperty(rung_up_count_lower_property);
  flip_callback.addProperty(rung_up_count_upper_property);
  flip_callback.addProperty(rung_down_count_property);
#if defined(__AVR_ATmega2560__)
  flip_callback.attachTo(h_bridge_controller::constants::switch_0_interrupt_name,modular_server::interrupt::mode_falling);
#endif

  // modular_server::Callback & enable_flip_callback = modular_server_.createCallback(constants::enable_flip_callback_name);
  // enable_flip_callback.attachFunctor(makeFunctor((Functor1<modular_server::Interrupt *> *)0,*this,&StepperController::enableFlipHandler));

  // modular_server::Callback & disable_flip_callback = modular_server_.createCallback(constants::disable_flip_callback_name);
  // disable_flip_callback.attachFunctor(makeFunctor((Functor1<modular_server::Interrupt *> *)0,*this,&StepperController::disableFlipHandler));

}

void StepperController::update()
{
  // Parent Update
  StepDirController::update();

  bool enable = (digitalRead(constants::di_pins[constants::ENABLE_DISABLE_INPUT]) == HIGH);
  if (enable)
  {
    enableFlipHandler(NULL);
  }
  else
  {
    disableFlipHandler(NULL);
  }
}

void StepperController::flip(const ConstantString & polarity)
{
  if (!flipping_ && flip_enabled_)
  {
    flipping_ = true;
    long flipper_delay;
    modular_server_.property(constants::flipper_delay_property_name).getValue(flipper_delay);
    long flipper_period;
    modular_server_.property(constants::flipper_period_property_name).getValue(flipper_period);
    long flipper_on_duration;
    modular_server_.property(constants::flipper_on_duration_property_name).getValue(flipper_on_duration);
    addPwm(constants::flipper_channels,
           polarity,
           flipper_delay,
           flipper_period,
           flipper_on_duration,
           1);
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

void StepperController::stopPwmHandler(int index)
{
  StepDirController::stopPwmHandler(index);
  flipping_ = false;
}

void StepperController::flipEnabledHandler()
{
  modular_server_.response().returnResult(flip_enabled_);
}

void StepperController::enableFlipHandler(modular_server::Interrupt * interrupt_ptr)
{
  if (!flip_enabled_)
  {
    noInterrupts();
    flip_enabled_ = true;
    interrupts();
  }
}

void StepperController::disableFlipHandler(modular_server::Interrupt * interrupt_ptr)
{
  if (flip_enabled_)
  {
    noInterrupts();
    flip_enabled_ = false;
    interrupts();
  }
}

void StepperController::flipHandler(modular_server::Interrupt * interrupt_ptr)
{
  if (!flipping_ && flip_enabled_)
  {
    long rung_up_count_lower;
    modular_server_.property(constants::rung_up_count_lower_property_name).getValue(rung_up_count_lower);
    long rung_up_count_upper;
    modular_server_.property(constants::rung_up_count_upper_property_name).getValue(rung_up_count_upper);
    long rung_down_count;
    modular_server_.property(constants::rung_down_count_property_name).getValue(rung_down_count);
    if (flipper_is_up_ && (flipper_up_inc_ == flipper_up_count_))
    {
      if (rung_down_count > 0)
      {
        flipper_is_up_ = false;
      }
      flipper_up_inc_ = 0;
    }
    else if (!flipper_is_up_ && (flipper_down_inc_ == rung_down_count))
    {
      if (rung_up_count_upper > 0)
      {
        flipper_is_up_ = true;
        flipper_up_count_ = random(rung_up_count_lower,rung_up_count_upper);
      }
      flipper_down_inc_ = 0;
    }
    if (flipper_is_up_ && (flipper_up_inc_ < flipper_up_count_))
    {
      flip(*constants::polarity_up_ptr);
      ++flipper_up_inc_;
    }
    else if (!flipper_is_up_ && (flipper_down_inc_ < rung_down_count))
    {
      flip(*constants::polarity_down_ptr);
      ++flipper_down_inc_;
    }
  }
}
