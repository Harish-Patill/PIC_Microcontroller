# PIC_Microcontroller

Embedded C programs for the PIC18F4580 microcontroller, written while learning its peripherals one by one. Each topic is built with MPLAB X and the XC8 compiler and flashed to the board with TimuBootloaderPlus.

## Toolchain

- **MCU:** PIC18F4580 (Microchip)
- **IDE:** MPLAB X IDE
- **Compiler:** XC8
- **Flashing tool:** TimuBootloaderPlus
- **Language:** Embedded C

## How to Build

1. Open MPLAB X IDE.
2. Select **File > Open Project** and choose the topic folder.
3. Set the device to **PIC18F4580** and the compiler to **XC8**.
4. Click **Clean and Build**.

## How to Dump and Execute

1. Open the project directory.
2. Navigate to `dist/default/production/`.
3. Open **TimuBootloaderPlus**, select the `.hex` file, and load it onto the board.

## Author

GitHub: [Harish-Patill](https://github.com/Harish-Patill)