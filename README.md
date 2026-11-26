# Energy Monitoring System and Automation — Reconstructed Firmware

This folder contains a **reconstructed reference implementation** based on the architecture described in the Semester V project report and the team's clarification that the Wi-Fi module used was an **ESP8266**.

> **Provenance:** These files are not the original project source code. The report's Appendix B contains GSM/SIM900A and MPU6050 accident-detection sketches, which do not implement the energy-monitoring system. The files here are a new, clearly labelled reconstruction to demonstrate the intended STM32-to-Wi-Fi monitoring architecture.

## Contents

- `STM32_Firmware/STM32_Energy_Monitor.ino` — analogue sampling, RMS estimates, energy accumulation, basic over-current relay action, and UART telemetry.
- `ESP8266_Firmware/ESP8266_Blynk_Gateway.ino` — UART CSV reception, Wi-Fi/Blynk connection, telemetry publishing, and relay command forwarding.

## Report-aligned hardware references

- STM32 NUCLEO-F103RB controller
- ACS712 current sensor
- AC voltage-sensing module (the report refers to ZMPT101B in its implementation/results sections and LM358-based sensing in an earlier overview)
- ESP8266 Wi-Fi module (confirmed by the project team; some report sections instead say ESP32)
- Relay module / isolated relay driver
- Blynk dashboard

## Blynk datastream mapping

| Virtual pin | Meaning | Unit / value |
|---|---|---|
| V0 | RMS voltage | V |
| V1 | RMS current | A |
| V2 | Voltage × current estimate | VA (not true real power) |
| V3 | Accumulated energy estimate | Wh |
| V4 | Relay state | 0 = OFF, 1 = ON |
| V5 | Relay control button | 0 = OFF, 1 = ON |

## Before compiling or connecting hardware

1. Install the STM32duino core for the NUCLEO-F103RB and the ESP8266 Arduino core.
2. Add the Blynk library and configure the Template ID, Auth Token, Wi-Fi SSID, and password in the ESP8266 sketch.
3. Verify the STM32 ADC pins, UART instance/pins, relay-driver pin, relay polarity, and ESP8266 UART pins against the actual wiring.
4. Calibrate voltage and current conversion constants using appropriate isolated, calibrated test equipment. The constants in the sketch are placeholders/examples, not validated project calibration values.
5. The current calculation assumes an ACS712-20A sensitivity of 100 mV/A; change it to match the exact ACS712 variant.
6. The `voltage × current` calculation is an apparent-power estimate. True real power and power factor require synchronized voltage/current waveform multiplication and suitable calibration.
7. The sample-based RMS routines are demonstration code and should be validated for timing, sampling rate, filtering, and accuracy before any real deployment.

## Safety

Mains voltage is dangerous. Do not connect or test this circuit on live mains unless supervised by a qualified person using correctly rated isolation, sensor modules, fuses, enclosures, and relay drivers. Never connect mains directly to an MCU. The example over-current threshold and relay logic are not a certified protection system.

## Scope and limitations

This reference implementation demonstrates sensing, telemetry, dashboard integration, and a basic relay command path. It does **not** implement a complete NILM appliance-classification algorithm. NILM requires additional signal-feature extraction/classification work and validation against labelled appliance data.
