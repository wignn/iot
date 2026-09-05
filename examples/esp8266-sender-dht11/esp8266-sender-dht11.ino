#include <SPI.h>
#include <LoRa.h>
#include <DHT.h>

// Target board: NodeMCU 1.0 (ESP-12E Module)
// LoRa SX1278 / Ra-02: 433 MHz

constexpr uint8_t DHT_PIN = 0;       // D3 / GPIO0
constexpr uint8_t DHT_TYPE = DHT11;
constexpr uint8_t LORA_NSS_PIN = 15; // D8 / GPIO15
constexpr uint8_t LORA_RST_PIN = 16; // D0 / GPIO16
constexpr uint8_t LORA_DIO0_PIN = 4; // D2 / GPIO4
constexpr long LORA_FREQUENCY = 433E6;
constexpr unsigned long SEND_INTERVAL_MS = 3000;

DHT dht(DHT_PIN, DHT_TYPE);
unsigned long packetNumber = 0;

void haltWithError(const __FlashStringHelper *message) {
  Serial.println(message);
  while (true) {
    delay(1000);
  }
}

void setup() {
  Serial.begin(115200);
  dht.begin();

  Serial.println();
  Serial.println(F("LoRa DHT11 Sender - ESP8266"));

  LoRa.setPins(LORA_NSS_PIN, LORA_RST_PIN, LORA_DIO0_PIN);
  if (!LoRa.begin(LORA_FREQUENCY)) {
    haltWithError(F("LoRa initialization failed. Check power and wiring."));
  }

  Serial.println(F("LoRa ready at 433 MHz."));
}

void loop() {
  const float humidity = dht.readHumidity();
  const float temperatureC = dht.readTemperature();

  if (isnan(humidity) || isnan(temperatureC)) {
    Serial.println(F("DHT11 read failed. Check sensor wiring."));
    delay(SEND_INTERVAL_MS);
    return;
  }

  // Shared text payload format used by every sender/receiver example in this project.
  String payload = "pkt=" + String(packetNumber) +
                   ";temp_c=" + String(temperatureC, 1) +
                   ";humidity_pct=" + String(humidity, 1);

  LoRa.beginPacket();
  LoRa.print(payload);
  const int result = LoRa.endPacket();

  if (result == 1) {
    Serial.print(F("Sent: "));
    Serial.println(payload);
    packetNumber++;
  } else {
    Serial.println(F("Packet transmission failed."));
  }

  delay(SEND_INTERVAL_MS);
}
