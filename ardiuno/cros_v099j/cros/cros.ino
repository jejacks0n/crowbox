//=============================================================================
// The CrowBoxOS (CrOS)
//
// Unofficial Version ~1.0a - December 2020
//
// http://www.thecrowbox.com
//
// Phase One: "Discovery & Free Feeding"
//
//   - NO coins are provided
//
//   - Reward basket is always open with morsels freely available
//   - Perch activations are tracked but don't trigger the reward strategy
//   - Coin activations are tracked but don't trigger the reward strategy
//
// Phase Two: "Reward on Arrival"
//
//   - NO coins are provided
//
//   - Reward basket is closed with morsels briefly provided as reward strategy
//   - Perch activation instantly triggers the reward strategy
//   - Coin activation instantly triggers the reward strategy (incidentally)
//
// Phase Three: "Reward on deposit, coins provided"
//
//   - Training coins ARE provided
//
//   - Reward basket is closed with morsels briefly provided as reward strategy
//   - Perch activations are tracked but don't trigger the reward strategy
//   - Coin activation instantly triggers the reward strategy
//
//   NOTES: In this phase the machine dispenses the provided training coins
//   onto the basket lid so that birds may discover and manipulate them until
//   they discover how to use coins to receive rewards.
//
// Phase Four: "Reward on deposit"
//
//   - NO coins are provided
//
//   - Reward basket is closed with morsels briefly provided as reward strategy
//   - Perch activations are tracked but don't trigger the reward strategy
//   - Coin activation instantly triggers the reward strategy
//
//   NOTES: Phase Three and Four are the same, but the birds must locate and
//   deposit their own coins since none are provided. This is the ideal steady
//   operating state for an urban CrowBox.
//
//=============================================================================
// Except where otherwise noted, this work is licensed under a Creative Commons
// Attribution-ShareAlike 4.0 International License.
//=============================================================================
#include <SPI.h>
#include <WiFiNINA.h>
#include "kernel.h"

// Allocate the CrOS Kernel on the heap so the Arduino IDE can be more accurate
// in reporting how much memory is being used after a successful compile.
CrOS::Kernel kernel;
unsigned long lastConnectionAttemptAt = 0;

// Called once by the Arduino system, after initial boot up or when the sketch
// is uploaded. We pass through to the CrOS Kernel setup method.
void setup() {
  kernel.Boot();

#if defined(CROS_NETWORK_SSID)
  // Make sure we can connect.
  if (WiFi.status() == WL_NO_MODULE) CrOS::Shutdown("Error: no WiFi module found.");

  kernel.Register([](CrOS::event eventType) {
    if (WiFi.status() != WL_CONNECTED) return;

    WiFiClient client;
    if (client.connect(CROS_API_HOST, 80)) {
      char data[255];
      sprintf(data, CROS_API_REQUEST, eventType, CROS_API_TOKEN, CROS_API_HOST);
      client.println(data);
      client.println();

      delay(100);
      while (client.available()) { char c = client.read(); }
      client.stop();
    } else {
      char message[100];
      sprintf(message, "Error: no connection to %s.", CROS_API_HOST);
      CrOS::Log(message);
    }
  });
#endif // CROS_NETWORK_SSID
}

// Called continuously by the Arduino system. Allow the CrOS Kernel to process
// its loop here.
void loop() {
  kernel.Loop();

#if defined(CROS_NETWORK_SSID)
  int status = WiFi.status();
  if (lastConnectionAttemptAt == 0 && status != WL_CONNECTED) {
    lastConnectionAttemptAt = millis();
    connect();
  } else if (lastConnectionAttemptAt != 0) {
    if (status == WL_CONNECTED) {
      lastConnectionAttemptAt = 0;
      CrOS::Log("Connected.");
    } else if (lastConnectionAttemptAt < millis() + 5000) {
      lastConnectionAttemptAt = millis();
      connect();
    }
  }
#endif // CROS_NETWORK_SSID
}

void connect() {
  char message[100];
  sprintf(message, "Connecting to the %s network...", CROS_NETWORK_SSID);
  CrOS::Log(message);
  
  WiFi.begin(CROS_NETWORK_SSID, CROS_NETWORK_PASS);
}
