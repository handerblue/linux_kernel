virtual box + Ubuntu18

copy/paste between Vbox and mac:
1. sudo apt install build-essential dkms linux-headers-$(uname -r)
2. from the Virtual Machine menu bar, go to Devices => click on Insert Guest Additions CD image. Run the installer to launch it.
3. Reboot
4. VBox menu->settings->general->Advanced->Shared Clipboard Bidirectional

How to compile Raspbian: 
https://www.raspberrypi.org/documentation/linux/kernel/building.md

Create Base Raspberry Pi Image:
https://www.raspberrypi.org/downloads/

VM Mount SD card
https://www.geekytidbits.com/mount-sd-card-virtualbox-from-mac-osx/
