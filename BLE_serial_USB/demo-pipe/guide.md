This topic demonstrates communication over Bluetooth Low Energy, using the 'transparent UART' mode of the RN4871.
One end of the communication link is a BLE serial USB device, attached to a workstation with a terminal emulator.
The other end is a mobile phone running a test application.

- [Configure the RN4871](#configure-the-rn4871)
  + [Activate the service](#activate-the-service)
- [Run the test application](#run-the-test-application)
- [Screenshots of Smart Data](#screenshots-of-smart-data)

### Configure the RN4871

Connect the BLE serial USB device to a laptop or workstation and enter the command mode as described [here](../demo-console/guide.md). 

#### Activate the service

Enter these commands:

    CMD> ss,c0
    AOK
    CMD> r,1
    Rebooting

The 'ss' command controls what services are made available by the device.  The 'c0' value designates the 'Device Information' service and the 'UART Transparent' service. The 'r' command reboots the device to insure the services are active.  Rebooting the device also terminates the command mode.

Leave the terminal emulator running to serve as one end of the communication link.

### Run the test application

We can use the *Bluetooth Smart Data* application by _Microchip Technology Inc._  as the other end of our communication link.  This application is available for iPhones and Android phones.  Search for the name in the app-store on your mobile phone of choice.

Run the application.  Discovered devices are listed (screen 1 below).  Select your device for connection.  The default application tab for a connected device is labeled as 'MLDP data' and provides access to the 'UART transparent' service (screen 2 below).

- Type characters in the text-entry box and press 'Send' in the SmartData application, and they will appear in the terminal emulator attached to the BLE serial USB device.
- Type characters in the terminal emulator attached to the BLE serial USB device, and they will appear in the SmartData application window.

### Screenshots of Smart Data

1. Scan and connect

2. Access service
