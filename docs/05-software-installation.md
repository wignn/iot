# Instalasi Perangkat Lunak

## 1. Arduino IDE

Gunakan Arduino IDE versi 2.x dari situs resmi Arduino. Setelah terpasang, buka **File > Preferences** dan tambahkan URL Board Manager berikut pada **Additional Boards Manager URLs**. Jika kolom sudah berisi URL lain, pisahkan dengan baris baru.

```text
ESP8266:
https://arduino.esp8266.com/stable/package_esp8266com_index.json

ESP32:
https://espressif.github.io/arduino-esp32/package_esp32_index.json
```

Lalu buka **Tools > Board > Boards Manager**, cari paket berikut, dan instal:

| Board yang akan dipakai | Paket Board Manager | Pilihan board saat upload |
|---|---|---|
| NodeMCU ESP8266 | `esp8266` by ESP8266 Community | `NodeMCU 1.0 (ESP-12E Module)` |
| ESP32 DevKit V1 | `esp32` by Espressif Systems | `ESP32 Dev Module` |

Rujukan: [dokumentasi ESP8266 Arduino core](https://arduino-esp8266.readthedocs.io/en/latest/installing.html) dan [dokumentasi Arduino-ESP32](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html).

## 2. Library Arduino

Buka **Tools > Manage Libraries...** dan instal library berikut dengan nama serta pembuat yang tepat.

| Library | Pembuat | Dibutuhkan oleh |
|---|---|---|
| `LoRa` | Sandeep Mistry | Semua contoh |
| `DHT sensor library` | Adafruit | Semua sender |
| `Adafruit Unified Sensor` | Adafruit | Dependency DHT sensor library |
| `Adafruit SSD1306` | Adafruit | Semua receiver |
| `Adafruit GFX Library` | Adafruit | Dependency OLED |
| `Adafruit BusIO` | Adafruit | Dependency OLED |

Library Manager biasanya akan memasang dependency otomatis, tetapi pastikan semua library di tabel muncul sebagai **Installed** sebelum kompilasi.

Sumber library: [LoRa](https://github.com/sandeepmistry/arduino-LoRa), [DHT sensor library](https://github.com/adafruit/DHT-sensor-library), [Adafruit SSD1306](https://github.com/adafruit/Adafruit_SSD1306), dan [Adafruit GFX](https://github.com/adafruit/Adafruit-GFX-Library).

## 3. Driver USB serial

Driver tergantung chip USB-to-UART pada board, bukan jenis firmware. Baca [panduan driver USB](drivers/README.md) untuk mengidentifikasi CH340/CH341, CP210x, atau FTDI dan memperoleh driver dari vendor resminya.

Setelah driver dipasang dan board disambungkan dengan kabel **data**, pilih port yang muncul melalui **Tools > Port**. Pada Windows nama port biasanya `COM3`, `COM5`, atau serupa.

## 4. Konfigurasi upload

### NodeMCU ESP8266

| Opsi Arduino IDE | Nilai awal yang disarankan |
|---|---|
| Board | `NodeMCU 1.0 (ESP-12E Module)` |
| Upload Speed | `115200` bila upload belum stabil; `921600` bila stabil |
| CPU Frequency | `80 MHz` |
| Port | Port COM board yang terdeteksi |
| Serial Monitor | `115200 baud` |

### ESP32 DevKit V1

| Opsi Arduino IDE | Nilai awal yang disarankan |
|---|---|
| Board | `ESP32 Dev Module` |
| Upload Speed | `115200` bila upload belum stabil; gunakan nilai lebih tinggi hanya setelah stabil |
| Port | Port COM board yang terdeteksi |
| Serial Monitor | `115200 baud` |

Untuk ESP32 yang gagal masuk upload mode, tahan tombol **BOOT** saat status upload mulai `Connecting...`, kemudian lepas setelah transfer berjalan. Prosedur ini berbeda pada setiap board; lihat dokumentasi produsen board jika diperlukan.

## 5. Membuka contoh

Jangan membuka file `.ino` langsung dari lokasi lain. Dari Arduino IDE pilih **File > Open**, kemudian buka file di salah satu folder berikut:

```text
examples/esp8266-sender-dht11/esp8266-sender-dht11.ino
examples/esp8266-receiver-oled/esp8266-receiver-oled.ino
examples/esp32-sender-dht11/esp32-sender-dht11.ino
examples/esp32-receiver-oled/esp32-receiver-oled.ino
```

Nama folder dan nama berkas sengaja dibuat identik agar sesuai dengan ketentuan sketch Arduino.
