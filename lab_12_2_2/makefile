CC := gcc
PARAMS := -std=c99 -Wall -Werror -pedantic

ifeq ($(mode), debug)
	PARAMS += -g3
endif

ifeq ($(mode), drmemory)
	PARAMS += -ggdb
endif

array.o: array.c array_lib.h
	$(CC) $(PARAMS) -c $<
	
arr.dll: array.o
	$(CC) -shared $< -Wl,--subsystem,windows -o $@
	
test.o: test.c array_lib.h
	$(CC) $(PARAMS) -c $<

test.exe: test.o arr.dll
	$(CC) $< -L. -larr -o $@
	
clean:
	rm *.exe *.o *.dll