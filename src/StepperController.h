// ----------------------------------------------------------------------------
// StepperController.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
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

  void enableAutomaticCurrentScaling(const size_t channel);
  void disableAutomaticCurrentScaling(const size_t channel);

  void zeroHoldCurrent(const size_t channel);
  void maximizeHoldCurrent(const size_t channel);
  void restoreHoldCurrent(const size_t channel);

  void setPwmOffset(const size_t channel,
                    const uint8_t pwm_amplitude);
  void setPwmGradient(const size_t channel,
                      const uint8_t pwm_amplitude);
  uint8_t getPwmScale(const size_t channel);

protected:
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
  void invertDriverDirectionHandler(const size_t channel);
  void setRunCurrentHandler(const size_t channel);
  void setHoldCurrentHandler(const size_t channel);
  void setHoldDelayHandler(const size_t channel);
  void preSetMicrostepsPerStepHandler(const size_t channel);
  void postSetMicrostepsPerStepHandler(const size_t channel);
  void setMicrostepsPerStepHandler(const size_t channel);
  void setZeroHoldCurrentModeHandler(const size_t channel);
  void getDriversStatusHandler();
  void getDriversSettingsHandler();
  void enableAutomaticCurrentScalingHandler();
  void disableAutomaticCurrentScalingHandler();
  void zeroHoldCurrentHandler();
  void maximizeHoldCurrentHandler();
  void restoreHoldCurrentHandler();
  void setPwmOffsetHandler();
  void setPwmGradientHandler();
  void getPwmScalesHandler();

};

#endif
