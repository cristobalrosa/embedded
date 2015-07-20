# Playing with yocto
Let's build a brand new BSP for our BeagleBone back (rev C). 

## Debuging using a serial connection
Before starting to build our new beaglebone image, it's highly recommendable to set up a USB to TTL Serial interface for debug purposes and to modify u-boot parameters as needed.

To do that I've used the USB-TTL [Adafruit PL2303]. I bought this cable to use it with my Raspberry Pi but you can usi it with the BBB. It works perfectly and it's quite cheap. There are some other options, you can see them here: [BBB Accessories]

Once you get your USB-TTL cable, you can connect as follow:

![Serial Connection](https://raw.githubusercontent.com/cristobalrosa/embedded/master/boards/bbb/yocto/images/SerialConnection.jpg)

## Boot the beaglebone
![Booting our new image](https://raw.githubusercontent.com/cristobalrosa/embedded/master/boards/bbb/yocto/images/PokyRunning.jpg)

## References
* [Yocto Project]
* [Texas Instruments AM335x U-Boot User's guide] 
[Yocto Project]: https://www.yoctoproject.org/
[Texas Instruments AM335x U-Boot User's guide]:http://processors.wiki.ti.com/index.php/AM335x_U-Boot_User's_Guide
[Adafruit PL2303]:http://www.adafruit.com/product/954
[BBB Accessories]:http://elinux.org/Beagleboard:BeagleBone_Black_Accessories#Adafruit_4_Pin_Cable_.28PL2303.29
