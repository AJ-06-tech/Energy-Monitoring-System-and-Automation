/*
 * Reconstructed reference firmware for the Semester V Energy Monitoring project.
 * Target: STM32 NUCLEO-F103RB using the STM32duino Arduino core.
 *
 * IMPORTANT: This is a documented reconstruction, not the original source code
 * recovered from the project. ADC pins, calibration constants and relay polarity
 * must be checked against the actual prototype before hardware use.
 */
#include <Arduino.h>
#include <math.h>

// ---- Pin mapping: verify against your actual wiring ----
const uint8_t VOLTAGE_SENSOR_PIN = PA0; // ZMPT101B analogue output (scaled/bias)
const uint8_t CURRENT_SENSOR_PIN = PA1; // ACS712 analogue output (bias around Vcc/2)
const uint8_t RELAY_PIN          = PB0; // relay driver input; use isolated driver
const uint8_t RELAY_ON_LEVEL     = HIGH;

// ---- Calibration placeholders: calibrate with a trusted meter/load ----
const float ADC_REFERENCE_V = 3.3f;
const float ADC_MAX_COUNTS  = 4095.0f; // 12-bit ADC
const float VOLTAGE_CALIBRATION = 230.0f; // adjust to match measured mains voltage
const float ACS712_SENSITIVITY_V_PER_A = 0.100f; // example for ACS712-20A; verify model
const float CURRENT_CALIBRATION = 1.0f; // adjust after calibration

const uint16_t SAMPLE_COUNT = 1000;
const uint16_t SAMPLE_INTERVAL_US = 200; // nominal sampling interval
const unsigned long REPORT_INTERVAL_MS = 1000;
const float OVERCURRENT_LIMIT_A = 5.0f; // example threshold; set for your load/relay rating

bool relayState = false;
float energyWh = 0.0f;
unsigned long lastReportMs = 0;

float readRmsVoltage(float &meanVoltage) {
  double sum = 0.0, sumSquares = 0.0;
  for (uint16_t i = 0; i < SAMPLE_COUNT; ++i) {
    const float sampleV = analogRead(VOLTAGE_SENSOR_PIN) * ADC_REFERENCE_V / ADC_MAX_COUNTS;
    sum += sampleV;
    sumSquares += (double)sampleV * sampleV;
    delayMicroseconds(SAMPLE_INTERVAL_US);
  }
  meanVoltage = (float)(sum / SAMPLE_COUNT);
  const double variance = (sumSquares / SAMPLE_COUNT) - ((double)meanVoltage * meanVoltage);
  const float acRms = sqrtf((float)max(0.0, variance));
  return acRms * VOLTAGE_CALIBRATION;
}

float readRmsCurrent() {
  double sum = 0.0, sumSquares = 0.0;
  for (uint16_t i = 0; i < SAMPLE_COUNT; ++i) {
    const float sampleV = analogRead(CURRENT_SENSOR_PIN) * ADC_REFERENCE_V / ADC_MAX_COUNTS;
    sum += sampleV;
    sumSquares += (double)sampleV * sampleV;
    delayMicroseconds(SAMPLE_INTERVAL_US);
  }
  const float meanV = (float)(sum / SAMPLE_COUNT);
  const double variance = (sumSquares / SAMPLE_COUNT) - ((double)meanV * meanV);
  const float sensorRmsV = sqrtf((float)max(0.0, variance));
  return (sensorRmsV / ACS712_SENSITIVITY_V_PER_A) * CURRENT_CALIBRATION;
}

void setRelay(bool on) {
  relayState = on;
  digitalWrite(RELAY_PIN, on ? RELAY_ON_LEVEL : !RELAY_ON_LEVEL);
}

void processEsp8266Commands() {
  // ESP8266 sends one-character commands terminated by newline: '1' or '0'.
  while (Serial1.available()) {
    const char command = (char)Serial1.read();
    if (command == '1') setRelay(true);
    else if (command == '0') setRelay(false);
  }
}

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  setRelay(false); // fail-safe startup state: OFF
  analogReadResolution(12);
  Serial.begin(115200);   // USB debug output
  Serial1.begin(115200);  // UART to ESP8266; verify board pin mapping/wiring
  Serial.println("Energy monitor starting");
}

void loop() {
  processEsp8266Commands();

  const unsigned long now = millis();
  if (now - lastReportMs >= REPORT_INTERVAL_MS) {
    lastReportMs = now;

    float voltageMean = 0.0f;
    const float voltageRms = readRmsVoltage(voltageMean);
    const float currentRms = readRmsCurrent();
    const float realPowerW = voltageRms * currentRms; // apparent-power estimate (PF not measured)
    energyWh += realPowerW * (REPORT_INTERVAL_MS / 3600000.0f);

    // Basic over-current protection example; choose a safe threshold for the hardware.
    if (currentRms > OVERCURRENT_LIMIT_A) setRelay(false);

    // CSV protocol consumed by ESP8266: voltage,current,power,energy,relay\n
    Serial1.print(voltageRms, 2); Serial1.print(',');
    Serial1.print(currentRms, 3); Serial1.print(',');
    Serial1.print(realPowerW, 2); Serial1.print(',');
    Serial1.print(energyWh, 4); Serial1.print(',');
    Serial1.println(relayState ? 1 : 0);

    Serial.print("Vrms="); Serial.print(voltageRms, 2);
    Serial.print(" V, Irms="); Serial.print(currentRms, 3);
    Serial.print(" A, estimated VA="); Serial.print(realPowerW, 2);
    Serial.print(", energy="); Serial.print(energyWh, 4);
    Serial.print(" Wh, relay="); Serial.println(relayState ? "ON" : "OFF");
  }
}
