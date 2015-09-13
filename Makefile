# BOFDemo: A simple buffer overflow vulnerability demo for IA-32

CC = gcc
CFLAGS = -std=c99 -pedantic -m32 -Wall -Werror \
	 -fno-stack-protector -mpreferred-stack-boundary=2
LDFLAGS = -z execstack

OBJCOPY = objcopy
RM = rm -f

BP_OFF   = 17
BP_VALUE = 0xbfffefe8
SC_ADDR  = 0xbfffeb80

.PHONY: all clean allclean

all: demo mkattack shellcode.bin

shellcode.o: shellcode.s
	$(CC) -m32 -c $<

shellcode.bin: shellcode.o
	$(OBJCOPY) -O binary $< $@

attack.dat: shellcode.bin mkattack
	./mkattack shellcode.bin $(BP_OFF) $(BP_VALUE) $(SC_ADDR) > $@

clean:
	$(RM) demo mkattack
	$(RM) *.o *.bin

allclean: clean
	$(RM) shellcode.bin
	$(RM) *.dat
	$(RM) a.out
	$(RM) *~ .DS_Store
