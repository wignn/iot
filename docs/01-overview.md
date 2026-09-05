# System Overview

## Purpose

The system transmits DHT22 temperature and humidity readings over SX1278/Ra-02 LoRa radio at 433 MHz. The receiver displays the incoming payload, RSSI, and SNR on the Serial Monitor and an I2C OLED screen.

```text
DHT22 → ESP8266/ESP32 sender → SX1278 433 MHz ))) ((( SX1278 → ESP8266/ESP32 receiver → OLED
```

## Supported Combinations

All four example sketches use an identical message format and radio configuration. Transmitter and receiver boards can be cross-paired freely.

| Transmitter | Receiver | Status |
|---|---|---|
| ESP8266 sender | ESP8266 receiver | Supported |
| ESP8266 sender | ESP32 receiver | Supported |
| ESP32 sender | ESP8266 receiver | Supported |
| ESP32 sender | ESP32 receiver | Supported |

Interoperability is supported as long as both radio modules are genuine 433 MHz SX127x modules, proper 433 MHz antennas are attached, and identical radio parameters are configured on both sides.

## Payload Format

Each transmitter sends the following ASCII text string every 3 seconds:

```text
pkt=12;temp_c=26.4;humidity_pct=70.0
```

| Field | Description | Example |
|---|---|---|
| `pkt` | Packet sequence number since boot | `12` |
| `temp_c` | Temperature in degrees Celsius | `26.4` |
| `humidity_pct` | Relative humidity in percent | `70.0` |

The receiver currently displays the raw payload string. This maintains cross-compatibility across examples and simplifies inspecting transmitted data on the Serial Monitor.

## Radio Parameters

| Parameter | Example Value |
|---|---|
| Radio Chip | Semtech SX1278 / compatible (Ra-02) |
| Frequency | `433E6` / 433 MHz |
| Radio Library | LoRa by Sandeep Mistry |
| Receiver Mode | `LoRa.onReceive()` callback & `LoRa.receive()` |

The library uses default LoRa radio settings for any parameters not explicitly specified in the code. If you alter the spreading factor, bandwidth, coding rate, sync word, CRC, or output power on one device, ensure identical changes are made on the peer device.

## Limitations

- This is a point-to-point LoRa implementation, not LoRaWAN.
- Payloads are unencrypted and unauthenticated; do not transmit sensitive data without implementing proper security layers.
- The DHT22 sensor provides higher accuracy and wider range than DHT11. For production or critical applications, consider upgrading to SHT3x or similar industrial sensors if needed.
- OLED screen space is limited. Received payloads longer than 96 characters are truncated by the receiver to conserve memory.
