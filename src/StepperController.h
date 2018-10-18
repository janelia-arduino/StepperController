// ----------------------------------------------------------------------------
// StepperController.h
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#ifndef STEPPER_CONTROLLER_H
#define STEPPER_CONTROLLER_H
#include <ArduinoJson.h>
#include <JsonStream.h>
#include <Array.h>
#include <Vector.h>
#include <ConstantVariable.h>
#include <Functor.h>

#include <TMC2130.h>

#include <ModularServer.h>
#include <ModularDeviceBase.h>
#include <StepDirController.h>

#include "StepperController/Constants.h"


class StepperController : public StepDirController
{
public:
  StepperController();
  virtual void setup();

  virtual void reinitialize();

  virtual size_t getChannelCount();

  void enableAutomaticCurrentScaling(size_t channel);
  void disableAutomaticCurrentScaling(size_t channel);

  void zeroHoldCurrent(size_t channel);
  void maximizeHoldCurrent(size_t channel);
  void modifyHoldCurrent(size_t channel,
    uint8_t current);
  void restoreHoldCurrent(size_t channel);

  void modifyRunCurrent(size_t channel,
    uint8_t current);
  void restoreRunCurrent(size_t channel);

  void setPwmOffset(size_t channel,
    uint8_t pwm_amplitude);
  void setPwmGradient(size_t channel,
    uint8_t pwm_amplitude);
  uint8_t getPwmScale(size_t channel);

protected:
  virtual size_t getDriverChipSelectPin(size_t driver);
  // Handlers
  void setChannelCountHandler();

private:
  modular_server::Pin pins_[stepper_controller::constants::PIN_COUNT_MAX];

  modular_server::Property properties_[stepper_controller::constants::PROPERTY_COUNT_MAX];
  modular_server::Parameter parameters_[stepper_controller::constants::PARAMETER_COUNT_MAX];
  modular_server::Function functions_[stepper_controller::constants::FUNCTION_COUNT_MAX];
  modular_server::Callback callbacks_[stepper_controller::constants::CALLBACK_COUNT_MAX];

  typedef TMC2130 Driver;
  Driver drivers_[stepper_controller::constants::CHANNEL_COUNT_MAX];

  // Handlers
  void invertDriverDirectionHandler(size_t channel);
  void setRunCurrentHandler(size_t channel);
  void setHoldCurrentHandler(size_t channel);
  void setHoldDelayHandler(size_t channel);
  void preSetMicrostepsPerStepHandler(size_t channel);
  void postSetMicrostepsPerStepHandler(size_t channel);
  void setMicrostepsPerStepHandler(size_t channel);
  void setZeroHoldCurrentModeHandler(size_t channel);
  void getDriversStatusHandler();
  void getDriversSettingsHandler();
  void enableAutomaticCurrentScalingHandler();
  void disableAutomaticCurrentScalingHandler();
  void zeroHoldCurrentHandler();
  void maximizeHoldCurrentHandler();
  void modifyHoldCurrentHandler();
  void restoreHoldCurrentHandler();
  void modifyRunCurrentHandler();
  void restoreRunCurrentHandler();
  void setPwmOffsetHandler();
  void setPwmGradientHandler();
  void getPwmScalesHandler();

};

#endif
