# Panduan Driver USB Serial

Folder ini menyimpan **panduan dan tautan resmi**, bukan salinan installer. Driver USB-to-UART adalah perangkat lunak vendor yang dapat berubah versi dan lisensinya. Mengunduh dari vendor resmi memastikan driver sesuai Windows dan lebih mutakhir.

## Identifikasi chip USB pada board

Periksa tulisan pada IC kecil di dekat konektor USB atau lihat nama perangkat di Windows Device Manager.

| Chip USB-to-UART | Nama yang mungkin muncul | Sumber resmi |
|---|---|---|
| WCH CH340 / CH341 | `USB-SERIAL CH340`, `USB-Enhanced-SERIAL CH340` | [WCH CH341SER](https://www.wch-ic.com/downloads/CH341SER_EXE.html) |
| Silicon Labs CP2102 / CP210x | `Silicon Labs CP210x USB to UART Bridge` | [Silicon Labs CP210x VCP Driver](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers) |
| FTDI FT232 | `USB Serial Port (COMx)` / `FT232R` | [FTDI VCP Drivers](https://ftdichip.com/drivers/vcp-drivers/) |

NodeMCU/ESP32 bukan jaminan jenis chip: board yang sama dari penjual berbeda dapat menggunakan CH340, CP2102, atau chip lain. Pilih driver berdasarkan **chip di board**, bukan berdasarkan nama board saja.

## Instalasi di Windows

1. Lepas board dari USB.
2. Unduh driver yang cocok dari tautan resmi pada tabel.
3. Jalankan installer vendor dengan hak yang diperlukan oleh Windows, atau ikuti instruksi resmi bila paket berbentuk ZIP/INF.
4. Sambungkan board memakai kabel USB **data**.
5. Buka **Device Manager > Ports (COM & LPT)**.
6. Catat port yang muncul, misalnya `COM3` atau `COM5`.
7. Pilih port itu di Arduino IDE melalui **Tools > Port**.

## Jika port tidak muncul

1. Uji kabel USB lain; banyak kabel hanya mendukung pengisian daya.
2. Uji port USB komputer lain dan hindari hub USB pasif saat diagnosis.
3. Lihat Device Manager untuk perangkat dengan tanda seru kuning dan cocokkan hardware tersebut dengan chip pada tabel.
4. Hapus perangkat/driver bermasalah sesuai prosedur Windows/vendor, lalu instal ulang driver resmi.
5. Jangan menginstal driver dari situs unduhan tidak resmi atau paket driver acak.

## Pemeliharaan

Tautan diperiksa saat dokumentasi ini dibuat, tetapi vendor dapat mengubah halaman, versi, dan ketentuan lisensinya. Gunakan halaman vendor sebagai sumber kebenaran dan baca lisensi sebelum distribusi dalam produk komersial.
