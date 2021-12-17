// ----------------------------------------------------------------------------
// TEENSY41.h
//
//
// Authors:
// Peter Polidoro peter@polidoro.io
// ----------------------------------------------------------------------------
#ifndef STEP_DIR_CONTROLLER_TEENSY41_CONSTANTS_H
#define STEP_DIR_CONTROLLER_TEENSY41_CONSTANTS_H
#include "Constants.h"


#if defined(__IMXRT1062__) && defined(ARDUINO_TEENSY41)
namespace step_dir_controller
{
namespace constants
{
//MAX values must be >= 1, >= created/copied count, < RAM limit
enum{PIN_COUNT_MAX=1};

enum {CONTROLLER_COUNT_MAX=1};
enum {CHANNEL_COUNT_MAX=CONTROLLER_COUNT_MAX*CHANNELS_PER_CONTROLLER_COUNT};

extern const size_t chip_select_pins[CONTROLLER_COUNT_MAX];
extern const size_t enable_pins[CHANNEL_COUNT_MAX];

// Units

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]
extern const long steps_per_position_units_default[CHANNEL_COUNT_MAX];

extern const long velocity_max_default[CHANNEL_COUNT_MAX];

extern const long velocity_min_default[CHANNEL_COUNT_MAX];

extern const long acceleration_max_default[CHANNEL_COUNT_MAX];

extern const ConstantString * const enable_polarity_default[CHANNEL_COUNT_MAX];

extern const bool step_polarity_inverted_default[CONTROLLER_COUNT_MAX];

extern const bool dir_polarity_inverted_default[CONTROLLER_COUNT_MAX];

extern const ConstantString * const switch_active_polarity_default[CONTROLLER_COUNT_MAX];

extern const bool right_switches_enabled_default[CONTROLLER_COUNT_MAX];

extern const bool left_switch_stop_enabled_default[CHANNEL_COUNT_MAX];

extern const bool right_switch_stop_enabled_default[CHANNEL_COUNT_MAX];

extern const bool switch_soft_stop_enabled_default[CHANNEL_COUNT_MAX];

extern const long home_velocity_default[CHANNEL_COUNT_MAX];

// Parameters

// Functions

// Callbacks

// Errors
}
}

#endif
#endif
