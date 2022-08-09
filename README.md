# nmtool
nmtool is a simple CLI for managing hotspot on Linux written in C++, make things easier since I'm too lazy to remember all the commands.

## Requirement
This program requires `dnsmasq` installed on your machine, so install it first.

## Features
- Create hotspot
- Activate hotspot
- Deactivate hotspot
- Show hotspot password
- Change hotspot password
- Delete hotspot

## Installation
For Arch users, it's available on [AUR](https://aur.archlinux.org/packages/nmtool):
```
yay -S nmtool
```
For other distro users:
```
sudo make install clean
```

## Uninstallation
```
sudo make uninstall
```
