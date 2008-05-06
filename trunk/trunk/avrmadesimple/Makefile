# Makefile for main.c for an AVR chip

#MICROCONTROLLER = atmega8515
MICROCONTROLLER = atmega8
SERIALPORT = /dev/cu.USA19H1a2P1.1
OPTIMIZE = -O2
PROGRAMMER = stk500v2
#MOREFUSES = -U hfuse:w:0xd9:m -U lfuse:w:0x24:m
MOREFUSES = 

# Processor frequency.
#     This will define a symbol, CPUFREQ, in all source code files equal to the
#     processor frequency. You can then use this symbol in your source code to
#     calculate timings. Do NOT tack on a 'UL' at the end, this will be done
#     automatically to create a 32-bit value in your source code.
#     Typical values are:
# CPUFREQ =  1000000
# CPUFREQ =  1843200
# CPUFREQ =  2000000
# CPUFREQ =  3686400
# CPUFREQ =  4000000
# CPUFREQ =  7372800
#CPUFREQ =  8000000
# CPUFREQ = 11059200
# CPUFREQ = 14745600
# CPUFREQ = 16000000
# CPUFREQ = 18432000
# CPUFREQ = 20000000
# CPUFREQ = 10000000 
CPUFREQ    = 3686400   
#(default for stk500)

# ===========================================
# default target when "make" is run w/o arguments
all: main.rom

# compile main.c into main.o
main.o: main.c 
	avr-gcc -c -g ${OPTIMIZE} -Wall -DF_CPU=${CPUFREQ} -mmcu=${MICROCONTROLLER} main.c -o main.o

# link up main.o and letters.o into main.elf
main.elf: main.o
	avr-gcc main.o -Wall,-nm,-Map=main.map,--cref -mmcu=${MICROCONTROLLER} -o main.elf

# copy ROM (FLASH) object out of main.elf into main.rom
main.rom: main.elf
	avr-objcopy -O ihex main.elf main.rom

# command to program chip (invoked by running "make install")
install:
	avrdude -p ${MICROCONTROLLER} -c ${PROGRAMMER} -P ${SERIALPORT} -e -U flash:w:main.rom ${MOREFUSES}

# command to clean up junk (no source files) (invoked by "make clean")
clean:
	rm -f *.o *.rom *.elf *.map *~

# avrdude interactive mode
interactive:
	avrdude -p ${MICROCONTROLLER} -c ${PROGRAMMER} -P ${SERIALPORT} -t

# sample uisp install command 
install_uisp:
	uisp -v=2 -dprog=${PROGRAMMER} -dserial=${SERIALPORT} -dpart=${MICROCONTROLLER} --erase --upload --verify if="main.rom"




# nice one too:
# OBJS =  file1.o \
#        file2.o
#EXE = exe
#
#all: $(EXE)
#$(EXE): $(OBJS)
#    gcc $(OBJS) -o $(EXE)
#
#.c.o:
#    gcc -c -o $*.o $<
