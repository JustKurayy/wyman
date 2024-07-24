# wyman
A simple terminal Wifi manager for bare-boned Debian 12

### How to install
Download the libiw library with `sudo apt install libiw-dev`
Use `make build` to compile the program

### How to use wyman
In terminal, use `sudo ./wyman <your interface card>`
Replace <your interface card> with wlan1, wlo1 or whatever interface card you have
You can find your interface card with `ip a` command in terminal

