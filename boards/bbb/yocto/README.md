# Playing with yocto
Let's build a brand new BSP for our BeagleBone back (rev C). 

## Debuging using a serial connection
Before starting to build our new beaglebone image, it's highly recommendable to set up a USB to TTL Serial interface for debug purposes and to modify u-boot parameters as needed.

To do that I've used the USB-TTL [Adafruit PL2303]. I bought this cable to use it with my Raspberry Pi but you can usi it with the BBB. It works perfectly and it's quite cheap. There are some other options, you can see them here: [BBB Accessories]

Once you get your USB-TTL cable, you can connect as follow:

![Serial Connection](https://raw.githubusercontent.com/cristobalrosa/embedded/master/boards/bbb/yocto/images/SerialConnection.jpg)

Now you are almost ready to start up a serial communication with your BBB, but before you can do that, you need to know 
which device is your system using for the PL2303 cable.

Plug the cable into the usb and checkout the kern.log file, you will see something like this:
```bash
Jul 20 16:29:07 devel kernel: [   13.730974] pl2303 1-1.3:1.0: pl2303 converter detected
Jul 20 16:29:07 devel kernel: [   13.732439] usb 1-1.3: pl2303 converter now attached to ttyUSB0
```

You need to add your user to the dialout group, since the device is allowed to use for this group
```bash
ls -lah /dev/ttyUSB0 
0 crw-rw---- 1 root dialout 188, 0 jul 20 17:06 /dev/ttyUSB0

sudo adduser YOUR_USER dialout
```

Now you can use whatever app you want, to communicate with your BBB using the serial port. (minicom, picocom, screen...) 

For the sake of simplicity I will use picocom, since I think is the easy one to use. 
```bash
 picocom -b 115200 /dev/ttyUSB0 
picocom v1.7

port is        : /dev/ttyUSB0
flowcontrol    : none
baudrate is    : 115200
parity is      : none
databits are   : 8
escape is      : C-a
local echo is  : no
noinit is      : no
noreset is     : no
nolock is      : no
send_cmd is    : sz -vv
receive_cmd is : rz -vv
imap is        : 
omap is        : 
emap is        : crcrlf,delbs,

Terminal ready

```

## Boot the beaglebone
![Booting our new image](https://raw.githubusercontent.com/cristobalrosa/embedded/master/boards/bbb/yocto/images/PokyRunning.jpg)

## References
* [Yocto Project]
* [Texas Instruments AM335x U-Boot User's guide] 
[Yocto Project]: https://www.yoctoproject.org/
[Texas Instruments AM335x U-Boot User's guide]:http://processors.wiki.ti.com/index.php/AM335x_U-Boot_User's_Guide
[Adafruit PL2303]:http://www.adafruit.com/product/954
[BBB Accessories]:http://elinux.org/Beagleboard:BeagleBone_Black_Accessories#Adafruit_4_Pin_Cable_.28PL2303.29
