// ----------------------------------------------------------------------------
// 3x2.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "3x2.h"


#if defined(__MK20DX256__)

namespace stepper_controller
{
namespace constants
{
const size_t cs_pins[TMC26X_COUNT] = {9,8,7};

// Interrupts

// Units

// Properties
const long current_scale_default[TMC26X_COUNT] =
  {
    20,
    20,
    20
  };

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
