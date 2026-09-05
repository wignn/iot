# Sistem Telemetri LoRa 433 MHz

Contoh proyek Arduino untuk mengirim data suhu dan kelembapan dari DHT11 melalui LoRa SX1278/Ra-02, lalu menerima data pada OLED I2C 128×64. Proyek menyediakan contoh yang siap dibuka dari Arduino IDE untuk **ESP8266 NodeMCU** dan **ESP32 DevKit V1**.

## Dukungan perangkat

| Peran | Board | Sensor/tampilan | Sketch siap upload |
|---|---|---|---|
| Pengirim | NodeMCU 1.0 (ESP-12E) | DHT11 + SX1278/Ra-02 | [`examples/esp8266-sender-dht11/`](examples/esp8266-sender-dht11/) |
| Penerima | NodeMCU 1.0 (ESP-12E) | SX1278/Ra-02 + OLED I2C | [`examples/esp8266-receiver-oled/`](examples/esp8266-receiver-oled/) |
| Pengirim | ESP32 DevKit V1 | DHT11 + SX1278/Ra-02 | [`examples/esp32-sender-dht11/`](examples/esp32-sender-dht11/) |
| Penerima | ESP32 DevKit V1 | SX1278/Ra-02 + OLED I2C | [`examples/esp32-receiver-oled/`](examples/esp32-receiver-oled/) |

Target OLED proyek ini adalah modul **GM009605 4-pin I2C** atau modul lain yang **SSD1306-compatible**, beresolusi **128×64**, dan memakai alamat I2C **`0x3C`**. Karena kode GM009605 bukan penanda driver yang terverifikasi secara universal, periksa tulisan pin pada PCB dan gunakan pemindai I2C bila layar tidak terdeteksi.

## Mulai cepat

1. Baca [kebutuhan hardware dan keselamatan daya](docs/02-hardware-and-power.md).
2. Pasang kabel berdasarkan board yang dipakai:
   - [ESP8266 / NodeMCU](docs/03-wiring-esp8266.md)
   - [ESP32 DevKit V1](docs/04-wiring-esp32.md)
3. Ikuti [instalasi Arduino IDE, board package, library, dan driver USB](docs/05-software-installation.md).
4. Buka satu folder contoh di Arduino IDE. Nama folder dan file `.ino` sudah sama sehingga dapat langsung di-upload.
5. Ikuti [prosedur upload dan verifikasi](docs/06-upload-and-verification.md).

## Struktur proyek

```text
iot/
├── README.md
├── LICENSE
├── docs/
│   ├── 01-overview.md
│   ├── 02-hardware-and-power.md
│   ├── 03-wiring-esp8266.md
│   ├── 04-wiring-esp32.md
│   ├── 05-software-installation.md
│   ├── 06-upload-and-verification.md
│   ├── 07-troubleshooting.md
│   └── drivers/README.md
└── examples/
    ├── esp8266-sender-dht11/esp8266-sender-dht11.ino
    ├── esp8266-receiver-oled/esp8266-receiver-oled.ino
    ├── esp32-sender-dht11/esp32-sender-dht11.ino
    └── esp32-receiver-oled/esp32-receiver-oled.ino
```

## Ketentuan penting

- SX1278/Ra-02 dan pin I/O ESP8266/ESP32 adalah **3.3 V**. Jangan hubungkan VCC LoRa ke 5 V.
- Pasang antena 433 MHz pada modul LoRa **sebelum** catu daya diberikan.
- Semua perangkat harus mempunyai **GND bersama**.
- Kedua ujung LoRa wajib memakai frekuensi dan parameter radio yang sama. Contoh ini memakai **433 MHz**.
- Jangan hanya mengikuti posisi header OLED. Hubungkan berdasarkan label **VCC**, **GND**, **SCL**, dan **SDA** yang tercetak di PCB; beberapa modul memiliki urutan header berbeda.

## Dokumen

- [Ikhtisar sistem dan kompatibilitas](docs/01-overview.md)
- [Hardware, daya, dan keselamatan](docs/02-hardware-and-power.md)
- [Wiring ESP8266 / NodeMCU](docs/03-wiring-esp8266.md)
- [Wiring ESP32 DevKit V1](docs/04-wiring-esp32.md)
- [Instalasi perangkat lunak](docs/05-software-installation.md)
- [Upload dan verifikasi](docs/06-upload-and-verification.md)
- [Troubleshooting](docs/07-troubleshooting.md)
- [Panduan driver USB](docs/drivers/README.md)

## Lisensi dan pihak ketiga

Contoh kode proyek ini dirilis dengan [Lisensi MIT](LICENSE). Library dan driver yang dipakai memiliki lisensi masing-masing; lihat sumber resmi pada [panduan instalasi](docs/05-software-installation.md) dan [panduan driver](docs/drivers/README.md).
