CC := gcc
PARAMS := -std=c99 -Wall -Werror -pedantic
OBJ := io.o filter.o sort.o

ifeq ($(mode), debug)
	PARAMS += -g3
endif
ifeq ($(mode), release)
	PARAMS += -DNDEBUG -g0
endif
ifeq ($(mode), drmemory)
	PARAMS += -ggdb
endif

app.exe: $(OBJ) main.o
	$(CC) -o $@ $^
	
test.exe: $(OBJ) test.o
	$(CC) -o $@ $^

main.o: main.c io.h defines.h filter.h sort.h
	$(CC) $(PARAMS) -c $<
	
test.o: test.c io.h filter.h sort.h
	$(CC) $(PARAMS) -c $<
	
io.o: io.c io.h defines.h
	$(CC) $(PARAMS) -c $<
	
filter.o: filter.c filter.h defines.h
	$(CC) $(PARAMS) -c $<
	
sort.o: sort.c sort.h defines.h
	$(CC) $(PARAMS) -c $<
	
clean:
	rm *.o *.exe