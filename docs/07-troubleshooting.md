# Troubleshooting Guide

## USB Connection & Firmware Upload Issues

| Symptom | Common Cause | Recommended Action |
|---|---|---|
| COM port does not appear | Charge-only USB cable, driver not installed, or faulty USB port | Try a known good USB data cable, install official drivers for your chip, and reconnect. See [USB Driver Guide](drivers/README.md). |
| `Failed to connect` on ESP8266 | GPIO0/D3 pulled LOW externally, wrong board/port selected, or unstable USB connection | Temporarily disconnect peripherals on D3, verify selected board and COM port, and retry uploading. |
| `Connecting...` hangs on ESP32 | Board fails to enter bootloader mode automatically | Press and hold the BOOT button when `Connecting...` appears; consult board manufacturer instructions. |
| Upload process freezes or fails mid-way | Unstable USB power or faulty cable | Use a high-quality short USB cable and lower the upload speed setting to 115200 baud in Arduino IDE. |

## LoRa Radio Communication Issues

| Symptom | Common Cause | Recommended Action |
|---|---|---|
| `LoRa initialization failed` | Wiring error on SPI/NSS/RST/DIO0, power supply issue, weak 3.3 V regulator, or wrong radio chip | Power off the circuit, double-check connections against the wiring table, measure 3.3 V voltage rail, and verify radio pin numbers. |
| Transmitter sends but receiver receives nothing | Mismatched frequency/parameters, missing antennas, mismatched hardware frequency bands, or receiver wiring error | Verify both sketches use `433E6`, confirm both modules and antennas are 433 MHz units, and check receiver wiring. |
| Receiver receives packets intermittently | Unstable power, excessive range/interference, loose jumper wires, or poor antennas | Improve power supply stability and grounding, test devices at close range first, and verify antenna connections. |
| Poor RSSI / SNR values | Antenna positioning, physical obstacles, RF interference, or distance | Reorient/reposition antennas and test communication in an open environment. |

## DHT22 Sensor Issues

| Symptom | Common Cause | Recommended Action |
|---|---|---|
| `DHT22 read failed` | DATA/VCC/GND miswired, missing pull-up resistor, reading sensor too frequently, or damaged sensor | Inspect DHT22 wiring. For bare 4-pin sensors without a PCB module, add a 4.7–10 kΩ pull-up resistor between DATA and 3.3 V. Examples sample every 3 seconds. |
| Unrealistic temperature or humidity values | Condensation, poor placement near heat sources, or sensor accuracy limits | Ensure the sensor is clean and dry, position it properly, and cross-check against a reference thermometer/hygrometer. |

## OLED Display Issues

| Symptom | Common Cause | Recommended Action |
|---|---|---|
| `OLED not detected at I2C address 0x3C` | VCC/GND/SDA/SCL swapped, different I2C address, or non-SSD1306 display controller | Do NOT swap VCC/GND pins blindly. Inspect PCB labels and run an I2C scanner sketch; update `OLED_ADDRESS` to `0x3D` only if detected by scanner. |
| OLED turns on but displays nothing | Driver IC or resolution mismatch, wrong I2C wiring, or display contrast issue | Confirm your OLED module is a 4-pin I2C 128×64 SSD1306-compatible display. Double-check SDA and SCL pin wiring. |
| ESP8266 fails to boot when OLED is connected | OLED SDA uses GPIO0/D3, pulling bootstrap pin LOW | Check OLED pull-up resistors and wiring; disconnect OLED to confirm boot behavior. For custom designs, use I2C pins that do not interfere with ESP8266 boot modes. |

## Reporting Unresolved Issues

When asking for assistance, please document:
1. Exact development board model used.
2. Sketch filename uploaded to sender and receiver.
3. Serial Monitor output text (including any error messages).
4. Clear photos showing front and back silkscreen labels of the LoRa and OLED modules.
5. Measured 3.3 V power rail voltage.

This information helps distinguish between driver issues, board configuration bugs, power instability, wiring errors, or hardware incompatibility.
