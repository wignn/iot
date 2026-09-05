# Upload dan Verifikasi

## Sebelum memberi daya

- Pastikan antena 433 MHz sudah terpasang di kedua modul LoRa.
- Pastikan VCC SX1278/Ra-02 ke 3.3 V, bukan 5 V.
- Pastikan seluruh GND tersambung bersama.
- Bandingkan kabel satu per satu dengan tabel wiring untuk board yang digunakan.
- Pasang sender dan receiver pada jarak dekat untuk pengujian pertama, lalu jauhkan antena beberapa puluh sentimeter agar tidak terlalu dekat.

## Urutan upload

1. Pilih satu pasangan sketch dari folder `examples/`. Kombinasi ESP8266 dan ESP32 dapat dicampur.
2. Upload sketch receiver terlebih dahulu.
3. Buka **Serial Monitor** pada `115200 baud`.
4. Pastikan receiver menampilkan status siap. Jika OLED cocok dan terhubung, layar menampilkan status menunggu paket.
5. Upload sketch sender.
6. Buka Serial Monitor sender pada `115200 baud`.
7. Periksa apakah sender mencetak satu pesan `Sent:` setiap sekitar tiga detik.
8. Periksa Serial Monitor receiver dan OLED. Keduanya harus menampilkan payload beserta RSSI dan SNR.

## Hasil yang diharapkan

### Sender

Contoh output serial:

```text
LoRa DHT11 Sender - ESP32
LoRa ready at 433 MHz.
Sent: pkt=0;temp_c=26.4;humidity_pct=70.0
Sent: pkt=1;temp_c=26.4;humidity_pct=70.0
```

Nama board pada baris pertama berubah menjadi ESP8266 atau ESP32 sesuai sketch.

### Receiver

Contoh output serial:

```text
LoRa OLED Receiver - ESP8266
LoRa ready at 433 MHz.
Received #1 | RSSI: -63 dBm | SNR: 9.5 dB | Payload: pkt=0;temp_c=26.4;humidity_pct=70.0
```

OLED menampilkan nomor paket, RSSI, payload, serta SNR. Nilai RSSI dan SNR bergantung pada jarak, antena, daya, hambatan fisik, dan kondisi radio; tidak ada angka tunggal yang selalu benar.

## Checklist penerimaan paket

| Pemeriksaan | Hasil benar |
|---|---|
| Kedua modul punya antena | Ya |
| Kedua sketch memakai `433E6` | Ya |
| Sender mencetak `Sent:` | Ya |
| Receiver selesai inisialisasi LoRa | Ya |
| Receiver mencetak `Received #` | Ya |
| OLED menampilkan paket (bila tersedia) | Ya |
| Payload sender dan receiver sama | Ya |

## Uji satu perubahan per waktu

Jika komunikasi belum bekerja, jangan sekaligus mengganti frekuensi, pin, dan library. Mulai dengan kabel dan catu daya, lalu konfirmasi `LoRa.begin()` pada kedua sisi. Sesudah itu periksa frekuensi dan antena, kemudian data sensor/OLED. Lihat [troubleshooting](07-troubleshooting.md) untuk gejala spesifik.
