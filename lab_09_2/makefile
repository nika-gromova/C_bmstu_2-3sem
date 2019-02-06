CC := gcc
PARAMS := -std=gnu99 -Wall -Werror -pedantic
OBJ := io.o str.o replace.o
ifeq ($(mode), debug)
	PARAMS += -g3
endif
ifeq ($(mode), drmemory)
	PARAMS += -ggdb
endif

app.exe: $(OBJ) main.o
	$(CC) -o $@ $^
	
test.exe: $(OBJ) test.o
	$(CC) -o $@ $^

main.o: main.c io.h str.h replace.h defines.h
	$(CC) $(PARAMS) -c $<
	
test.o: test.c io.h str.h replace.h defines.h
	$(CC) $(PARAMS) -c $<

io.o: io.c io.h str.h defines.h
	$(CC) $(PARAMS) -c $<

replace.o: replace.c str.h replace.h
	$(CC) $(PARAMS) -c $<

str.o: str.c str.h
	$(CC) $(PARAMS) -c $<
clean:
	rm *.o *.exe