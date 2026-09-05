# Troubleshooting

## Upload dan koneksi USB

| Gejala | Penyebab umum | Tindakan |
|---|---|---|
| Tidak ada port COM | Kabel hanya untuk charging, driver belum terpasang, atau port USB bermasalah | Coba kabel data lain, pasang driver sesuai chip, lalu sambungkan kembali. Lihat [panduan driver](drivers/README.md). |
| `Failed to connect` pada ESP8266 | GPIO0/D3 tertarik LOW, salah board/port, atau kabel tidak stabil | Lepas sementara perangkat di D3, cek board dan port, lalu upload ulang. |
| `Connecting...` tidak lanjut pada ESP32 | Board tidak masuk mode bootloader | Tekan/tahan BOOT saat `Connecting...`; lihat panduan produsen board. |
| Upload berhenti/putus | Daya USB atau kabel tidak stabil | Gunakan kabel pendek berkualitas dan turunkan upload speed ke 115200. |

## LoRa

| Gejala | Penyebab umum | Tindakan |
|---|---|---|
| `LoRa initialization failed` | VCC/GND salah, SPI/NSS/RST/DIO0 salah, regulator 3.3 V lemah, atau modul tidak sesuai | Matikan daya, periksa tabel wiring, ukur 3.3 V, lalu periksa kembali semua pin. |
| Sender mengirim tetapi receiver tidak menerima | Frekuensi/radio parameter berbeda, antena belum dipasang, modul band berbeda, atau wiring receiver salah | Pastikan kedua sketch memakai `433E6`, modul dan antena 433 MHz, serta kabel sesuai tabel. |
| Receiver hanya menerima kadang-kadang | Daya tidak stabil, jarak/halangan, antena buruk, koneksi longgar | Perbaiki daya dan ground, uji dekat terlebih dahulu, lalu periksa antena/konektor. |
| RSSI/SNR buruk | Penempatan antena, halangan, interferensi, atau jarak | Ubah posisi/orientasi antena dan uji lokasi berbeda. |

## DHT11

| Gejala | Penyebab umum | Tindakan |
|---|---|---|
| `DHT11 read failed` | DATA/VCC/GND salah, pull-up tidak ada, pembacaan dilakukan terlalu cepat, atau sensor rusak | Periksa wiring DHT11; untuk sensor tanpa board pasang pull-up 4.7–10 kΩ DATA ke 3.3 V. Contoh membaca tiap 3 detik. |
| Nilai suhu/kelembapan tidak wajar | Kondensasi, penempatan sensor, atau batas akurasi DHT11 | Keringkan/posisikan sensor dengan benar dan bandingkan dengan alat referensi. |

## OLED

| Gejala | Penyebab umum | Tindakan |
|---|---|---|
| `OLED not detected at I2C address 0x3C` | VCC/GND/SDA/SCL tertukar, alamat berbeda, atau modul bukan I2C SSD1306-compatible | Jangan menukar VCC/GND. Periksa label PCB dan jalankan I2C scanner; ubah `OLED_ADDRESS` ke `0x3D` hanya bila scanner menemukan `0x3D`. |
| OLED menyala tetapi kosong | Driver/resolusi bukan target, kabel I2C salah, atau contrast/kompatibilitas modul berbeda | Pastikan OLED 4-pin I2C 128×64 dan SSD1306-compatible. Periksa kembali SDA/SCL. |
| ESP8266 tidak boot ketika OLED terpasang | SDA memakai GPIO0/D3, pin bootstrap tertarik LOW | Periksa pull-up OLED dan kabel; lepas OLED untuk memastikan boot. Untuk desain produksi, gunakan pin I2C yang tidak memengaruhi bootstrap atau sesuaikan firmware. |

## Masih bermasalah

Catat board yang dipakai, nama sketch, teks error serial, foto label depan/belakang modul LoRa/OLED, dan hasil pemeriksaan tegangan. Informasi tersebut membedakan masalah driver, board, daya, koneksi, atau kompatibilitas modul.
