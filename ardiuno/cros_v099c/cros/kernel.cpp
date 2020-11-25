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
#include <EEPROM.h>
#include "kernel.h"

namespace CrOS {
  void Log(const char *message) {
#if defined(CROS_SERIAL_BAUD_RATE)
    if (!Serial.available()) Serial.begin(CROS_SERIAL_BAUD_RATE);

    Serial.print("CrOS: ");
    Serial.println(message);
#endif // CROS_SERIAL_BAUD_RATE
  }

  void InterruptHandler() {
    const unsigned long uptime = millis();
    if (lastInterruptUptime > uptime - 1000) return;

    lastInterruptUptime = uptime;
    pendingInterruptEvent = true;
  }

  void Shutdown(const char *message) {
    Log(message);
    Log("Shutting down...");
    while (true) {};
  }

  Kernel::Kernel() {}

  void Kernel::Register(void (*handler)(event eventName)) {
    m_eventHandlers[++m_eventHandlersLen] = handler;
  }

  void Kernel::Boot() {
    Log("Booting up...");

    // Setup the pin modes.
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(CROS_INPUT_PIN_PERCH, INPUT_PULLUP);
    pinMode(CROS_INPUT_PIN_COIN, INPUT_PULLUP);
    pinMode(CROS_INPUT_PIN_TRAINING_PHASE, INPUT_PULLUP);

    // Initialize the servo.
    Log("Initializing basket servo...");
    SetLidPosition(50);
    delay(800);
    SetLidPosition(0);

    // Load the training phase from the EEPROM or default it.
    currentTrainingPhase = EEPROM.read(CROS_EEPROM_ADDRESS_TRAINING_PHASE);
    if (currentTrainingPhase < 1 || currentTrainingPhase > 4) currentTrainingPhase = 1;

    char message[100];
    sprintf(message, "Initializing training phase %i.", currentTrainingPhase);
    Log(message);

    // Register the interrupt.
    attachInterrupt(digitalPinToInterrupt(CROS_INPUT_PIN_COIN), InterruptHandler, FALLING);
    Log("Coin interrupt registered.");

    // Blink the LED to indicate the current training phase.
    BlinkLED(currentTrainingPhase);

    // Close the lid if we should.
    if (currentTrainingPhase != 1) m_initCloseBasketAt = 5000;
  }

  void Kernel::Loop() {
    const unsigned long uptime = millis();

    if (pendingInterruptEvent) {
      // Handle coin events.
      ProcessEvent(COIN_ACTIVATED);

      pendingInterruptEvent = false;
    } else {
      // Handle perch events.
      const bool perchActive = InputFrom(CROS_INPUT_PIN_PERCH);

      if (!m_perchActive && perchActive) ProcessEvent(PERCH_ACTIVATED);
      else if (m_perchActive && !perchActive) ProcessEvent(PERCH_DEACTIVATED);

      m_perchActive = perchActive;
    }

    // Handle the training phase cycle button.
    if (InputFrom(CROS_INPUT_PIN_TRAINING_PHASE, true)) NextTrainingPhase();

    // Close the lid in steps.
    if (m_initCloseBasketAt > 0 && m_initCloseBasketAt < uptime) {
      SetLidPosition(m_lidPosition + 10);
      if (m_lidPosition >= 100) m_initCloseBasketAt = 0;
      else m_initCloseBasketAt = uptime + CROS_BASKET_CLOSE_STEP_DURATION;
    }

    // Detach the servo if we need to.
    if (m_servoDetachAtUptime > 0 && m_servoDetachAtUptime < uptime) {
      m_servo.detach();
      m_servoDetachAtUptime = 0;
    }

    unsigned long duration = millis() - uptime;
    if (duration < 20) delay(20 - duration);
  }

  void Kernel::Reward() {
    SetLidPosition(0);

    // TODO: We're not bothering to handle multiple coins at this point.

    m_initCloseBasketAt = millis() + CROS_BASKET_REWARD_DURATION;
  };

  void Kernel::NextTrainingPhase() {
    if (++currentTrainingPhase > 4) currentTrainingPhase = 1;

    // Save the training phase in EEPROM.
    EEPROM.write(CROS_EEPROM_ADDRESS_TRAINING_PHASE, currentTrainingPhase);

    // Reset the device.
    delay(250);
    pinMode(CROS_OUTPUT_PIN_RESET, OUTPUT);
  }

  void Kernel::ProcessEvent(event eventName) {
    switch (eventName) {
      case COIN_ACTIVATED:
        Log("Event: COIN_ACTIVATED");
        if (currentTrainingPhase > 2) Reward();
        break;
      case PERCH_ACTIVATED:
        Log("Event: PERCH_ACTIVATED");
        if (currentTrainingPhase == 2) Reward();
        break;
      case PERCH_DEACTIVATED:
        Log("Event: PERCH_DEACTIVATED");
        break;
    }
  
    for (unsigned char i = 0; i <= m_eventHandlersLen; ++i) m_eventHandlers[i](eventName);
  }  

  bool Kernel::InputFrom(const unsigned char pin, const bool waitForRelease = false) {
    if (digitalRead(pin) != LOW) return false;

    if (waitForRelease) while (digitalRead(pin) == LOW) delay(50);
    return true;
  }

  void Kernel::SetLidPosition(unsigned char percent) {
    if (percent > 100) percent = 100;

    m_servo.attach(CROS_OUTPUT_PIN_SERVO);
    m_servo.write(percent / 100.0 * 179);

    m_lidPosition = percent;
    m_servoDetachAtUptime = millis() + 2000;
  }

  void Kernel::BlinkLED(const unsigned char numTimes = 1) {
    for (unsigned char i = 0; i < numTimes; ++i) {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(250);

      digitalWrite(LED_BUILTIN, LOW);
      delay(250);
    }
  }
}
