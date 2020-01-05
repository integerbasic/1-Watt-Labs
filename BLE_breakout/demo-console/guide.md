This topic describes hardware and software setup necessary to access the command console of the RN4871 breakout board.  
This is a necessary preparation step for the BLE breakout demo.

- [Hardware](#hardware)
- [Terminal emulation](#terminal-emulation)
- [Command mode access](#command-mode-access)

### Hardware

The RN4871-BB has transmit and receive signal lines for serial communication using the RS-232 protocol.  
Most desktop computing systems no longer have serial ports, so typically a USB-to-serial device is necessary 
to connect a desktop computer to the device.  The first diagram here shows how a Sparkfun FTDI basic 
configured for 3.3 volts would be used. The 2nd diagram shows the wiring necessary if the FTDI basic is 
configured for 5 volts.

### Terminal emulation

This example uses the 'Putty' terminal emulator to access the RN4871 console.  You can get Putty here.  
It is available for many operating systems.  The default serial connection settings for the RN4871 UART are 
the same as the Putty defaults, with one exception; the speed.  The default speed for the RN4871 is 115200 baud.

So, for example, if you have connected your RN4871-BB to port 4 on a Windows system, 
the Putty dialog to initiate a terminal should look like this; 


Putty configuration dialog excerpt

This setting, found in the 'Terminal' section of the Putty configuration, is also helpful for uncluttered console output:

### Command mode access

Once you've connected the device and started the terminal emulator, 
the first thing you need to tell the device is to switch to command mode.  
This is done by typing three dollar-sign characters in the terminal emulator application.  
You will not see the characters in the terminal window, but the result should be a command prompt returned by the RN4871:

    CMD>

One basic command available is 'd' (display basic configuration).  Try pressing the 'd' key followed by 'enter' key.  
You should see something like this as a result:

    CMD> d
    BTA=D88039F80080
    Name=RN_BLE
    Connected=no
    Authen=2
    Features=0000
    Services=00
    CMD>

If you did not see the 'd' in the terminal when you typed it, you might also prefer to turn on 'echo'.  Do this by pressing the '+' key followed by the 'enter' key.  The device should respond like this:

    CMD> ECHO ON
    CMD>

Subsequent commands should be visible as you type them.

Now you have access to the RN4871 command mode console and can use it for the programming and 
configuration described in the other demos.
