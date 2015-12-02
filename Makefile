LIB = libpia.a
OBJ = pia.o

default : all

include Common.mk

all : $(LIB)

$(LIB) : $(OBJ)
	ar rs $(LIB) $(OBJ)

test : $(LIB)
	$(MAKE) -C test test

doc :
	$(MAKE) -C doc all

clean :
	$(RM) $(LIB) $(OBJ)
	$(MAKE) -C test clean
	$(MAKE) -C doc clean

scan-build :
	scan-build -v -o /tmp $(MAKE)

.PHONY : default test doc clean scan-build
