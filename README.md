# ESP32C3-Heart-Rate-Monitor-Blynk
ESP32-C3 based heart-rate monitoring prototype with analog pulse sensing, Blynk Cloud telemetry, and configurable alerts.
# ESP32-C3 Heart Rate Monitoring with Blynk Cloud

**An IoT-based prototype for pulse monitoring and remote data visualization.**

## Overview

This project uses an ESP32-C3 SuperMini and an analog Pulse Sensor to estimate heart rate from a pulse waveform. Readings can be transmitted to Blynk Cloud for remote monitoring, with configurable cloud events for readings outside selected limits.

## Features

- Analog pulse signal acquisition
- Estimated heart rate in beats per minute (BPM)
- Blynk Cloud telemetry
- Configurable high and low threshold alerts
- Serial Monitor debugging

## Hardware Requirements

- ESP32-C3 SuperMini
- Three-pin analog Pulse Sensor
- USB data cable
- Wi-Fi hotspot or compatible router

## Software Requirements

- Arduino IDE
- ESP32 board support for Arduino
- Blynk library and Blynk IoT account

## Circuit Connections

| Pulse Sensor | ESP32-C3 |
|---|---|
| VCC | 5 V, if supported by the sensor |
| GND | GND |
| Signal | GPIO0 |

Confirm the sensor's voltage requirements and ensure its output is safe for the ESP32-C3 input.

## Setup

1. Install Arduino IDE and the ESP32 board package.
2. Install the Blynk library.
3. Create a Blynk template and device.
4. Configure the required virtual-pin datastreams.
5. Add your Wi-Fi credentials and Blynk device token securely.
6. Upload the firmware to the ESP32-C3.
7. Open Serial Monitor at 115200 baud.
8. Verify the pulse waveform and compare the BPM estimate with a suitable reference.
9. Check cloud updates and test alert events safely.

## Cloud Configuration

- V0: Heart rate (BPM)
- V1: Raw analog pulse signal
- Event code: `heart_rate_alert`

Configure event notifications in Blynk Console. Cloud alerts require a working network connection.

## Testing

Record the following before describing the project as tested:

- Sensor signal observed: Pending verification
- Heart-rate accuracy: Pending validation
- Blynk cloud transmission: Pending verification
- Alert delivery: Pending verification

## Limitations and Safety

This is an educational prototype, not a certified medical device. The basic beat-detection algorithm may miss beats or produce inaccurate estimates. It must not be used for diagnosis, emergency decisions, or treatment.

A pulse sensor alone does not measure blood oxygen saturation (SpO₂) or body temperature.

## Future Improvements

- Improve beat detection and signal filtering.
- Validate heart-rate accuracy against a suitable reference.
- Add connection-status monitoring and error reporting.
- Improve cloud dashboard presentation and alert testing.

## License

Specify the project's chosen license here once selected.
