CC := gcc
PARAMS := -std=c99 -Wall -Werror
OBJ := io.o get_max.o

ifeq ($(mode), debug)
	PARAMS += -g3
endif
ifeq ($(mode), release)
	PARAMS += -DNDEBUG -g0
endif
get_max_sum.exe : $(OBJ) main.o
	$(CC) $(PARAMS) -o $@ $^
tests.exe: $(OBJ) tests.o
	$(CC) $(PARAMS) -o $@ $^
	
io.o : io.c io.h defines.h
	$(CC) $(PARAMS) -c $<
get_max.o : get_max.c get_max.h defines.h
	$(CC) $(PARAMS) -c $<

main.o : main.c io.h get_max.h defines.h
	$(CC) $(PARAMS) -c $<
	
tests.o : tests.c io.h get_max.h defines.h
	$(CC) $(PARAMS) -c $<

clean :
	rm *.o *.exe