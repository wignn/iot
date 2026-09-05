#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define OLED_SDA 0   // GPIO0 (Pin D3 pada NodeMCU ESP8266)
#define OLED_SCL 5   // GPIO5 (Pin D1 pada NodeMCU ESP8266)

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C  // Alamat I2C default (0x3C atau 0x3D)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
bool oledReady = false;


#define ss 15        // GPIO15 (Pin D8 pada NodeMCU)
#define rst 16       // GPIO16 (Pin D0 pada NodeMCU)
#define dio0 4       // GPIO4  (Pin D2 pada NodeMCU)


// Variabel penampung data (volatile flag untuk transfer dari interrupt ke loop)
volatile bool newPacket = false;
String receivedMessage = "";
int packetRSSI = 0;
float packetSNR = 0;
unsigned int packetCount = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println("\n--- LoRa Receiver with OLED ---");

  // Inisialisasi Bus I2C kustom pada GPIO0 & GPIO5
  Wire.begin(OLED_SDA, OLED_SCL);

  // Inisialisasi Layar OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("OLED SSD1306 gagal diinisialisasi! Periksa koneksi/alamat I2C."));
  } else {
    oledReady = true;
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);
    display.setCursor(10, 15);
    display.println(F("LORA RECEIVER"));
    display.setCursor(10, 30);
    display.println(F("Inisialisasi..."));
    display.display();
    delay(1000);
  }

  // Setup pin modul LoRa
  LoRa.setPins(ss, rst, dio0);

  // Mulai LoRa pada frekuensi 433 MHz
  if (!LoRa.begin(433E6)) {
    Serial.println("Gagal memulai LoRa! Periksa kabel LoRa.");
    if (oledReady) {
      display.clearDisplay();
      display.setCursor(0, 15);
      display.println(F("LoRa GAGAL!"));
      display.println(F("Cek wiring LoRa!"));
      display.display();
    }
    while (1);
  }

  Serial.println("LoRa Berhasil Diinisialisasi!");

  // Daftarkan callback saat paket diterima
  LoRa.onReceive(onReceive);

  // Aktifkan mode receive
  LoRa.receive();

  // Tampilkan status standby di OLED
  if (oledReady) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println(F("=== LORA READY ==="));
    display.setCursor(0, 16);
    display.println(F("Freq : 433 MHz"));
    display.setCursor(0, 28);
    display.println(F("Status: Menunggu..."));
    display.display();
  }
}

void loop() {
  // Update tampilan OLED dilakukan di dalam loop() agar ESP8266 tidak crash (WDT reset)
  if (newPacket) {
    newPacket = false;

    if (oledReady) {
      display.clearDisplay();

      // Header: Nomor paket & RSSI
      display.setTextSize(1);
      display.setCursor(0, 0);
      display.print(F("RX #"));
      display.print(packetCount);
      display.print(F(" | "));
      display.print(packetRSSI);
      display.print(F("dBm"));

      // Garis pemisah horizontal
      display.drawLine(0, 10, 127, 10, SSD1306_WHITE);

      // Isi Pesan yang Diterima
      display.setCursor(0, 15);
      display.println(F("Pesan:"));
      display.setCursor(0, 26);
      display.println(receivedMessage);

      // Informasi SNR di bagian bawah layar
      display.drawLine(0, 52, 127, 52, SSD1306_WHITE);
      display.setCursor(0, 55);
      display.print(F("SNR: "));
      display.print(packetSNR);
      display.print(F(" dB"));

      display.display();
    }
  }
}


// Fungsi interrupt callback saat sinyal LoRa masuk
void onReceive(int packetSize) {
  if (packetSize == 0) return;

  receivedMessage = "";
  for (int i = 0; i < packetSize; i++) {
    receivedMessage += (char)LoRa.read();
  }

  packetRSSI = LoRa.packetRssi();
  packetSNR = LoRa.packetSnr();
  packetCount++;
  newPacket = true;

  // Cetak juga ke Serial Monitor
  Serial.print("Paket #");
  Serial.print(packetCount);
  Serial.print(" | Pesan: \"");
  Serial.print(receivedMessage);
  Serial.print("\" | RSSI: ");
  Serial.print(packetRSSI);
  Serial.print(" dBm | SNR: ");
  Serial.println(packetSNR);
}