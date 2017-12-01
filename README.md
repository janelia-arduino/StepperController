# StepperController

Authors:

    Peter Polidoro <polidorop@janelia.hhmi.org>

License:

    BSD

## Ancestors

[ModularServer](https://github.com/janelia-arduino/ModularServer)

[ModularDeviceBase](https://github.com/janelia-arduino/ModularDeviceBase)

[StepDirController](https://github.com/janelia-arduino/StepDirController)

## Clients

## Devices

[modular_device_base](https://github.com/janelia-modular-devices/modular_device_base.git)

[stepper_controller](https://github.com/janelia-modular-devices/stepper_controller.git)

## API NAMES

```json
{
  "id": "getApi",
  "result": {
    "firmware": [
      "StepperController"
    ],
    "verbosity": "NAMES",
    "functions": [
      "getDriversStatus",
      "getDriversSettings",
      "enableAutomaticCurrentScaling",
      "disableAutomaticCurrentScaling",
      "zeroHoldCurrent",
      "restoreHoldCurrent",
      "setPwmOffset",
      "setPwmGradient",
      "getPwmScales"
    ],
    "parameters": [
      "pwm_amplitude"
    ],
    "properties": [
      "invertDriverDirection",
      "runCurrent",
      "holdCurrent",
      "holdDelay",
      "microstepsPerStep",
      "zeroHoldCurrentMode"
    ]
  }
}
```

## API GENERAL

[API GENERAL](./api/)

## More Detailed Modular Device Information

[modular-devices](https://github.com/janelia-modular-devices/modular-devices)

## Install Library Dependencies

[arduino-libraries](https://github.com/janelia-arduino/arduino-libraries)
