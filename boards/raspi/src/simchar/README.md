#Simple Character Device
This is the simplest character device you can build. It's aims is to show you 
how to build a simple character device. I'll try to do something more smart soon, but little by little. 
The device itself does nothing. We only register the device, create a file_operation structure with the basic operations, create some functions for each operation and unregister the device. This code could be used as skeleton for more complicated devices. 

##Notes
* I upgraded my raspberry and I forgot to upgrade the kernel sources that I compiled last time for the kernel 3.10.25. Now, the kernel is 3.18.7 and it's much more easy to get the sources ready to go. But the thing is that when I was trying to test the simchar module I saw the following error:
```bash
Error: could not insert module simchar.ko: Invalid module format
# if you look at /var/log/messages, you will see something like
[  927.608394] simchar: disagrees about version of symbol module_layout
```
That means that you have compiled the module with a diferent kernel sources/configuration. (Thus it is as I realized that I had not updated the sources)

* In this module I'm using the older way to register a device, using the function **regiter_chrdev** There is another way to do that since 2.6 kernel versions. We will see this new way in a future version of simchar. 

* I'm using static major number allocation. This couldn't be the best approach. We will later how to get a dinamically allocated major number. 

## Steps to test the module
```bash
# Insert the module
sudo insmod simchar.ko
# Create a device file
sudo mknod -m 666 /dev/simchar c 200 0
$ ls -lah /dev/simchar 
crw-rw-rw- 1 root root 200, 0 mar  3 06:45 /dev/simchar
# See my module
cat /proc/modules  | grep simchar
simchar 1755 0 - Live 0xbf18e000 (O)
# Test the opeartions
cat /dev/simchar


# See the logs to check your device is working.. 
$ tail -f /var/log/kern.log
Mar  3 07:00:46 kktuapi kernel: [30345.873755] Simchar open..
Mar  3 07:00:46 kktuapi kernel: [30345.879136] Simchar read..
Mar  3 07:00:46 kktuapi kernel: [30345.885284] Simchar close..

```
