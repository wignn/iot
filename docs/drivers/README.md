# USB Serial Driver Guide

This directory contains **guidance and official links** for USB drivers, rather than bundled installer executables. USB-to-UART bridge drivers are vendor-maintained software subject to version updates and licensing terms. Downloading drivers directly from official manufacturer sources ensures compatibility and security.

## Identifying the USB Chip on Your Board

Inspect the markings on the small IC located near the USB port on your development board, or check device details in Windows Device Manager.

| USB-to-UART Chip | Possible Device Name in Windows | Official Download Source |
|---|---|---|
| WCH CH340 / CH341 | `USB-SERIAL CH340`, `USB-Enhanced-SERIAL CH340` | [WCH CH341SER Official Page](https://www.wch-ic.com/downloads/CH341SER_EXE.html) |
| Silicon Labs CP2102 / CP210x | `Silicon Labs CP210x USB to UART Bridge` | [Silicon Labs CP210x VCP Drivers](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers) |
| FTDI FT232 | `USB Serial Port (COMx)` / `FT232R` | [FTDI VCP Drivers](https://ftdichip.com/drivers/vcp-drivers/) |

NodeMCU and ESP32 board names do not guarantee a specific USB chip family; identical development board designs from different manufacturers may use CH340, CP2102, or other bridge ICs. Select driver installers based on the **physical chip on the board**, not the micro-controller board name.

## Windows Installation Steps

1. Disconnect the development board from your computer's USB port.
2. Download the appropriate driver from the official manufacturer links in the table above.
3. Run the vendor installer with administrator privileges (or follow official setup instructions if provided as a ZIP/INF package).
4. Connect the board using a **USB data cable**.
5. Open **Device Manager > Ports (COM & LPT)**.
6. Note the assigned port number (for example, `COM3` or `COM5`).
7. In Arduino IDE, select that port under **Tools > Port**.

## Troubleshooting Unrecognized USB Ports

1. Test with a different USB cable; many cables sold with consumer devices are charge-only cables lacking data lines.
2. Try connecting directly to a different USB port on the computer and avoid unpowered USB hubs during testing.
3. Check Windows Device Manager for unrecognized devices marked with a yellow exclamation icon (`!`) and match hardware IDs against the table above.
4. Remove misconfigured device drivers via Device Manager and reinstall official vendor drivers.
5. Avoid downloading drivers from unauthorized third-party file hosting websites or unknown utility bundles.

## Maintenance Notice

Links were verified when this documentation was created; however, semiconductor vendors may update URL structures, driver versions, and licensing agreements over time. Treat official vendor websites as the primary source of truth and review licensing requirements prior to commercial distribution.
