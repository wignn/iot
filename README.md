# 433 MHz LoRa Telemetry System

Arduino example project for transmitting DHT22 temperature and humidity data over LoRa SX1278/Ra-02, and receiving the data on a 128×64 I2C OLED display. This repository provides ready-to-open Arduino IDE examples for **ESP8266 NodeMCU** and **ESP32 DevKit V1**.

## Supported Hardware

| Role | Board | Sensor / Display | Ready-to-upload Sketch |
|---|---|---|---|
| Transmitter | NodeMCU 1.0 (ESP-12E) | DHT22 + SX1278/Ra-02 | [`examples/esp8266-sender-dht11/`](examples/esp8266-sender-dht11/) |
| Receiver | NodeMCU 1.0 (ESP-12E) | SX1278/Ra-02 + I2C OLED | [`examples/esp8266-receiver-oled/`](examples/esp8266-receiver-oled/) |
| Transmitter | ESP32 DevKit V1 | DHT22 + SX1278/Ra-02 | [`examples/esp32-sender-dht11/`](examples/esp32-sender-dht11/) |
| Receiver | ESP32 DevKit V1 | SX1278/Ra-02 + I2C OLED | [`examples/esp32-receiver-oled/`](examples/esp32-receiver-oled/) |

The target OLED for this project is a **GM009605 4-pin I2C** module or any other **SSD1306-compatible** module with a **128×64** resolution using I2C address **`0x3C`**. Because the GM009605 marking is not a universally verified driver identifier, check the pin labels on the PCB and use an I2C scanner if the display is not detected.

## Quick Start

1. Review [hardware requirements and power safety](docs/02-hardware-and-power.md).
2. Wire components based on your board:
   - [ESP8266 / NodeMCU Wiring](docs/03-wiring-esp8266.md)
   - [ESP32 DevKit V1 Wiring](docs/04-wiring-esp32.md)
3. Follow the instructions for [Arduino IDE setup, board packages, libraries, and USB drivers](docs/05-software-installation.md).
4. Open one example directory in Arduino IDE. Directory and `.ino` file names match, so they can be uploaded directly.
5. Follow the [upload and verification procedure](docs/06-upload-and-verification.md).

## Project Structure

```text
iot/
├── README.md
├── LICENSE
├── docs/
│   ├── 01-overview.md
│   ├── 02-hardware-and-power.md
│   ├── 03-wiring-esp8266.md
│   ├── 04-wiring-esp32.md
│   ├── 05-software-installation.md
│   ├── 06-upload-and-verification.md
│   ├── 07-troubleshooting.md
│   └── drivers/README.md
└── examples/
    ├── esp8266-sender-dht11/esp8266-sender-dht11.ino
    ├── esp8266-receiver-oled/esp8266-receiver-oled.ino
    ├── esp32-sender-dht11/esp32-sender-dht11.ino
    └── esp32-receiver-oled/esp32-receiver-oled.ino
```

## Important Notes

- SX1278/Ra-02 and ESP8266/ESP32 I/O pins operate at **3.3 V**. Do NOT connect LoRa VCC to 5 V.
- Attach a 433 MHz antenna to the LoRa module **before** supplying power.
- All devices must share a common **GND**.
- Both ends of the LoRa link must use the same frequency and radio parameters. This project defaults to **433 MHz**.
- Do not rely solely on the physical header layout of the OLED module. Always connect according to the **VCC**, **GND**, **SCL**, and **SDA** labels printed on the PCB, as header pinouts vary between hardware modules.

## Documentation

- [System Overview and Compatibility](docs/01-overview.md)
- [Hardware, Power, and Safety](docs/02-hardware-and-power.md)
- [ESP8266 / NodeMCU Wiring](docs/03-wiring-esp8266.md)
- [ESP32 DevKit V1 Wiring](docs/04-wiring-esp32.md)
- [Software Installation](docs/05-software-installation.md)
- [Upload and Verification](docs/06-upload-and-verification.md)
- [Troubleshooting Guide](docs/07-troubleshooting.md)
- [USB Serial Driver Guide](docs/drivers/README.md)

## License and Third-Party Notices

The example code in this repository is released under the [MIT License](LICENSE). Third-party libraries and drivers are governed by their respective licenses; refer to official sources in the [software installation guide](docs/05-software-installation.md) and [driver guide](docs/drivers/README.md).
