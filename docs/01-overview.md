# Ikhtisar Sistem

## Tujuan

Sistem mengirim pembacaan suhu dan kelembapan DHT11 melalui radio LoRa SX1278/Ra-02 pada frekuensi 433 MHz. Penerima menampilkan payload dan kualitas sinyal pada serial monitor serta OLED I2C.

```text
DHT11 → ESP8266/ESP32 sender → SX1278 433 MHz ))) ((( SX1278 → ESP8266/ESP32 receiver → OLED
```

## Kombinasi yang didukung

Keempat contoh menggunakan format pesan dan pengaturan radio yang sama. Pengirim dan penerima dapat dipasangkan silang.

| Pengirim | Penerima | Status |
|---|---|---|
| ESP8266 sender | ESP8266 receiver | Didukung |
| ESP8266 sender | ESP32 receiver | Didukung |
| ESP32 sender | ESP8266 receiver | Didukung |
| ESP32 sender | ESP32 receiver | Didukung |

Kompatibilitas berlaku jika kedua modul benar-benar SX127x yang mendukung 433 MHz, antena sesuai frekuensi, serta frekuensi dan parameter radio identik.

## Format payload

Setiap pengirim mengirim teks ASCII berikut setiap 3 detik:

```text
pkt=12;temp_c=26.4;humidity_pct=70.0
```

| Field | Arti | Contoh |
|---|---|---|
| `pkt` | Nomor paket sejak perangkat dinyalakan | `12` |
| `temp_c` | Suhu dalam derajat Celsius | `26.4` |
| `humidity_pct` | Kelembapan relatif dalam persen | `70.0` |

Penerima saat ini menampilkan payload mentah. Ini membuat contoh tetap saling kompatibel dan memudahkan pemeriksaan data di serial monitor.

## Parameter radio

| Parameter | Nilai contoh |
|---|---|
| Chip radio | Semtech SX1278 / kompatibel (Ra-02) |
| Frekuensi | `433E6` / 433 MHz |
| Library radio | LoRa by Sandeep Mistry |
| Mode penerima | Callback `LoRa.onReceive()` dan `LoRa.receive()` |

Library menggunakan nilai default LoRa untuk parameter yang tidak ditentukan program. Jika Anda mengubah spreading factor, bandwidth, coding rate, sync word, CRC, atau daya pancar pada salah satu sisi, buat perubahan yang sama pada sisi lain.

## Batasan contoh

- Ini adalah contoh point-to-point, bukan LoRaWAN.
- Payload tidak dienkripsi dan tidak memiliki autentikasi; jangan kirim data rahasia tanpa menambahkan proteksi yang sesuai.
- DHT11 memiliki akurasi dan rentang terbatas. Untuk kebutuhan lebih baik, pertimbangkan DHT22, SHT3x, atau sensor lain serta sesuaikan kode.
- Tampilan OLED menyisakan ruang terbatas. Payload yang terlalu panjang dipotong pada 96 karakter oleh receiver untuk menjaga penggunaan memori.
