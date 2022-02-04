// ----------------------------------------------------------------------------
// StepperController.h
//
//
// Authors:
// Peter Polidoro peter@polidoro.io
// ----------------------------------------------------------------------------
#ifndef STEPPER_CONTROLLER_H
#define STEPPER_CONTROLLER_H
#include <ArduinoJson.h>
#include <JsonStream.h>
#include <Array.h>
#include <Vector.h>
#include <ConstantVariable.h>
#include <Functor.h>

#include <TMC2209.h>

#include <ModularServer.h>
#include <ModularDeviceBase.h>
#include <StepDirController.h>

#include "StepperController/Constants.h"


class StepperController : public StepDirController
{
public:
  virtual void setup();
  virtual void update();

  virtual void reinitialize();

  virtual size_t getChannelCount();

  virtual void enable(size_t channel);
  virtual void disable(size_t channel);

  void standstill(size_t channel);
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

protected:
  virtual HardwareSerial & getDriverSerial(size_t driver);
  virtual void setupDriver(size_t channel);
  virtual void shutdownDriver(size_t channel);
  virtual void reinitializeDriver(size_t channel);

  // Handlers
  void setChannelCountHandler();

private:
  modular_server::Pin pins_[stepper_controller::constants::PIN_COUNT_MAX];

  modular_server::Property properties_[stepper_controller::constants::PROPERTY_COUNT_MAX];
  modular_server::Parameter parameters_[stepper_controller::constants::PARAMETER_COUNT_MAX];
  modular_server::Function functions_[stepper_controller::constants::FUNCTION_COUNT_MAX];
  modular_server::Callback callbacks_[stepper_controller::constants::CALLBACK_COUNT_MAX];

  typedef TMC2209 Driver;
  Driver drivers_[stepper_controller::constants::CHANNEL_COUNT_MAX];
  unsigned long check_drivers_time_;

  // Handlers
  void invertDriverDirectionHandler(size_t channel);
  void setRunCurrentHandler(size_t channel);
  void setHoldCurrentHandler(size_t channel);
  void setHoldDelayHandler(size_t channel);
  void preSetMicrostepsPerStepHandler(size_t channel);
  void postSetMicrostepsPerStepHandler(size_t channel);
  void setMicrostepsPerStepHandler(size_t channel);
  void setStandstillModeHandler(size_t channel);
  void automaticCurrentScalingHandler(size_t channel);
  void automaticGradientAdaptationHandler(size_t channel);
  void coolStepDurationThresholdHandler(size_t channel);
  void coolStepCurrentIncrementHandler(size_t channel);
  void coolStepMeasurementCountHandler(size_t channel);
  void coolStepEnabledHandler(size_t channel);
  void getDriversStatusHandler();
  void getDriversSettingsHandler();
  void getDriversMeasurementsHandler();
  void standstillHandler();
  void maximizeHoldCurrentHandler();
  void modifyHoldCurrentHandler();
  void restoreHoldCurrentHandler();
  void modifyRunCurrentHandler();
  void restoreRunCurrentHandler();
  void setPwmOffsetHandler();
  void setPwmGradientHandler();

};

#endif
