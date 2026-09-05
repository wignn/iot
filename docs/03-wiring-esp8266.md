# ESP8266 / NodeMCU Wiring Guide

This document uses the **NodeMCU 1.0 (ESP-12E Module)** board profile. Pin labels `D0` through `D8` correspond to silkscreen markings on the NodeMCU board, not raw GPIO numbers. Refer to the GPIO column if using another ESP8266 board model.

> **GPIO0/D3 Boot Warning:** The examples use GPIO0 for the DHT11 data pin on the transmitter and for OLED SDA on the receiver. GPIO0 is a bootstrap pin: it must be pulled HIGH at reset to boot normally from flash memory. Do not press the FLASH button while booting, and ensure external circuitry does not pull this pin LOW during reset. If the board enters flash mode unexpectedly or fails to boot, temporarily disconnect D3 and inspect external pull-up/pull-down components.

## Transmitter: NodeMCU + DHT11 + SX1278/Ra-02

| Device | Device Pin | NodeMCU Pin | ESP8266 GPIO | Description |
|---|---|---|---:|---|
| DHT11 | VCC | 3V3 | — | 3.3 V Power |
| DHT11 | GND | GND | — | Common Ground |
| DHT11 | DATA / OUT | D3 | GPIO0 | Sensor Data |
| SX1278/Ra-02 | VCC | 3V3 | — | **3.3 V Only** |
| SX1278/Ra-02 | GND | GND | — | Common Ground |
| SX1278/Ra-02 | NSS / NCS / CS | D8 | GPIO15 | Chip Select |
| SX1278/Ra-02 | RST | D0 | GPIO16 | Radio Reset |
| SX1278/Ra-02 | DIO0 | D2 | GPIO4 | Radio Interrupt |
| SX1278/Ra-02 | SCK | D5 | GPIO14 | SPI Clock |
| SX1278/Ra-02 | MISO | D6 | GPIO12 | SPI MISO |
| SX1278/Ra-02 | MOSI | D7 | GPIO13 | SPI MOSI |
| SX1278/Ra-02 | DIO1–DIO5 | Not Connected | — | Unused in examples |

Open sketch: [`../examples/esp8266-sender-dht11/esp8266-sender-dht11.ino`](../examples/esp8266-sender-dht11/esp8266-sender-dht11.ino)

## Receiver: NodeMCU + SX1278/Ra-02 + I2C OLED

| Device | Device Pin | NodeMCU Pin | ESP8266 GPIO | Description |
|---|---|---|---:|---|
| I2C OLED | VCC | 3V3 | — | 3.3 V Power |
| I2C OLED | GND | GND | — | Common Ground |
| I2C OLED | SCL / SCK | D1 | GPIO5 | I2C Clock |
| I2C OLED | SDA | D3 | GPIO0 | I2C Data (Bootstrap Pin) |
| SX1278/Ra-02 | VCC | 3V3 | — | **3.3 V Only** |
| SX1278/Ra-02 | GND | GND | — | Common Ground |
| SX1278/Ra-02 | NSS / NCS / CS | D8 | GPIO15 | Chip Select |
| SX1278/Ra-02 | RST | D0 | GPIO16 | Radio Reset |
| SX1278/Ra-02 | DIO0 | D2 | GPIO4 | Packet Received Interrupt |
| SX1278/Ra-02 | SCK | D5 | GPIO14 | SPI Clock |
| SX1278/Ra-02 | MISO | D6 | GPIO12 | SPI MISO |
| SX1278/Ra-02 | MOSI | D7 | GPIO13 | SPI MOSI |
| SX1278/Ra-02 | DIO1–DIO5 | Not Connected | — | Unused in examples |

Open sketch: [`../examples/esp8266-receiver-oled/esp8266-receiver-oled.ino`](../examples/esp8266-receiver-oled/esp8266-receiver-oled.ino)

## Bare ESP-12E/ESP-12F Notes

The tables above are tailored for NodeMCU development boards, not raw ESP-12 modules. If soldering directly to a bare ESP-12E/F module, you must add a 3.3 V power regulator, reset circuit, 3.3 V USB-to-UART bridge, and proper boot pin pull resistors. Minimum boot configuration: EN/CH_PD HIGH, GPIO15 LOW, and GPIO0 and GPIO2 HIGH during normal boot. Refer to official Espressif datasheets and reference schematics for physical module pad pinouts; do not use NodeMCU silkscreen pinout tables for raw chip pin numbering.
