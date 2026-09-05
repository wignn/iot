#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Target board: NodeMCU 1.0 (ESP-12E Module)
// OLED target: 4-pin I2C, 128x64, SSD1306-compatible, address 0x3C.
// LoRa target: SX1278 / Ra-02, 433 MHz.

constexpr uint8_t OLED_SDA_PIN = 0;  // D3 / GPIO0
constexpr uint8_t OLED_SCL_PIN = 5;  // D1 / GPIO5
constexpr uint8_t OLED_ADDRESS = 0x3C;
constexpr int SCREEN_WIDTH = 128;
constexpr int SCREEN_HEIGHT = 64;
constexpr int OLED_RESET_PIN = -1;

constexpr uint8_t LORA_NSS_PIN = 15; // D8 / GPIO15
constexpr uint8_t LORA_RST_PIN = 16; // D0 / GPIO16
constexpr uint8_t LORA_DIO0_PIN = 4; // D2 / GPIO4
constexpr long LORA_FREQUENCY = 433E6;
constexpr size_t MAX_PACKET_LENGTH = 96;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET_PIN);
bool oledAvailable = false;

volatile bool packetPending = false;
volatile char receivedPayload[MAX_PACKET_LENGTH + 1] = "";
volatile int receivedRssi = 0;
volatile float receivedSnr = 0.0F;
volatile unsigned long receivedPacketCount = 0;

void showMessage(const __FlashStringHelper *line1, const __FlashStringHelper *line2) {
  if (!oledAvailable) {
    return;
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 16);
  display.println(line1);
  display.setCursor(0, 32);
  display.println(line2);
  display.display();
}

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println(F("LoRa OLED Receiver - ESP8266"));

  Wire.begin(OLED_SDA_PIN, OLED_SCL_PIN);
  oledAvailable = display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS);
  if (oledAvailable) {
    showMessage(F("LoRa receiver"), F("Initializing..."));
  } else {
    Serial.println(F("OLED not detected at I2C address 0x3C."));
  }

  LoRa.setPins(LORA_NSS_PIN, LORA_RST_PIN, LORA_DIO0_PIN);
  if (!LoRa.begin(LORA_FREQUENCY)) {
    Serial.println(F("LoRa initialization failed. Check power and wiring."));
    showMessage(F("LoRa failed"), F("Check wiring"));
    while (true) {
      delay(1000);
    }
  }

  LoRa.onReceive(onReceive);
  LoRa.receive();
  showMessage(F("LoRa ready: 433MHz"), F("Waiting for packets"));
  Serial.println(F("LoRa ready at 433 MHz."));
}

void loop() {
  if (!packetPending) {
    return;
  }

  noInterrupts();
  char payload[MAX_PACKET_LENGTH + 1];
  for (size_t index = 0; index < sizeof(payload); index++) {
    payload[index] = receivedPayload[index];
  }
  const int rssi = receivedRssi;
  const float snr = receivedSnr;
  const unsigned long packetCount = receivedPacketCount;
  packetPending = false;
  interrupts();

  Serial.print(F("Received #"));
  Serial.print(packetCount);
  Serial.print(F(" | RSSI: "));
  Serial.print(rssi);
  Serial.print(F(" dBm | SNR: "));
  Serial.print(snr, 1);
  Serial.print(F(" dB | Payload: "));
  Serial.println(payload);

  if (!oledAvailable) {
    return;
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print(F("RX #"));
  display.print(packetCount);
  display.print(F("  "));
  display.print(rssi);
  display.println(F("dBm"));
  display.drawLine(0, 10, 127, 10, SSD1306_WHITE);
  display.setCursor(0, 16);
  display.println(F("Payload:"));
  display.setCursor(0, 27);
  display.println(payload);
  display.drawLine(0, 52, 127, 52, SSD1306_WHITE);
  display.setCursor(0, 55);
  display.print(F("SNR: "));
  display.print(snr, 1);
  display.println(F(" dB"));
  display.display();
}

void onReceive(int packetSize) {
  if (packetSize <= 0) {
    return;
  }

  const size_t bytesToRead = min(static_cast<size_t>(packetSize), MAX_PACKET_LENGTH);
  for (size_t index = 0; index < bytesToRead; index++) {
    receivedPayload[index] = static_cast<char>(LoRa.read());
  }
  receivedPayload[bytesToRead] = '\0';

  while (LoRa.available()) {
    LoRa.read();
  }

  receivedRssi = LoRa.packetRssi();
  receivedSnr = LoRa.packetSnr();
  receivedPacketCount++;
  packetPending = true;
}
