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
#include "TMC2130.h"

#include "ModularClient.h"

#include "ModularServer.h"
#include "ModularDeviceBase.h"
#include "StepDirController.h"

#include "utility/Constants.h"


class StepperController : public StepDirController
{
public:
  StepperController();
  virtual void setup();

  virtual void reinitialize();

  virtual size_t getChannelCount();

  void enableAutomaticCurrentScaling(const size_t channel);
  void disableAutomaticCurrentScaling(const size_t channel);
  void setPwmOffset(const size_t channel,
                    const uint8_t percent);
  void setPwmGradient(const size_t channel,
                      const uint8_t percent);

  void zeroHoldCurrent(const size_t channel);
  void restoreHoldCurrent(const size_t channel);

  void setZeroHoldCurrentOperation(const size_t channel,
                                   const TMC2130::ZeroHoldCurrentOperation operation);

protected:
  // Handlers
  void setChannelCountHandler();

private:
  modular_server::Interrupt interrupts_[stepper_controller::constants::INTERRUPT_COUNT_MAX];

  modular_server::Property properties_[stepper_controller::constants::PROPERTY_COUNT_MAX];
  modular_server::Parameter parameters_[stepper_controller::constants::PARAMETER_COUNT_MAX];
  modular_server::Function functions_[stepper_controller::constants::FUNCTION_COUNT_MAX];
  modular_server::Callback callbacks_[stepper_controller::constants::CALLBACK_COUNT_MAX];

  typedef TMC2130 Driver;
  Driver drivers_[stepper_controller::constants::CHANNEL_COUNT_MAX];

  // Handlers
  void invertDriverDirectionHandler(const size_t channel);
  void setRunCurrentHandler(const size_t channel);
  void setHoldCurrentHandler(const size_t channel);
  void setHoldDelayHandler(const size_t channel);
  void preSetMicrostepsPerStepHandler(const size_t channel);
  void postSetMicrostepsPerStepHandler(const size_t channel);
  void setMicrostepsPerStepHandler(const size_t channel);
  void getDriversStatusHandler();
  void getDriversSettingsHandler();
  void enableAutomaticCurrentScalingHandler();
  void disableAutomaticCurrentScalingHandler();
  void setPwmOffsetHandler();
  void setPwmGradientHandler();
  void setZeroHoldCurrentOperationHandler();
  void zeroHoldCurrentHandler();
  void restoreHoldCurrentHandler();

};

#endif
