- [Overview](#overview)
- [Pinouts](#pinouts)
- [References](#references)

### Overview 

<img src="pinout.png" width="400px"/>

The BLE serial USB board makes the RN4871 module accessible from any PC or laptop.
Four additional hardware features are included:

1. A jumper is included to put the device into flash-program mode.
2. A blue LED is connected to the RN4871 'mode' signal (LED0).
   This LED flashes slowly when disconnected, and flashes faster when connected.
3. A red LED is connected to the RN4871 'tx' signal.
   It flashes whenever data is emitted on the module serial line, which is typically
   when the device is in 'transparent UART' mode and is receiving data over the air.
4. A green LED is connected to the RN4871 'rx' signal.
   It flashes whenever data is passed to the module on the serial line.

Two topics are available in the library to assist in developing with this device:

- [A guide for accessing the console of the device](../demo-console/guide.md)
- [A demonstration of communication between the device and a mobile phone application](../demo-pipe/guide.md)

### Pinouts

#### J1
Pin | Description
--- | -----------
1 | GND
2 | RN4871 System configuration input P0_2. Leave disconnected for normal operation. Jumper to ground to re-flash EEPROM.

### References
- [Schematic](schematic.svg)
- [Vendor home page for RN4871](https://www.microchip.com/wwwproducts/en/RN4871)
