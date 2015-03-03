# Compiling modules for raspberry   
Apparently this is something that should be difficult, but since it could be. 
I have been trying to find my raspberry kernel source to be able to compile some kernel modules for it, and it has been really hard, xD

So I decided to write some notes here about how I've got my modules compiled. 

## Step 1: What is my kernel versión?
Before attemting to get the kernel version you have, upgrade your raspberry code:
```bash
sudo apt-get update
sudo apt-get upgrade
```
After that, type 
```bash
uname -r
3.10.25+
```
## Step 2: Look for your kernel sources.... xD
This could be the hardest part...
I have followed the instructions on this [post] and finally I have got my kernel compiled. 
The steps are:
- Get the kernel sources;  ```git clone https://github.com/raspberrypi/linux.git```
- Get the firmware repo hash that matches your uname string from here: ```https://github.com/raspberrypi/firmware/blob/3a4ba0c3964f8f0ecc2dd46246a83258d9e4046d/extra/uname_string```
- Get the related githash ```https://github.com/raspberrypi/firmware/blob/3a4ba0c3964f8f0ecc2dd46246a83258d9e4046d/extra/git_hash```
- Checkout the code: ```git checkout 16eb921a96db3dc3555a65b53b99c15753e6b770 ```

**NOTE** I've upgrade my raspberry and now the kernel version is 3.18.7+.I've realized that 
for that version is much more easy to get the kernel soures. Just download the sources from thit 
repository and checkout to the branch.

```bash
git checkout rpi-3.18.y
```
## Step 3: Compile the kernel
Set a few environment variables:
```bash
export MODULES=$HOME/work/embedded/ldd.priv/src/modules
export KERNEL_SRC=$HOME/work/embedded/ldd.priv/src/linux
export CCPREFIX=$HOME/bin/raspitools/arm-bcm2708/arm-bcm2708-linux-gnueabi/bin/arm-bcm2708-linux-gnueabi-
``` 
Get the kernel configuration file from your raspberry:
```scp pi@youraspi:/proc/config.gz .```
Un tar this configuration on your linux folder:
```
zcat config.gz > .config; mv .config $KERNEL_SRC
```
Build the kernel
```
make ARCH=arm CROSS_COMPILE=${CCPREFIX} oldconfig
make ARCH=arm CROSS_COMPILE=${CCPREFIX} 
```
Now we are ready to compile our module...!
## Step 4: Compile the module
Create your simplemodule code and use this makefile
```bash
obj-m += hello.o
 
all:
        make  ARCH=arm CROSS_COMPILE=${CCPREFIX} -C ${KERNEL_SRC} M=$(PWD) modules

clean:
        make -C ${KERNEL_SRC} M=$(PWD) clean
```

[post]:https://github.com/raspberrypi/linux/issues/486 
## Step 5: Playing...
```
pi@myraspi ~/simplemodule $ uname -a
Linux myraspi 3.10.25+ #622 PREEMPT Fri Jan 3 18:41:00 GMT 2014 armv6l GNU/Linux

pi@myraspi ~/simplemodule $ sudo insmod hello.ko
pi@myraspi ~/simplemodule $ lsmod | grep hello
hello                    706  0 

pi@myraspi ~/simplemodule $ modinfo hello.ko
filename:       /home/pi/simplemodule/hello.ko
description:    A simple module to test my cross-compile environment
author:         Cristobal Rosa <cristobalrosa@gmail.com>
license:        GPL
srcversion:     AE1AB7B1BA97916068882E2
depends:        
vermagic:       3.10.25+ preempt mod_unload modversions ARMv6 

pi@myraspi ~/simplemodule $ tail -n 1 /var/log/kern.log 
Feb 25 22:31:37 myraspi kernel: [100691.448363] Hello from the raspi world

pi@myraspi ~/simplemodule $ sudo rmmod hello.ko
pi@myraspi ~/simplemodule $ tail -n 1 /var/log/kern.log
Feb 25 22:35:06 myraspi kernel: [100901.105449] Bye bye, have fun!


```
## References
* Brian Chavez Post http://bchavez.bitarmory.com/archive/2013/01/16/compiling-kernel-modules-for-raspberry-pi.aspx 
