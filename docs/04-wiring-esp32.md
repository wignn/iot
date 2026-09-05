# ESP32 DevKit V1 Wiring Guide

This document uses the **ESP32 DevKit V1** board profile with the classic ESP32 chip. Pin numbers listed in the tables refer to GPIO numbers printed on the board silkscreen. These pin selections are designed so that LoRa (SPI), OLED (I2C), and DHT22 signals do not collide; they are not the only valid pin mapping for ESP32.

## Transmitter: ESP32 + DHT22 + SX1278/Ra-02

| Device | Device Pin | ESP32 GPIO | Description |
|---|---|---:|---|
| DHT22 | VCC | 3V3 | 3.3 V Power |
| DHT22 | GND | GND | Common Ground |
| DHT22 | DATA / OUT | GPIO27 | Sensor Data |
| SX1278/Ra-02 | VCC | 3V3 | **3.3 V Only** |
| SX1278/Ra-02 | GND | GND | Common Ground |
| SX1278/Ra-02 | NSS / NCS / CS | GPIO5 | Chip Select |
| SX1278/Ra-02 | RST | GPIO14 | Radio Reset |
| SX1278/Ra-02 | DIO0 | GPIO26 | Radio Interrupt |
| SX1278/Ra-02 | SCK | GPIO18 | SPI Clock |
| SX1278/Ra-02 | MISO | GPIO19 | SPI MISO |
| SX1278/Ra-02 | MOSI | GPIO23 | SPI MOSI |
| SX1278/Ra-02 | DIO1–DIO5 | Not Connected | Unused in examples |

Open sketch: [`../examples/esp32-sender-dht11/esp32-sender-dht11.ino`](../examples/esp32-sender-dht11/esp32-sender-dht11.ino)

## Receiver: ESP32 + SX1278/Ra-02 + I2C OLED

| Device | Device Pin | ESP32 GPIO | Description |
|---|---|---:|---|
| I2C OLED | VCC | 3V3 | 3.3 V Power |
| I2C OLED | GND | GND | Common Ground |
| I2C OLED | SCL / SCK | GPIO22 | I2C Clock |
| I2C OLED | SDA | GPIO21 | I2C Data |
| SX1278/Ra-02 | VCC | 3V3 | **3.3 V Only** |
| SX1278/Ra-02 | GND | GND | Common Ground |
| SX1278/Ra-02 | NSS / NCS / CS | GPIO5 | Chip Select |
| SX1278/Ra-02 | RST | GPIO14 | Radio Reset |
| SX1278/Ra-02 | DIO0 | GPIO26 | Packet Received Interrupt |
| SX1278/Ra-02 | SCK | GPIO18 | SPI Clock |
| SX1278/Ra-02 | MISO | GPIO19 | SPI MISO |
| SX1278/Ra-02 | MOSI | GPIO23 | SPI MOSI |
| SX1278/Ra-02 | DIO1–DIO5 | Not Connected | Unused in examples |

Open sketch: [`../examples/esp32-receiver-oled/esp32-receiver-oled.ino`](../examples/esp32-receiver-oled/esp32-receiver-oled.ino)

## Adapting for Other ESP32 Boards

1. Verify that your board uses an ESP32 chip compatible with the selected Arduino ESP32 core package.
2. Select available GPIO pins that do not conflict with onboard flash memory, PSRAM, native USB, or onboard peripherals.
3. Update all `LORA_*_PIN`, `OLED_*_PIN`, or `DHT_PIN` constants in the corresponding sketch consistently.
4. Keep explicit `SPI.begin(SCK, MISO, MOSI, NSS)` and `Wire.begin(SDA, SCL)` calls in code to apply custom pin mappings.
5. Check strapping/boot pin requirements on your specific board variant before attaching external pull-up or pull-down resistors.
6. Power LoRa and OLED with 3.3 V and verify that all ground (GND) pins are tied together.

ESP32-S2, ESP32-S3, ESP32-C3, and boards featuring native USB interfaces may have different pin designations, strapping rules, and upload procedures. Consult official board documentation before adapting the DevKit V1 layout.
