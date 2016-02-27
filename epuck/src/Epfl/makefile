# LIBRARY MAKEFILE
#------------------------------
ROOT = ../..
LIB_TARGET = E-puck

LIBS = 
INCS = 
OPTS = -Wall -g


# don't modify what is below ...
#------------------------------

ASM_SRCS 	= $(wildcard *.s)
C_SRCS 		= $(wildcard *.c)
SRCS 		= $(C_SRCS) $(ASM_SRCS)
HDRS 		= $(wildcard *.h) $(wildcard *.inc)
OBJS 		= $(addsuffix .o,$(basename $(SRCS)))

CC	  	= pic30-elf-gcc
AS	  	= pic30-elf-as
BIN2HEX  	= pic30-elf-bin2hex
AR		= pic30-elf-ar
RANLIB		= pic30-elf-ranlib

CC_FLAGS 	= -mcpu=30f6014a -I/usr/pic30-elf/include -O2
AS_FLAGS 	= -I/usr/share/pic30-support/inc -p=30f6014a
LD_FLAGS 	= -Wl,--heap=512,-L/usr/pic30-elf/lib,-T/usr/share/pic30-support/gld/p30f6014a.gld


all : lib$(LIB_TARGET).a

lib$(LIB_TARGET).a : $(OBJS) 
	if [ ! -d $(ROOT)/include ]; then mkdir $(ROOT)/include; fi
	cp *.h $(ROOT)/include
	$(AR) cru $@ $(OBJS) 
	$(RANLIB) $@
	if [ ! -d $(ROOT)/lib ]; then mkdir $(ROOT)/lib; fi
	cp $@ $(ROOT)/lib/

$(OBJ) : %.o : %.cpp %.h
	$(CC) $< $(DEBUG) $(OPTS) $(INCS) -I$(ROOT)/include


%.o : %.c %.h
	$(CC) $(CC_FLAGS) $(OPTS) $(INCS) -I$(ROOT)/include -c $< -o $(<:.c=.o)

%.o : %.c
	$(CC) $(CC_FLAGS) $(OPTS) $(INCS) -I$(ROOT)/include -c $< -o $(<:.c=.o)

%.o : %.s
	$(AS) $< $(AS_FLAGS) $(INCS) -I$(ROOT)/include -o $(<:.s=.o)


.PHONY : clean
clean : 
	rm -f *~ *.o *.a *.bak $(LIB_TARGET) core gmon.out  




