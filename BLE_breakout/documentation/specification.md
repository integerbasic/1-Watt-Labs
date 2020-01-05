![Part](pinout.png){:width="250px"}

The BLE breakout board serves primarily to expose all the connections of the RN4871 module in a form-factor that is easier for use on a breadboard or other prototype environment.

Four additional features are included:

* A 3.3 volt regulator is included.  The RN4871 module operates at 3.3 volts; this regulator makes it easier to incorporate the RN4871 in a system with a higher supply voltage.
* A jumper is included to put the device into flash-program mode.
* A blue LED is connected to the RN4871 'mode' signal (LED0).  This LED flashes slowly when disconnected.  It flashes faster when connected.
* An orange LED is attached to the RN4871 'tx' signal.  Flashes whenever data is emitted on the module serial line, which is typically when the device is in 'transparent UART' mode and is receiving data over the air.

Two demonstration topics are available to assist in developing with this device:

A guide for accessing the console of the device: BLE breakout console
A demonstration of remote-control of a digital signal: BLE breakout demo
