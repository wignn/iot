# Wiring ESP32 DevKit V1

Dokumen ini memakai profil **ESP32 DevKit V1** dengan chip ESP32 klasik. Pin pada tabel adalah nomor GPIO yang umumnya tercetak di board. Pin tersebut adalah pilihan proyek agar jalur LoRa (SPI), OLED (I2C), dan DHT11 tidak bertabrakan; ini bukan satu-satunya pemetaan ESP32 yang valid.

## Sender: ESP32 + DHT11 + SX1278/Ra-02

| Perangkat | Pin perangkat | ESP32 GPIO | Keterangan |
|---|---|---:|---|
| DHT11 | VCC | 3V3 | Daya 3.3 V |
| DHT11 | GND | GND | Ground bersama |
| DHT11 | DATA / OUT | GPIO27 | Data sensor |
| SX1278/Ra-02 | VCC | 3V3 | **3.3 V saja** |
| SX1278/Ra-02 | GND | GND | Ground bersama |
| SX1278/Ra-02 | NSS / NCS / CS | GPIO5 | Chip select |
| SX1278/Ra-02 | RST | GPIO14 | Reset radio |
| SX1278/Ra-02 | DIO0 | GPIO26 | Interrupt radio |
| SX1278/Ra-02 | SCK | GPIO18 | SPI clock |
| SX1278/Ra-02 | MISO | GPIO19 | SPI MISO |
| SX1278/Ra-02 | MOSI | GPIO23 | SPI MOSI |
| SX1278/Ra-02 | DIO1–DIO5 | Tidak dihubungkan | Tidak dipakai contoh |

Buka sketch: [`../examples/esp32-sender-dht11/esp32-sender-dht11.ino`](../examples/esp32-sender-dht11/esp32-sender-dht11.ino)

## Receiver: ESP32 + SX1278/Ra-02 + OLED I2C

| Perangkat | Pin perangkat | ESP32 GPIO | Keterangan |
|---|---|---:|---|
| OLED I2C | VCC | 3V3 | Daya 3.3 V |
| OLED I2C | GND | GND | Ground bersama |
| OLED I2C | SCL / SCK | GPIO22 | I2C clock |
| OLED I2C | SDA | GPIO21 | I2C data |
| SX1278/Ra-02 | VCC | 3V3 | **3.3 V saja** |
| SX1278/Ra-02 | GND | GND | Ground bersama |
| SX1278/Ra-02 | NSS / NCS / CS | GPIO5 | Chip select |
| SX1278/Ra-02 | RST | GPIO14 | Reset radio |
| SX1278/Ra-02 | DIO0 | GPIO26 | Interrupt paket masuk |
| SX1278/Ra-02 | SCK | GPIO18 | SPI clock |
| SX1278/Ra-02 | MISO | GPIO19 | SPI MISO |
| SX1278/Ra-02 | MOSI | GPIO23 | SPI MOSI |
| SX1278/Ra-02 | DIO1–DIO5 | Tidak dihubungkan | Tidak dipakai contoh |

Buka sketch: [`../examples/esp32-receiver-oled/esp32-receiver-oled.ino`](../examples/esp32-receiver-oled/esp32-receiver-oled.ino)

## Adaptasi untuk board ESP32 lain

1. Pastikan board menggunakan chip ESP32 yang kompatibel dengan core Arduino ESP32 yang dipilih.
2. Pilih GPIO yang benar-benar tersedia pada board dan tidak berbagi fungsi penting dengan flash, PSRAM, USB native, atau peripheral board.
3. Ubah semua konstanta `LORA_*_PIN`, `OLED_*_PIN`, atau `DHT_PIN` pada sketch terkait secara konsisten.
4. Pertahankan pemanggilan `SPI.begin(SCK, MISO, MOSI, NSS)` dan `Wire.begin(SDA, SCL)` agar pin kustom diterapkan.
5. Periksa pin bootstrap pada varian board Anda sebelum memasang pull-up/pull-down eksternal.
6. Gunakan 3.3 V untuk LoRa dan OLED, lalu pastikan seluruh GND terhubung.

ESP32-S2, ESP32-S3, ESP32-C3, dan board dengan USB native dapat mempunyai nama board, pin, serta aturan upload berbeda. Gunakan dokumentasi resmi board tersebut sebelum menyalin pemetaan DevKit V1.
