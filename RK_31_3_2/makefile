CC := gcc
PARAMS := -std=c99 -Wall -ggdb -Werror -pedantic

ifeq ($(mode), debug)
	$(PARAMS) += -g3
endif
ifeq ($(mode), drmemory)
	$(PARAMS) += -ggdb
endif

main.exe: main.o io.o process.o
	$(CC) -o $@ $^
	
test.exe: test.o process.o
	$(CC) -o $@ $^

test.o: test.c defines.h process.h structure.h
	$(CC) $(PARAMS) -c $<

main.o: main.c io.h defines.h process.h structure.h
	$(CC) $(PARAMS) -c $<

io.o: io.c io.h defines.h structure.h
	$(CC) $(PARAMS) -c $<
	
process.o: process.c process.h defines.h structure.h
	$(CC) $(PARAMS) -c $<
	
clean:
	rm *.o *.exe