BASE = ./
PROJECT = ../../

INCFL = $(PROJECT)include/
OBJFL = $(PROJECT)bin/obj/

CC = g++
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -I $(INCFL)

SRC = $(wildcard *.cpp)

DEPEND = $(patsubst %.cpp, %.d, $(SRC))
OBJS = $(patsubst %.cpp, %.o, $(SRC))

PI = 0
ifeq ($(PI), 1)
CC = arm-linux-gnueabi-g++
endif

.PHONY: ALL
ALL:
	make TOUCH_TEMPS MOVE_TO_BASE CHECK_COMPILE MOVE_FROM_BASE REMOVE_TEMPS

%.d: %.cpp
	@set -e; rm -f $@; \
	$(CC) -M $(CFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

%.o: %.cpp %.d
	$(CC) $(CFLAGS) $< -c

.PHONY: TOUCH_TEMPS
TOUCH_TEMPS:
	touch $(OBJFL)tempytemp.o

.PHONY: MOVE_TO_BASE
MOVE_TO_BASE:
	mv $(OBJFL)*.o $(BASE)

.PHONY: CHECK_COMPILE
CHECK_COMPILE:
	echo CHECKS D FILES
	make $(DEPEND)
	echo CHECKS O FILES
	make $(OBJS)

.PHONY: MOVE_FROM_BASE
MOVE_FROM_BASE:
	mv $(BASE)*.o $(OBJFL)

.PHONY: REMOVE_TEMPS
REMOVE_TEMPS:
	rm $(OBJFL)tempytemp.o

.PHONY: CLEAN
CLEAN:
	rm *.d