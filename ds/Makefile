CC					= gcc
OBJFLAGS			= -ansi -pedantic-errors -Wall -Wextra -c
OUTFLAGS 			= -ansi -pedantic-errors -Wall -Wextra -o
IFLAG				= -I
LIB 				= lib.a
TARGETS				= scheduler tasks PriorityQueue UID sorted_list dlist
DEBUG 				= 1

INCLUDE 			?= include/
TESTDIR 			?= test/
LIBPATH				?= obj/
EXEC				?= executables/
CURRDIR				?= /home/student/roy-yablonka/ds/

AOUT				:= $(TARGETS:=.out)
OBJFILES			:= $(TARGETS:=.o)
deps				:= $(OBJFILES:.o=.d)

ifeq ($(DEBUG),1)
OBJFLAGS += -g
OUTFLAGS += -g
endif

all: $(AOUT)

.PRECIOUS: %_test.o

%.out: %_test.o $(LIB)
	$(CC) $^ -o $@

-include $(deps)

%.o: %.c
	$(CC) $(OBJFLAGS) -MMD -MP $< $(IFLAG) $(INCLUDE)

$(LIB): $(OBJFILES)
	ar -rc $@ $^

%_test.o: $(TESTDIR)%_test.c
	$(CC) $(OBJFLAGS) $< $(IFLAG) $(INCLUDE)

execute_%: $(CURRDIR)%
	date +"%D" >> log.txt
	date +"%T" >> log.txt
	$< >> log.txt
	echo >> log.txt
	echo >> log.txt

.PHONY: clean
clean:
	rm -f $(OBJFILES) *.out *.d *.txt *~
