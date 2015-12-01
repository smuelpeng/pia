CFLAGS  +=
LDLIBS  += -lcunit -lpia
LDFLAGS += -L..
CFLAGS  += -I..

default : all

include ../Common.mk

all : unit

test : unit
	./unit

OBJ = main.o tests.o tests_pia.o

RUBBISH += $(OBJ) unit

unit : $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) $(LDLIBS) -o unit

clean :
	$(RM) $(RUBBISH)

.PHONY : default all test clean
