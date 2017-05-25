# BOFDemo: A simple buffer overflow vulnerability demo for IA-32
# Copyright (c) 2015-2017 Takuo Watanabe

CC = gcc
CFLAGS = -std=c11 -pedantic -Wall -Wextra -Werror -m32 -fno-stack-protector -g
LDFLAGS = -z execstack

OBJCOPY = objcopy
RM = rm -f

RET_OFF   = 20
SC_ADDR  = 0xbfffeb8c
#SC_ADDR  = 0xffffcb7c

.PHONY: all data clean allclean

all: demo mkattack shellcode.bin

data: normal.dat attack.dat

shellcode.o: shellcode.s
	$(CC) -m32 -c $<

shellcode.bin: shellcode.o
	$(OBJCOPY) -O binary $< $@

normal.dat:
	echo 1234 > $@

attack.dat: shellcode.bin mkattack
	./mkattack shellcode.bin $(RET_OFF) $(SC_ADDR) > $@

clean:
	$(RM) demo mkattack
	$(RM) *.o *.bin

allclean: clean
	$(RM) shellcode.bin
	$(RM) *.dat
	$(RM) a.out
	$(RM) *~ .DS_Store

