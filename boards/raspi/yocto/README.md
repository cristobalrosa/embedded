# Yocto BSP for Raspberry

Let's build custom image for our Raspberry

## Using the USB-TTL

Within the beagleboard readme I talked about the USB-TTL cable I'm using and how I use it, so 
in this recipe, I will only show you where you should connect your pins:

![Serial Connection](https://raw.githubusercontent.com/cristobalrosa/embedded/master/boards/raspi/yocto/images/RaspiSerialConnection.jpg)

## Steps to create our Raspberry Image

* Download the meta-raspberry repository
```bash
git clone -b fido git://git.yoctoproject.org/meta-raspberrypi
```

* Create a new working environment
```bash
source oe-init-build-env build_raspberry
```

* Configure our local.conf
```
MACHINE ?="raspberrypi"
```
* Add the new layer to the file bblayers.conf
```
BBLAYERS ?= " \
  /home/user/Documentos/work/yocto/poky/meta \
  /home/user/Documentos/work/yocto/poky/meta-yocto \
  /home/user/Documentos/work/yocto/poky/meta-yocto-bsp \
  /home/user/Documentos/work/yocto/poky/meta-raspberrypi \
  "

```
* Execute the baker...
```bash
bitbake rpi-basic-image
```
If you want to build the sdk:
```bash
bitbake rpi-basic-image -c populate_sdk
```

* Finally copy the image to the SD card and boot you Raspi
```
sudo dd if=rpi-basic-image-raspberrypi.rpi-sdimg of=/dev/mmcblk0
```

## Add WIFI support

Modify the local.conf file and add the following line:
```
IMAGE_INSTALL_append = " wpa-supplicant wireless-tools dhcp-client linux-firmware"
```
Build and write the image again, and before the raspberry boots, configure your network interface.

```bash
root@raspberrypi:~# cat /etc/network/interfaces 
# /etc/network/interfaces -- configuration file for ifup(8), ifdown(8)
 
# The loopback interface
auto lo
iface lo inet loopback

# Wireless interfaces
auto wlan0
iface wlan0 inet dhcp
        wpa-conf /etc/wpa_supplicant.conf


root@raspberrypi:~# cat /etc/wpa_supplicant.conf 
ctrl_interface=/var/run/wpa_supplicant
ctrl_interface_group=0
update_config=1

network={
        ssid="YOUR_SSID"
        psk="YOUR_PASS"
        key_mgmt=YOUR MANAGEMENT METHOD
}
```
## References
* [Raspberry] Repo
[Raspberry]:http://git.yoctoproject.org/cgit/cgit.cgi/meta-raspberrypi/about/
