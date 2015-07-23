# Building a Raspberry pi image for QEMU
If you want to develop something for raspberry pi it's a good idea to have a way
to test it before putting it on the real target (Well, maybe using raspberry this is not entirely true), or maybe you don't have a raspberry, etc. Anyhow, virtualizing it's an efficient way to develop applications for embedded targets, at least when you're starting. 

## Requirements
To virtualize using QEMU, we will need qemu installed on your system, obviously xD

I'm using debian as host system, so to install QEMU I just have to type the following command:
```bash
sudo apt-cache update
sudo apt-get install qemu
```
If you're using a different distribution you here you are a couple of references that may help you:
* [QEMU] 
* [Install QEMU]

[QEMU]:http://wiki.qemu.org/Manual
[Install QEMU]: http://en.wikibooks.org/wiki/QEMU/Installing_QEMU

## Using a raspberry pi image for QEMU
To start, we're going to use a functional Raspberry pi image, later we could try to build a custom raspberry pi image using the [yocto] project tools.
[yocto]:https://www.yoctoproject.org/

We have to bear in mind some [data]:
* Raspberry PI CPU:  [ARM1176JZF-S]
[data]:http://en.wikipedia.org/wiki/Raspberry_Pi 
[ARM1176JZF-S]:http://www.arm.com/products/processors/classic/arm11/arm1176.php

To see if your qemu installation supports this cpu run the following command:
```bash
 qemu-arm -cpu ?
Available CPUs:
  arm1026
  arm1136
  arm1136-r2
  arm1176
  arm11mpcore
  arm926
  arm946
  cortex-a15
  cortex-a8
  cortex-a9
  cortex-m3
  pxa250
  pxa255
  pxa260
  pxa261
  pxa262
  pxa270-a0
  pxa270-a1
  pxa270
  pxa270-b0
  pxa270-b1
  pxa270-c0
  pxa270-c5
  sa1100
  sa1110
  ti925t
  any
```

As you can see on the list the CPU is supported. 

So, now we need to download a valid raspberry pi image ready to go. In my case I will use raspbian, 
because Debian is the distribution that makes me feel comfortable.

```bash
wget -c http://downloads.raspberrypi.org/raspbian_latest
```
You can take a look to the [download] page at raspberry.com for other options. 
[download]:http://www.raspberrypi.org/downloads/


When the download finishes, you will have a file like YYYY-MM-DD-wheezy-raspbian.zip
the next step will be to extract this file, to do that just use unzip command.
The image could need 3GB of space in your HDD. 
```bash
unzip 2013-09-25-wheezy-raspbian.zip
```

We now have a raspbian image ready to be launched, but we will need a kernel! 
```bash
wget http://xecdesign.com/downloads/linux-qemu/kernel-qemu
```
You can compile your own kernel, [here] you are the instructions. It's a great exercise
[here]:http://xecdesign.com/compiling-a-kernel/

Now we have all the files that we need to run an emulated raspberry with QEMU.
But, before start up our raspberry, we will resize the raspbian image, but why? Because we will need 
some extra space to install our applications.

You can do that by running the following command:
```bash
qemu-img resize 2014-09-09-wheezy-raspbian.img +3G
```

**First Boot**

We have to modify a few things before booting our image in a "normal" way. To do that we're going 
to start up the raspberry pi image with a root shell. This way, we could have our image mounted,
and we can modify what we want.

```bash
qemu-system-arm -kernel kernel-qemu -cpu arm1176 -m 256 -M versatilepb -append "root=/dev/sda2 panic=1 init=/bin/sh rw" -hda ./2014-09-09-wheezy-raspbian.img
```

Where:
* **-cpu:** CPU model
* **-m**: RAM memory
* **-M**: Emulated machine type.[versatile]
* **-append**: Kernel command line. Init a root shell
* **-had**: The HDD image file. 
[versatile]:http://www.arm.com/products/tools/development-boards/versatile/platform-baseboards.php

Once the raspbi has started up, we have to follow the next steps:
* Edit the file /etc/ld.so.preload, and comment out the line /usr/lib/arm-linux-gnueabihf/libcofi_rpi.so. You can do that by appending a '#':
```sh
#/usr/lib/arm-linux-gnueabihf/libcofi_rpi.so
```

* Create a file  /etc/udev/rules.d/90-qemu.rules with the following content:
```bash
KERNEL=="sda", SYMLINK+="mmcblk0"
KERNEL=="sda?", SYMLINK+="mmcblk0p%n"
KERNEL=="sda2", SYMLINK+="root"
```
This will create links to the sda as mmcblk0, that is the device which raspi sees. (Memory Card)
And that all, no you can start up your emulated raspi running:
```sh
```

## References
This doc is only a summary for the instructions that the following references give us. Thanks guys for sharing.
* [xecdesign]
* [www.linux-mitterteich.de]
* [BCM2835 GPIO Lib]

[xecdesign]:http://xecdesign.com/qemu-emulating-raspberry-pi-the-easy-way/
[www.linux-mitterteich.de]:http://www.linux-mitterteich.de/fileadmin/datafile/papers/2013/qemu_raspiemu_lug_18_sep_2013.pdf
[BCM2835 GPIO Lib]:http://www.airspayce.com/mikem/bcm2835/
