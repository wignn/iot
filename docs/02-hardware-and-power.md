# Hardware, Power, and Safety

## Bill of Materials

A complete single-link telemetry system requires the following items:

| Quantity | Component | Notes |
|---:|---|---|
| 2 | ESP8266 NodeMCU **or** ESP32 DevKit V1 | One sender and one receiver; board families can be mixed |
| 2 | LoRa SX1278 / Ra-02 433 MHz | Ensure both modules operate on the same frequency band |
| 2 | 433 MHz Antenna | Attach before powering on the LoRa modules |
| 1 | DHT11 Sensor | Sensor for the transmitter node |
| 1 | 4-pin I2C OLED (128×64) | Software target: SSD1306-compatible, typically address `0x3C` |
| As needed | Jumper wires and breadboards | Keep wire runs short for SPI signals and power lines |
| 1 per board | Micro-USB / USB-C data cable | Charge-only USB cables cannot be used for uploading code |

## Voltage and Current Requirements

| Device | Project Voltage Level | Notes |
|---|---|---|
| ESP8266 / ESP32 Dev Board | Powered via USB or onboard pin | Onboard voltage regulator handles board power |
| SX1278 / Ra-02 | **3.3 V only** | **Do NOT connect VCC to 5 V** |
| I2C OLED | 3.3 V | Supplying 3.3 V keeps I2C pull-up logic levels safe for the ESP |
| DHT11 | 3.3 V | Safe for 3.3 V I/O logic levels |

LoRa modules draw high peak currents during transmission. If `LoRa.begin()` fails frequently or the microcontroller resets unexpectedly, check the 3.3 V power regulator capacity and GND connection. Use a stable 3.3 V power source with sufficient current headroom for both the board and the LoRa transceiver; do not rely on small USB-to-TTL adapters as the sole power source.

## Assembly and Handling Rules

1. Disconnect all power sources before modifying wiring.
2. Connect **all GND pins** together to establish a common ground reference.
3. Attach a proper 433 MHz antenna to each SX1278 module before applying power.
4. Always follow PCB pin labels rather than header pin order. On GM009605 OLED modules, `VCC` and `GND` layout may differ between board revisions.
5. Verify that your LoRa module is a **433 MHz** variant if firmware uses `433E6`. Do not operate `433E6` firmware with 868 MHz or 915 MHz modules/antennas.
6. Avoid touching or pulling wires while the device is powered on.

## DHT11 Wiring Notes

3-pin DHT11 module boards usually include an onboard data pull-up resistor. If using a raw 4-pin DHT11 sensor without a breakout board, install a **4.7 kΩ to 10 kΩ** pull-up resistor between the DATA line and 3.3 V. Refer to the sensor datasheet for pinout orientation.

## GM009605 OLED Notes

The label GM009605 does not guarantee a specific IC driver or I2C address across all suppliers. The receiver sketch is configured for:

- 4-pin I2C interface: `VCC`, `GND`, `SCL`, `SDA`
- 128×64 resolution
- SSD1306 compatibility
- I2C address `0x3C`

If the OLED display is not detected, do not swap VCC and GND pins. Check the PCB pin markings, run an I2C scanner sketch, and change the `OLED_ADDRESS` constant to `0x3D` only if reported by the scanner. 7-pin SPI OLED modules cannot be wired using these I2C tables without modifying hardware connections and firmware driver settings.
