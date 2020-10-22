//==========================================================
// cros.ino
//
// The 'kernel' of the CrOS is called "The Core"
// 
// Version 0.99c - October 2018
//
// http://www.thecrowbox.com
//==========================================================
//   Except where otherwise noted, this work is licensed 
//   under a Creative Commons Attribution-ShareAlike 4.0 
//   International License
//==========================================================
#include "cros_core.h"
#include "cros_constants.h"
#include "cros_types.h"

//======================================
// Allocate the core object right here 
// on the heap so that the Arduino IDE 
// is more correct about how much memory
// the CrOS software when this is reported
// after a successful compile
//======================================
CCrowboxCore g_crOSCore;


//======================================
// Called by the Arduino system one time,
// after the board boots up. CrOS hooks
// to this to call the core's Setup()
// method
//======================================
void setup() 
{
    // Run-Once
    g_crOSCore.Setup(); 
}

//======================================
// Called as often as possible by the
// Arduino system. CrOS hooks to this 
// in order to call the core's Loop()
// method
//======================================
void loop()
{
    // Continuous Run
    g_crOSCore.Loop();
}

