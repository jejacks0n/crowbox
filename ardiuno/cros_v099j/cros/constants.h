//=============================================================================
// The CrowBoxOS (CrOS)
//
// Unofficial Version ~0.99j - December 2020
//
// http://www.thecrowbox.com
//=============================================================================
// Except where otherwise noted, this work is licensed under a Creative Commons
// Attribution-ShareAlike 4.0 International License.
//=============================================================================
#ifndef CROS_CONSTANTS_H
#define CROS_CONSTANTS_H

// Settings for serial communications. This is used for debug text-based error
// and status messages in the serial monitor / console.
//
// CROS_SERIAL_BAUD_RATE should be #undef when compiling for a CrowBox that's
// going to be deployed -- for performance and optimization reasons.
#undef CROS_SERIAL_BAUD_RATE
#define CROS_SERIAL_BAUD_RATE 9600

// Pin apportioning. The following assumes an Arduino board, and these may need
// to be changed when porting this code to run on another board type, or when
// changing wiring.
//
// The PERCH and COIN pins must support interrupts.
#define CROS_INPUT_PIN_PERCH 2
#define CROS_INPUT_PIN_COIN 3
#define CROS_INPUT_PIN_TRAINING_PHASE 4
#define CROS_OUTPUT_PIN_SERVO 9
#define CROS_OUTPUT_PIN_RESET 10

// Constants used to store the CrOS data in the EEPROM so that it will be
// remembered on restarts.
#define CROS_EEPROM_ADDRESS_TRAINING_PHASE 0

// Basket and servo behavior. These define an important safety feature which
// closes the lid slowly in a series of small steps. This ensures visitors have
// plenty of time before there's any danger of getting one of their parts caught.
//
// Think carefully before changing these.
#define CROS_BASKET_REWARD_DURATION 15000
#define CROS_BASKET_CLOSE_STEP_DURATION 1500

//=============================================================================
// Wifi support...
//=============================================================================
#undef CROS_NETWORK_SSID
#define CROS_NETWORK_SSID ""
#define CROS_NETWORK_PASS ""
#define CROS_API_HOST ""
#define CROS_API_TOKEN ""
#define CROS_API_REQUEST "HEAD /log_event?type=%i&token=%s HTTP/1.1\nHost: %s\nConnection: close\n\n"

#endif // CROS_CONSTANTS_H
