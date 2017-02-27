// ----------------------------------------------------------------------------
// StepperController.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef STEPPER_CONTROLLER_H
#define STEPPER_CONTROLLER_H
#include "Flash.h"
#include <EEPROM.h>
#include "Streaming.h"
#include "ArduinoJson.h"
#include "JsonSanitizer.h"
#include "JsonStream.h"
#include "Array.h"
#include "Vector.h"
#include "MemoryFree.h"
#include "ConstantVariable.h"
#include "SavedVariable.h"
#include "Functor.h"
#include "IndexedContainer.h"
#include "FunctorCallbacks.h"

#include "ModularServer.h"
#include "ModularDevice.h"
#include "StepDirController.h"

#include "utility/Constants.h"


class StepperController : public StepDirController
{
public:
  StepperController();
  virtual void setup();
  virtual void update();
  void flip(const ConstantString & polarity);

  // Handlers
  virtual void stopPwmHandler(int index);

private:
  modular_server::Property properties_[stepper_controller::constants::PROPERTY_COUNT_MAX];
  modular_server::Parameter parameters_[stepper_controller::constants::PARAMETER_COUNT_MAX];
  modular_server::Function functions_[stepper_controller::constants::FUNCTION_COUNT_MAX];
  modular_server::Callback callbacks_[stepper_controller::constants::CALLBACK_COUNT_MAX];

  volatile bool flipping_;
  volatile bool flip_enabled_;
  volatile long flipper_up_inc_;
  volatile long flipper_down_inc_;
  volatile bool flipper_is_up_;
  volatile long flipper_up_count_;

  // Handlers
  void flipEnabledHandler();
  void enableFlipHandler(modular_server::Interrupt * interrupt_ptr);
  void disableFlipHandler(modular_server::Interrupt * interrupt_ptr);
  void flipHandler(modular_server::Interrupt * interrupt_ptr);

};

#endif
