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

#include "SPI.h"
#include "TMC429.h"
#include "TMC26X.h"

#include "ModularServer.h"
#include "ModularDevice.h"
#include "StepDirController.h"

#include "utility/Constants.h"


class StepperController : public StepDirController
{
public:
  StepperController();
  virtual void setup();

private:
  modular_server::Property properties_[stepper_controller::constants::PROPERTY_COUNT_MAX];
  modular_server::Parameter parameters_[stepper_controller::constants::PARAMETER_COUNT_MAX];
  modular_server::Function functions_[stepper_controller::constants::FUNCTION_COUNT_MAX];
  modular_server::Callback callbacks_[stepper_controller::constants::CALLBACK_COUNT_MAX];

  TMC26X tmc26xs_[stepper_controller::constants::TMC26X_COUNT];

  // Handlers
  void setCurrentScaleHandler(const size_t driver);

};

#endif
