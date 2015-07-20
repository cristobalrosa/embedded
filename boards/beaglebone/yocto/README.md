# Playing with yocto
Let's build a brand new BSP for our BeagleBone Black (rev C). 

## Debuging using a serial connection
Before starting to build our new beaglebone image, it's highly recommendable to set up a USB to TTL Serial interface for debug purposes and to modify u-boot parameters as needed.

To do that I've used the USB-TTL [Adafruit PL2303]. I bought this cable to use it with my Raspberry Pi but you can usi it with the BBB. It works perfectly and it's quite cheap. There are some other options, you can see them here: [BBB Accessories]

Once you get your USB-TTL cable, you can connect as follow:

![Serial Connection](https://raw.githubusercontent.com/cristobalrosa/embedded/master/boards/beaglebone/yocto/images/SerialConnection.jpg)

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
## Setting up our yocto environment

First, you need to download yocto in your PC, to do that follow this [instructions].
Fido is the name of the stable branch at time of writting this document.

Once you get yocto installed, let's create our working environment:
```bash
source oe-init-build-env build_bbb
```
Now, inside the build_bbb/conf folder we have a local.conf file, that is used by bitbake to create our image.
To build our bbb image I've modified the following values
```bash
MACHINE ?= "beaglebone"
# This is the folder I use to downlod all the packages. This way I can share it between projects
DL_DIR ?= "/home/<myuser>/work/yocto/download_cache/"
# I prefer to use debian like packages
PACKAGE_CLASSES ?= "package_deb"
# let's build the sdk and add an ssh server to our image
EXTRA_IMAGE_FEATURES = "debug-tweaks tools-sdk tools-debug ssh-server-dropbear"
```
and thats all, now we are ready to bake our image:

```bash
bitbake core-image-base
```

After a while we will have our artefact built under the folder /tmp/deploy/images/beaglebone/

## Formatting the SD card

```bash
fdisk -lu /dev/mmcblk0
mkfs.vfat -F 16 -n "boot" /dev/mmcblk0p1 
mke2fs -j -L "root" /dev/mmcblk0p2
```

### Copy the MLO, u-boot image and rootfs to the sdcard.

```bash
cp ./tmp/deploy/images/beaglebone/{MLO,u-boot.img,zImage} /media/myuser/boot
cp ./tmp/deploy/images/beaglebone/zImage-am335x-boneblack.dtb /media/myuser/boot/dtb
sudo tar xpf ./tmp/deploy/images/beaglebone/core-image-minimal-beaglebone.tar.bz2 -C /media/myuser/rootfs
sync 
```

### Create uEnv.txt file in /media/myuser/boot/uEnv.txt

This file will be used by uboot to boot the kernel.

```bash
cat << 'EOF' > /media/myuser/boot/uEnv.txt
bootargs=console=ttyO0 earlyprintk root=/dev/mmcblk0p2 rw
bootcmd=mmc rescan; fatload mmc 0 0x80200000 zImage; fatload mmc 0 0x82000000 dtb; bootz 0x80200000 - 0x82000000
uenvcmd=boot

EOF
```

## Time to boot the beaglebone
![Booting our new image](https://raw.githubusercontent.com/cristobalrosa/embedded/master/boards/beaglebone/yocto/images/PokyRunning.jpg)
## References
* [Yocto Project]
* [Texas Instruments AM335x U-Boot User's guide]
* [Free Electrons] One of the best resources for embedded engineers.
[instructions]:http://www.yoctoproject.org/docs/1.8/ref-manual/ref-manual.html#intro-requirements
[Yocto Project]: https://www.yoctoproject.org/
[Texas Instruments AM335x U-Boot User's guide]:http://processors.wiki.ti.com/index.php/AM335x_U-Boot_User's_Guide
[Adafruit PL2303]:http://www.adafruit.com/product/954
[BBB Accessories]:http://elinux.org/Beagleboard:BeagleBone_Black_Accessories#Adafruit_4_Pin_Cable_.28PL2303.29
[Free Electrons]: http://free-electrons.com/training/yocto/
