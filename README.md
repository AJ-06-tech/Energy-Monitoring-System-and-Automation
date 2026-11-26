# Energy Monitoring System and Automation

An embedded systems and IoT-based project for monitoring electrical energy consumption, identifying appliance activity, and enabling remote appliance control.

## Project Overview

The system uses an STM32 NUCLEO-F103RB microcontroller to acquire and process electrical parameters from voltage and current sensors. An ESP8266 Wi-Fi module enables wireless communication with the Blynk IoT dashboard for remote monitoring and appliance control.

The project explores energy monitoring, load identification using Non-Intrusive Load Monitoring (NILM), and relay-based automation.

## Key Features

- Real-time voltage and current monitoring
- RMS voltage and current calculations
- Power and energy estimation
- Sensor interfacing using STM32 ADC
- UART-based communication
- ESP8266 Wi-Fi connectivity
- Blynk IoT dashboard integration
- Relay-based appliance control
- Exploration of NILM for appliance identification

## Hardware Components

| Component | Purpose |
|---|---|
| STM32 NUCLEO-F103RB | Main controller and data processing |
| ACS712 | Current sensing |
| AC Voltage Sensor | Voltage measurement |
| ESP8266 | Wi-Fi communication |
| Relay Module | Appliance switching |
| OLED Display | Local information display |
| Electrical Load | System demonstration |

## Technologies Used

- Embedded C / Arduino Framework
- STM32
- ESP8266
- ADC
- UART Communication
- Blynk IoT
- Sensor Interfacing
- Relay Control

## System Architecture and Working

1. Voltage and current sensors acquire electrical signals from the connected load.
2. The STM32 microcontroller reads sensor outputs through ADC channels.
3. Electrical parameters are processed to estimate RMS voltage, current, power and energy.
4. The ESP8266 receives monitoring data from the STM32 through UART.
5. Wi-Fi connectivity enables communication with the Blynk IoT dashboard.
6. Users can monitor readings and send remote appliance-control commands.
7. The relay module performs appliance switching based on the control logic.

## Project Diagrams

- [Block Diagram](Block%20Diaagram.png)
- [System Working Diagram](Working.png)

## Firmware Source Code

The repository includes a reconstructed reference implementation based on the project's documented architecture.

- [STM32 Energy Monitoring Firmware](STM32_Energy_Monitor.ino)
- [ESP8266 Blynk Gateway Firmware](ESP8266_Blynk_Gateway.ino)

**Source Code Note:** These firmware files are reconstructed reference implementations, not the original project source files. They are provided to demonstrate the intended embedded-system architecture and require hardware-specific configuration and validation.

## Project Report

[View the Complete Semester V Project Report](Energy_Monitoring_System_Project_Report.pdf)

## Applications

- Smart energy monitoring
- Classroom and laboratory energy management
- Residential energy management
- Office and commercial energy monitoring
- IoT-based appliance automation

## Future Scope

- Improved NILM-based appliance classification
- Multi-room energy monitoring
- Cloud-based energy analytics
- Enhanced fault detection
- Integration with smart-grid systems

## Academic Details

- **Project:** Mini Project 2A
- **Semester:** V
- **Academic Year:** 2025–2026
- **Department:** Electronics and Telecommunication Engineering
- **Institute:** Don Bosco Institute of Technology, Mumbai
