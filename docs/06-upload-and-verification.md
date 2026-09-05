# Upload and Verification Guide

## Pre-Power Inspection Checklist

- Confirm that a 433 MHz antenna is attached to both LoRa modules.
- Ensure SX1278/Ra-02 VCC is connected to 3.3 V, NOT 5 V.
- Ensure all ground (GND) lines are connected together.
- Verify wiring connections pin-by-pin against the wiring table for your board family.
- Place transmitter and receiver nodes close together for initial testing, keeping antennas separated by at least a few tens of centimeters to prevent RF overload.

## Upload Procedure

1. Choose a sketch pair from the `examples/` directory. ESP8266 and ESP32 boards can be cross-paired.
2. Upload the receiver sketch first.
3. Open the **Serial Monitor** set to `115200 baud`.
4. Verify that the receiver displays a ready status. If an OLED display is connected and supported, it should display a "Waiting for packets" screen.
5. Upload the transmitter sketch.
6. Open the transmitter **Serial Monitor** set to `115200 baud`.
7. Verify that the transmitter prints a `Sent:` message approximately once every 3 seconds.
8. Check the receiver Serial Monitor and OLED display. Both should display incoming payload data alongside RSSI and SNR values.

## Expected Output

### Transmitter

Sample serial output:

```text
LoRa DHT11 Sender - ESP32
LoRa ready at 433 MHz.
Sent: pkt=0;temp_c=26.4;humidity_pct=70.0
Sent: pkt=1;temp_c=26.4;humidity_pct=70.0
```

The board name on the first line changes to ESP8266 or ESP32 depending on the uploaded sketch.

### Receiver

Sample serial output:

```text
LoRa OLED Receiver - ESP8266
LoRa ready at 433 MHz.
Received #1 | RSSI: -63 dBm | SNR: 9.5 dB | Payload: pkt=0;temp_c=26.4;humidity_pct=70.0
```

The OLED screen displays the packet sequence number, RSSI, payload string, and SNR. RSSI and SNR values depend on physical distance, antennas, transmission power, obstacles, and RF environment conditions; there is no single fixed reference value.

## Packet Reception Verification Checklist

| Inspection Item | Expected Result |
|---|---|
| Both modules have antennas attached | Yes |
| Both sketches use `433E6` frequency | Yes |
| Transmitter prints `Sent:` messages | Yes |
| Receiver successfully completes LoRa initialization | Yes |
| Receiver prints `Received #` messages | Yes |
| OLED displays received packet data (if connected) | Yes |
| Transmitter and receiver payload contents match | Yes |

## Single-Variable Testing Method

If communication fails, do not change frequency settings, pin assignments, and libraries simultaneously. Start by verifying power supply and physical wiring connections, then confirm that `LoRa.begin()` succeeds on both sides. Next, verify operating frequency and antenna connections, followed by sensor and OLED functions. Refer to the [troubleshooting guide](07-troubleshooting.md) for specific failure symptoms.
