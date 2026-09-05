# Hardware, Daya, dan Keselamatan

## Bill of materials

Untuk satu link telemetry lengkap diperlukan:

| Jumlah | Komponen | Catatan |
|---:|---|---|
| 2 | ESP8266 NodeMCU **atau** ESP32 DevKit V1 | Satu sender dan satu receiver; boleh berbeda keluarga board |
| 2 | LoRa SX1278 / Ra-02 433 MHz | Pastikan kedua modul menggunakan band frekuensi sama |
| 2 | Antena 433 MHz | Pasang sebelum memberi daya pada LoRa |
| 1 | DHT11 | Sensor untuk sender |
| 1 | OLED 4-pin I2C, 128×64 | Target program: SSD1306-compatible, biasanya alamat `0x3C` |
| Secukupnya | Kabel jumper dan breadboard | Gunakan jalur pendek untuk SPI serta daya |
| 1 per board | Kabel USB data | USB charge-only tidak dapat digunakan untuk upload |

## Tegangan dan arus

| Perangkat | Tegangan yang digunakan proyek | Catatan |
|---|---|---|
| ESP8266 / ESP32 board dev | Dari USB atau input board sesuai dokumentasi board | Board mengatur regulator internalnya |
| SX1278 / Ra-02 | **3.3 V saja** | Jangan sambungkan VCC ke 5 V |
| OLED I2C | 3.3 V | Memberi daya 3.3 V menjaga pull-up I2C tetap pada level aman untuk ESP |
| DHT11 | 3.3 V | Aman untuk I/O 3.3 V |

Modul LoRa dapat membutuhkan arus puncak yang lebih besar daripada sensor biasa. Bila `LoRa.begin()` sering gagal atau perangkat reset, periksa kemampuan regulator 3.3 V dan sambungan GND. Gunakan regulator 3.3 V yang stabil dengan headroom arus yang memadai untuk board dan LoRa; jangan mengandalkan konverter USB-to-TTL kecil sebagai satu-satunya sumber untuk seluruh rangkaian.

## Aturan pemasangan

1. Matikan sumber daya sebelum mengubah kabel.
2. Sambungkan **semua GND** menjadi satu ground bersama.
3. Pasang antena yang sesuai band 433 MHz ke tiap SX1278 sebelum rangkaian diberi daya.
4. Periksa label PCB, bukan urutan fisik pin header. Pada OLED GM009605, urutan `VCC` dan `GND` dapat berbeda antar varian.
5. Pastikan LoRa yang digunakan adalah modul **433 MHz** bila firmware tetap memakai `433E6`. Jangan menggunakan `433E6` dengan modul/antena 868 atau 915 MHz.
6. Hindari menyentuh atau mencabut kabel saat perangkat menyala.

## Catatan DHT11

Modul DHT11 tiga pin yang sudah memakai PCB umumnya memiliki resistor pull-up data. Jika memakai DHT11 sensor mentah tanpa PCB, pasang resistor pull-up **4.7 kΩ hingga 10 kΩ** dari pin DATA ke 3.3 V. Rujuk datasheet sensor untuk orientasi pin paket sensor yang dipakai.

## Tentang OLED GM009605

Nama GM009605 tidak cukup untuk menjamin driver elektronik dan alamat I2C pada setiap penjual. Contoh receiver dikonfigurasi untuk:

- I2C empat pin: `VCC`, `GND`, `SCL`, `SDA`
- 128×64 pixel
- SSD1306-compatible
- alamat I2C `0x3C`

Bila OLED tidak terdeteksi, jangan menukar VCC/GND. Periksa label pin, jalankan pemindai I2C, lalu ubah konstanta `OLED_ADDRESS` menjadi `0x3D` hanya jika hasil scanner menunjukkan alamat tersebut. Modul 7-pin/SPI tidak dapat dipasang menggunakan tabel I2C ini tanpa konfigurasi hardware dan firmware berbeda.
