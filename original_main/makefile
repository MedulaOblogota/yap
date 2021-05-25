BASE = ./
PROJECT = ../../

INCFL = $(PROJECT)include/
OBJFL = $(PROJECT)bin/obj/
EXEFL = $(PROJECT)bin/exe/

SHARED_LIB = -lpthread -ldl ~/roy-yablonka/projects/bin/lib/*.so

CC = g++
CFLAGS = -ansi -g -pedantic-errors -Wall -Wextra -I $(INCFL)

SRC = $(wildcard *.hpp)

TEST_FILE = $(patsubst %.hpp, %_test.cpp, $(SRC))

DEPEND = $(patsubst %.hpp, %.d, $(SRC)) $(patsubst %.cpp, %.d, $(TEST_FILE))
OBJS = $(patsubst %.hpp, %.o, $(SRC))
TARGET = $(patsubst %.cpp, %.out, $(TEST_FILE))

PI = 0
ifeq ($(PI), 1)
CC = arm-linux-gnueabi-g++
endif

.PHONY: ALL
ALL:
	make TOUCH_TEMPS MOVE_TO_BASE CHECK_COMPILE MOVE_FROM_BASE

%.d: %.cpp
	@set -e; rm -f $@; \
	$(CC) -M $(CFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

%.o: %.cpp %.d $(SRC)
	$(CC) $(CFLAGS) $< -c

$(TARGET): $(SRC) *.cpp *.d
	$(CC) $(CFLAGS) $(TEST_FILE) *.o $(SHARED_LIB) -o $(TARGET)

.PHONY: TOUCH_TEMPS
TOUCH_TEMPS:
	touch $(OBJFL)tempytemp.o
	touch $(EXEFL)tempytemp.out

.PHONY: MOVE_TO_BASE
MOVE_TO_BASE:
	mv $(OBJFL)*.o $(BASE)
	rm tempytemp.o
	mv $(EXEFL)*.out $(BASE)
	rm tempytemp.out

.PHONY: CHECK_COMPILE
CHECK_COMPILE:
	echo CHECKS D FILES
	make $(DEPEND)
	echo CHECKS O FILES
	make $(OBJS)
	echo CHECKS OUT FILES
	make $(TARGET)

.PHONY: MOVE_FROM_BASE
MOVE_FROM_BASE:
	mv $(BASE)*.o $(OBJFL)
	mv $(BASE)*.out $(EXEFL)

.PHONY: CLEAN
CLEAN:
	rm *.d
