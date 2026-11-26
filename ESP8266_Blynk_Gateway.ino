/*
 * Reconstructed reference firmware for the Semester V Energy Monitoring project.
 * Target: ESP8266 (e.g., NodeMCU) using Arduino IDE / ESP8266 core.
 * Receives CSV telemetry from STM32 over UART and publishes values to Blynk.
 *
 * IMPORTANT: This is a documented reconstruction, not the original source code.
 * Configure Wi-Fi/Blynk credentials and verify UART pins/logic before use.
 */
#define BLYNK_TEMPLATE_ID   "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "Energy Monitor"
#define BLYNK_AUTH_TOKEN    "YOUR_BLYNK_AUTH_TOKEN"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>

char ssid[] = "YOUR_WIFI_NAME";
char pass[] = "YOUR_WIFI_PASSWORD";

// Software UART: ESP8266 D5 = RX (from STM32 TX), D6 = TX (to STM32 RX).
// Cross-connect TX/RX and share GND. Both sides must use 3.3V UART logic.
SoftwareSerial stm32Serial(D5, D6); // RX, TX
BlynkTimer timer;

float voltageRms = 0.0f;
float currentRms = 0.0f;
float powerEstimate = 0.0f;
float energyWh = 0.0f;
int relayStatus = 0;
String inputLine;

void publishTelemetry() {
  Blynk.virtualWrite(V0, voltageRms);    // RMS voltage (V)
  Blynk.virtualWrite(V1, currentRms);    // RMS current (A)
  Blynk.virtualWrite(V2, powerEstimate); // estimated apparent power (VA)
  Blynk.virtualWrite(V3, energyWh);      // accumulated energy (Wh)
  Blynk.virtualWrite(V4, relayStatus);   // relay state (0/1)
}

void parseTelemetry(const String &line) {
  float v, i, p, e;
  int relay;
  // Expected STM32 line: voltage,current,power,energy,relay
  if (sscanf(line.c_str(), "%f,%f,%f,%f,%d", &v, &i, &p, &e, &relay) == 5) {
    voltageRms = v;
    currentRms = i;
    powerEstimate = p;
    energyWh = e;
    relayStatus = relay;
    publishTelemetry();
  }
}

void readFromStm32() {
  while (stm32Serial.available()) {
    const char c = (char)stm32Serial.read();
    if (c == '\n') {
      inputLine.trim();
      if (inputLine.length() > 0) parseTelemetry(inputLine);
      inputLine = "";
    } else if (c != '\r' && inputLine.length() < 100) {
      inputLine += c;
    } else if (inputLine.length() >= 100) {
      inputLine = ""; // discard malformed/oversized line
    }
  }
}

// Blynk button on V5: 1 = relay ON, 0 = relay OFF.
BLYNK_WRITE(V5) {
  const int requestedState = param.asInt() ? 1 : 0;
  stm32Serial.println(requestedState ? '1' : '0');
}

void setup() {
  Serial.begin(115200);
  stm32Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(100L, readFromStm32);
}

void loop() {
  Blynk.run();
  timer.run();
  readFromStm32();
}
