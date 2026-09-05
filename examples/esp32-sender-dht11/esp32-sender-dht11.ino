#include <SPI.h>
#include <LoRa.h>
#include <DHT.h>

// Target board: ESP32 DevKit V1
// LoRa SX1278 / Ra-02: 433 MHz

constexpr uint8_t DHT_PIN = 27;
constexpr uint8_t DHT_TYPE = DHT22;
constexpr uint8_t LORA_NSS_PIN = 5;
constexpr uint8_t LORA_RST_PIN = 14;
constexpr uint8_t LORA_DIO0_PIN = 26;
constexpr uint8_t LORA_SCK_PIN = 18;
constexpr uint8_t LORA_MISO_PIN = 19;
constexpr uint8_t LORA_MOSI_PIN = 23;
constexpr long LORA_FREQUENCY = 433E6;
constexpr unsigned long SEND_INTERVAL_MS = 3000;

DHT dht(DHT_PIN, DHT_TYPE);
unsigned long packetNumber = 0;

void haltWithError(const char *message) {
  Serial.println(message);
  while (true) {
    delay(1000);
  }
}

void setup() {
  Serial.begin(115200);
  dht.begin();

  Serial.println();
  Serial.println("LoRa DHT22 Sender - ESP32");

  SPI.begin(LORA_SCK_PIN, LORA_MISO_PIN, LORA_MOSI_PIN, LORA_NSS_PIN);
  LoRa.setPins(LORA_NSS_PIN, LORA_RST_PIN, LORA_DIO0_PIN);
  if (!LoRa.begin(LORA_FREQUENCY)) {
    haltWithError("LoRa initialization failed. Check power and wiring.");
  }

  Serial.println("LoRa ready at 433 MHz.");
}

void loop() {
  const float humidity = dht.readHumidity();
  const float temperatureC = dht.readTemperature();

  if (isnan(humidity) || isnan(temperatureC)) {
    Serial.println("DHT22 read failed. Check sensor wiring.");
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
    Serial.print("Sent: ");
    Serial.println(payload);
    packetNumber++;
  } else {
    Serial.println("Packet transmission failed.");
  }

  delay(SEND_INTERVAL_MS);
}
