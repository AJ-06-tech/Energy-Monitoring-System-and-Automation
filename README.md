
# Energy Monitoring System and Automation

An embedded and IoT-based project designed to monitor electrical energy consumption, identify appliance activity, and enable remote appliance control.

## Project Overview

The Energy Monitoring System and Automation project aims to reduce energy wastage in classrooms and laboratory environments through real-time monitoring, intelligent load identification, and automated control.

The system uses an STM32 microcontroller to acquire and process voltage and current signals. Non-Intrusive Load Monitoring (NILM) techniques are used to identify operating appliances from their electrical signatures. Processed information is communicated to a Wi-Fi module, allowing users to monitor energy usage and control appliances through a mobile or web dashboard.

## Objectives

- Monitor electrical parameters in real time.
- Identify appliance activity using NILM.
- Calculate RMS voltage, current, and power.
- Enable remote ON/OFF control of electrical appliances.
- Detect abnormal load conditions and potential faults.
- Reduce unnecessary energy consumption.

## Hardware Components

| Component | Purpose |
|---|---|
| STM32 Nucleo-F103RB | Data acquisition and processing |
| ACS712 Current Sensor | Current measurement |
| ZMPT101B Voltage Sensor | AC voltage measurement |
| ESP Wi-Fi Module | Wireless communication |
| Relay Module | Appliance switching |
| OLED Display (0.96 inch) | Local information display |
| Jumper Wires | Hardware connections |
| 9W Bulb | Demonstration load |

## Software and Technologies

- Embedded C / Microcontroller Programming
- STM32
- ESP-based Wi-Fi Communication
- Blynk IoT Dashboard
- UART Communication
- ADC Signal Acquisition
- Non-Intrusive Load Monitoring (NILM)

## System Working

1. The AC mains supply provides power to the connected electrical loads.
2. Voltage and current sensors acquire electrical signals from the supply.
3. The STM32 microcontroller samples these signals through its ADC channels.
4. The controller processes the signals to calculate RMS voltage, current, and power.
5. NILM techniques analyze electrical signatures to identify active appliances.
6. Relay driver circuits allow appliances to be switched ON or OFF.
7. Processed data is transferred to the Wi-Fi module through UART communication.
8. The Blynk dashboard provides remote monitoring and appliance control.
9. Abnormal current patterns and unexpected load conditions can trigger fault detection and safety actions.

## Key Features

- Real-time electrical parameter monitoring
- Centralized energy monitoring
- NILM-based appliance identification
- Remote appliance control
- Relay-based automation
- Abnormal load and fault detection
- IoT dashboard integration

## Applications

- Smart classrooms and laboratories
- Residential energy management
- Offices and commercial buildings
- Warehouses
- Smart energy monitoring systems

## Future Scope

- AI-based appliance identification
- Multi-room and multi-building monitoring
- Advanced cloud data storage and analytics
- PCB miniaturization
- Renewable energy and smart-grid integration
- Mobile application enhancements and voice control

## Project Report

The complete academic project report is available here:

(Energy_Monitoring_System_Project_Report.pdf)

## Academic Details

- **Course:** Mini Project 2A
- **Semester:** V
- **Academic Year:** 2025–2026
- **Department:** Electronics and Telecommunication Engineering
- **Institute:** Don Bosco Institute of Technology, Mumbai
