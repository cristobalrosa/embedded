#!/bin/bash
qemu-system-arm -kernel kernel-qemu -cpu arm1176 -m 256 -M versatilepb -append "root=/dev/sda2 panic=1" -hda ./2014-09-09-wheezy-raspbian.img
