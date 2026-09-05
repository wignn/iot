# Wiring ESP8266 / NodeMCU

Dokumen ini memakai profil **NodeMCU 1.0 (ESP-12E Module)**. Label `D0` sampai `D8` adalah label pada board NodeMCU, bukan nomor GPIO. Ikuti kolom GPIO bila menggunakan board ESP8266 lain.

> **Peringatan GPIO0/D3:** contoh memakai GPIO0 pada sender untuk DHT11 dan pada receiver untuk SDA OLED. GPIO0 adalah pin bootstrap: harus HIGH ketika reset agar boot normal dari flash. Jangan menekan tombol FLASH ketika upload selesai, dan pastikan rangkaian eksternal tidak menarik pin ini LOW saat perangkat reset. Jika muncul mode flash/boot gagal, lepas perangkat pada D3 sementara dan periksa pull-up/pull-down modul.

## Sender: NodeMCU + DHT11 + SX1278/Ra-02

| Perangkat | Pin perangkat | NodeMCU | GPIO ESP8266 | Keterangan |
|---|---|---|---:|---|
| DHT11 | VCC | 3V3 | — | Daya 3.3 V |
| DHT11 | GND | GND | — | Ground bersama |
| DHT11 | DATA / OUT | D3 | GPIO0 | Data sensor |
| SX1278/Ra-02 | VCC | 3V3 | — | **3.3 V saja** |
| SX1278/Ra-02 | GND | GND | — | Ground bersama |
| SX1278/Ra-02 | NSS / NCS / CS | D8 | GPIO15 | Chip select |
| SX1278/Ra-02 | RST | D0 | GPIO16 | Reset radio |
| SX1278/Ra-02 | DIO0 | D2 | GPIO4 | Interrupt radio |
| SX1278/Ra-02 | SCK | D5 | GPIO14 | SPI clock |
| SX1278/Ra-02 | MISO | D6 | GPIO12 | SPI MISO |
| SX1278/Ra-02 | MOSI | D7 | GPIO13 | SPI MOSI |
| SX1278/Ra-02 | DIO1–DIO5 | Tidak dihubungkan | — | Tidak dipakai contoh |

Buka sketch: [`../examples/esp8266-sender-dht11/esp8266-sender-dht11.ino`](../examples/esp8266-sender-dht11/esp8266-sender-dht11.ino)

## Receiver: NodeMCU + SX1278/Ra-02 + OLED I2C

| Perangkat | Pin perangkat | NodeMCU | GPIO ESP8266 | Keterangan |
|---|---|---|---:|---|
| OLED I2C | VCC | 3V3 | — | Daya 3.3 V |
| OLED I2C | GND | GND | — | Ground bersama |
| OLED I2C | SCL / SCK | D1 | GPIO5 | I2C clock |
| OLED I2C | SDA | D3 | GPIO0 | I2C data; pin bootstrap |
| SX1278/Ra-02 | VCC | 3V3 | — | **3.3 V saja** |
| SX1278/Ra-02 | GND | GND | — | Ground bersama |
| SX1278/Ra-02 | NSS / NCS / CS | D8 | GPIO15 | Chip select |
| SX1278/Ra-02 | RST | D0 | GPIO16 | Reset radio |
| SX1278/Ra-02 | DIO0 | D2 | GPIO4 | Interrupt paket masuk |
| SX1278/Ra-02 | SCK | D5 | GPIO14 | SPI clock |
| SX1278/Ra-02 | MISO | D6 | GPIO12 | SPI MISO |
| SX1278/Ra-02 | MOSI | D7 | GPIO13 | SPI MOSI |
| SX1278/Ra-02 | DIO1–DIO5 | Tidak dihubungkan | — | Tidak dipakai contoh |

Buka sketch: [`../examples/esp8266-receiver-oled/esp8266-receiver-oled.ino`](../examples/esp8266-receiver-oled/esp8266-receiver-oled.ino)

## Catatan bare ESP-12E/ESP-12F

Tabel di atas ditujukan untuk NodeMCU, bukan modul ESP-12 bare. Jika menyolder langsung ke ESP-12E/F, Anda tetap membutuhkan regulator 3.3 V, rangkaian reset, USB-to-UART 3.3 V, dan resistor bootstrap yang benar. Minimal: EN/CH_PD HIGH, GPIO15 LOW, serta GPIO0 dan GPIO2 HIGH saat boot normal. Gunakan datasheet ESP-12E/F dan skema referensi Espressif untuk nomor pad fisik; jangan mengandalkan tabel NodeMCU sebagai pemetaan pin fisik modul.
