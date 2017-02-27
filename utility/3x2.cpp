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
const size_t di_pins[DIGITAL_INPUT_COUNT] = {2};

// Interrupts

// Units

// Properties
const bool polarity_reversed_default[h_bridge_controller::constants::CHANNEL_COUNT] = {false,true};

const bool channels_enabled_default[h_bridge_controller::constants::CHANNEL_COUNT] = {true,true};


// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
