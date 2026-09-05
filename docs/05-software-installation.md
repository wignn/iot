# Software Installation

## 1. Arduino IDE

Use Arduino IDE version 2.x from the official Arduino website. After installation, navigate to **File > Preferences** and add the following Board Manager URLs to **Additional Boards Manager URLs**. If other URLs are already present, separate them with a newline.

```text
ESP8266:
https://arduino.esp8266.com/stable/package_esp8266com_index.json

ESP32:
https://espressif.github.io/arduino-esp32/package_esp32_index.json
```

Then go to **Tools > Board > Boards Manager**, search for the following packages, and install them:

| Target Board | Board Manager Package | Board Selection for Upload |
|---|---|---|
| NodeMCU ESP8266 | `esp8266` by ESP8266 Community | `NodeMCU 1.0 (ESP-12E Module)` |
| ESP32 DevKit V1 | `esp32` by Espressif Systems | `ESP32 Dev Module` |

References: [ESP8266 Arduino Core Documentation](https://arduino-esp8266.readthedocs.io/en/latest/installing.html) and [Arduino-ESP32 Documentation](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html).

## 2. Arduino Libraries

Navigate to **Tools > Manage Libraries...** and install the following libraries by searching for their exact names and authors:

| Library | Author | Required By |
|---|---|---|
| `LoRa` | Sandeep Mistry | All examples |
| `DHT sensor library` | Adafruit | All transmitter examples |
| `Adafruit Unified Sensor` | Adafruit | Dependency of DHT sensor library |
| `Adafruit SSD1306` | Adafruit | All receiver examples |
| `Adafruit GFX Library` | Adafruit | Dependency of OLED library |
| `Adafruit BusIO` | Adafruit | Dependency of OLED library |

The Library Manager typically prompts to install dependencies automatically, but verify that all libraries listed above show as **Installed** prior to compiling.

Library source code: [LoRa](https://github.com/sandeepmistry/arduino-LoRa), [DHT sensor library](https://github.com/adafruit/DHT-sensor-library), [Adafruit SSD1306](https://github.com/adafruit/Adafruit_SSD1306), and [Adafruit GFX](https://github.com/adafruit/Adafruit-GFX-Library).

## 3. USB Serial Drivers

The required driver depends on the USB-to-UART bridge chip integrated into your board, not the main microcontroller firmware. Refer to the [USB Serial Driver Guide](drivers/README.md) to identify CH340/CH341, CP210x, or FTDI chips and download official vendor drivers.

Once the driver is installed and the board is connected using a **data** USB cable, select the populated port under **Tools > Port**. On Windows, port names typically appear as `COM3`, `COM5`, or similar.

## 4. Board & Upload Configuration Settings

### NodeMCU ESP8266

| Arduino IDE Option | Recommended Initial Value |
|---|---|
| Board | `NodeMCU 1.0 (ESP-12E Module)` |
| Upload Speed | `115200` (if uploads fail/unstable); `921600` (if stable) |
| CPU Frequency | `80 MHz` |
| Port | Detected COM port for the board |
| Serial Monitor | `115200 baud` |

### ESP32 DevKit V1

| Arduino IDE Option | Recommended Initial Value |
|---|---|
| Board | `ESP32 Dev Module` |
| Upload Speed | `115200` (increase only after confirming stable uploads) |
| Port | Detected COM port for the board |
| Serial Monitor | `115200 baud` |

For ESP32 boards that fail to enter upload mode automatically, press and hold the **BOOT** button when the upload status shows `Connecting...`, then release it after firmware transfer begins. Boot procedures vary between board models; consult your manufacturer documentation if necessary.

## 5. Opening Example Projects

Do not open `.ino` files directly from random working directories. In Arduino IDE, select **File > Open**, then open the main `.ino` file in one of the following example directories:

```text
examples/esp8266-sender-dht11/esp8266-sender-dht11.ino
examples/esp8266-receiver-oled/esp8266-receiver-oled.ino
examples/esp32-sender-dht11/esp32-sender-dht11.ino
examples/esp32-receiver-oled/esp32-receiver-oled.ino
```

Directory names and sketch filenames are intentionally identical to satisfy Arduino IDE sketch structure rules.
