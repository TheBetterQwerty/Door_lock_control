# ESP32 Smart Door Lock

An IoT door locking system using an ESP32. Sends lock/unlock logs to a Discord channel via webhook.

## Features

- Lock/unlock mechanism via ESP32
- Wi-Fi connectivity
- Sends lock/unlock logs to Discord

## Hardware

- ESP32 Dev Board
- Lock mechanism (e.g., servo or solenoid)
- Power supply

## Software

- C/C++ with Arduino framework or ESP-IDF
- Discord Webhook integration

## Setup

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/esp32-door-lock.git
   cd esp32-door-lock'''
   
2. Add your Wi-Fi and Discord webhook info to the config:
   #define WIFI_SSID "your-ssid"
   #define WIFI_PASS "your-password"
