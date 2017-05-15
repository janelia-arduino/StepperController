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

## API

```json
{
  "id":"getApi",
  "result":{
    "firmware":["StepperController"],
    "functions":[
      "minimizeCurrent",
      "restoreCurrent"
    ],
    "parameters":[],
    "properties":[
      "currentScale",
      "microstepsPerStep"
    ],
    "callbacks":[]
  }
}
```

## API Verbose

```json
{
  "id":"getApiVerbose",
  "result":{
    "firmware":["StepperController"],
    "functions":[
      {
        "name":"minimizeCurrent",
        "parameters":[
          "channel"
        ]
      },
      {
        "name":"restoreCurrent",
        "parameters":[
          "channel"
        ]
      }
    ],
    "parameters":[],
    "properties":[
      {
        "name":"currentScale",
        "type":"array",
        "array_element_type":"long",
        "units":"%",
        "functions":[
          "getValue",
          "setValue",
          "getDefaultValue",
          "setValueToDefault",
          "getElementValue",
          "setElementValue",
          "getDefaultElementValue",
          "setElementValueToDefault",
          "setAllElementValues",
          "getArrayLength",
          "setArrayLength"
        ],
        "parameters":[
          "value",
          "element_index",
          "element_value",
          "array_length"
        ]
      },
      {
        "name":"microstepsPerStep",
        "type":"array",
        "array_element_type":"long",
        "functions":[
          "getValue",
          "setValue",
          "getDefaultValue",
          "setValueToDefault",
          "getElementValue",
          "setElementValue",
          "getDefaultElementValue",
          "setElementValueToDefault",
          "setAllElementValues",
          "getArrayLength",
          "setArrayLength"
        ],
        "parameters":[
          "value",
          "element_index",
          "element_value",
          "array_length"
        ]
      }
    ],
    "callbacks":[]
  }
}
```

## More Detailed Modular Device Information

[modular-devices](https://github.com/janelia-modular-devices/modular-devices)

## Install Library Dependencies

[arduino-libraries](https://github.com/janelia-arduino/arduino-libraries)
