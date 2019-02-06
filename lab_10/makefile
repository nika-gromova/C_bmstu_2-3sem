CC := gcc
PARAMS := -std=c99 -Wall -Werror -pedantic

ifeq ($(mode), debug)
	PARAMS += -g3
endif
ifeq ($(mode), drmemory)
	PARAMS += -ggdb
endif

app.exe: main.o io.o list.o
	$(CC) -o $@ $^
	
test.exe: test.o io.o list.o
	$(CC) -o $@ $^
	
main.o: main.c defines.h io.h structure.h list.h
	$(CC) $(PARAMS) -c $<

test.o: test.c defines.h io.h structure.h list.h
	$(CC) $(PARAMS) -c $<

io.o: io.c io.h defines.h structure.h list.h
	$(CC) $(PARAMS) -c $<

list.o: list.c list.h structure.h
	$(CC) $(PARAMS) -c $<

clean:
	rm *.exe *.o