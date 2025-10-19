# Elastick adapter

Connect vintage joysticks (Apple 2, Atari, CoCo...) to your modern PC via Bluetooth.

🚧 WORK IN PROGRESS – NOT READY YET 🚧

![preview.jpg](preview.jpg)

Elastick is a hardware and software project using the ESP32-based Lolin D32 to interface with classic joysticks. These devices are detected as Bluetooth input peripherals and can be used with emulators like MAME or any modern game using game controllers.

## Folders

- **code**: arduino code (I used arduino IDE v2)
- **3d**: resources for 3D printing
- **elec**: kicad project for PCB
- **resources**: various pictures

## Known issues

- The rotary button does not work perfectly. It's unclear whether this is due to a hardware limitation or a software issue that could be resolved in code.

- The Lolin board draws a significant amount of current when Bluetooth is initialized, which can cause a reboot at that exact moment if the power supply is insufficient. A capacitor has been added to reduce the risk, and while it improves stability, the issue may still occur during Bluetooth startup.

## Arduino IDE Setup

This URL must be added to the "Additional Boards Manager URLs" (in Files / Preferences) : https://dl.espressif.com/dl/package_esp32_index.json

Some dependencies must be added:

- ESP32-BLE-Gamepad (with NimBLE-Arduino dependency)
- U8g2 by Oliver (for screen)

## Hardware

- [Lolin D32 WROOM (ESP32) µc](https://fr.aliexpress.com/item/1005006233798203.html)
- [OLED 0,96" SSD1306 I2C 128X64 pixels](https://fr.aliexpress.com/item/1005004355547926.html)
- [DE-9 female connector](https://fr.aliexpress.com/item/1005006997365476.html) aka DB9
- [Rotary Button EC11](https://fr.aliexpress.com/item/1005007737001031.html)
- [USB-C connector](https://fr.aliexpress.com/item/1005008400775423.html) (not mandatory)

## Additional documentation

- [Controllers pinout](/resources/controllers_pinout.md)
