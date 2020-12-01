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
#ifndef CROS_KERNEL_H
#define CROS_KERNEL_H

#include "Arduino.h"
#include "Servo.h"
#include "constants.h"

namespace CrOS {
  enum event {
    PERCH_ACTIVATED,
    PERCH_DEACTIVATED,
    COIN_ACTIVATED
  };

  void Log(const char *message);

  void Shutdown(const char *message);

  static unsigned char currentTrainingPhase = 1;

  void InterruptHandler();

  static unsigned long lastInterruptUptime;
  static bool pendingInterruptEvent = false;

  class Kernel {
  public:
    Kernel();

    void Register(void (*handler)(const event));

    void Boot();

    void Loop();

    void Reward();

    void NextTrainingPhase();

  private:
    void (*m_eventHandlers[32])(const event);
    unsigned char m_eventHandlersLen = -1;

    const Servo m_servo;
    unsigned long m_servoDetachAtUptime = 0;
    unsigned long m_initCloseBasketAt = 0;
    unsigned char m_lidPosition = 0;

    bool m_perchActive = false;

    void ProcessEvent(const event eventName);

    bool InputFrom(const unsigned char pin, const bool waitForRelease = false);

    void SetLidPosition(const unsigned char percent);

    void BlinkLED(const unsigned char numTimes = 1);
  };
}

#endif // CROS_KERNEL_H
