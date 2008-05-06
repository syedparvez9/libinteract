
This is a sample make file for AVR. Change for your settings in the first few
lines of the "Makefile". 
Project from Leah Buechley 
http://www.cs.colorado.edu/~buechley/diy/avr_mac_osx.html

Makefile from Alexandre Quessy
http://alexandre.quessy.net


COMMANDS
================
make 
make install 
make clean 
make interactive


CONFIGURATION
================
For the parts list : 
http://www.nongnu.org/avrdude/user-manual/avrdude_4.html

MICROCONTROLLER = atmega8515
SERIALPORT = /dev/cu.USA19H1a2P1.1
OPTIMIZE = -O0
PROGRAMMER = stk500v2

