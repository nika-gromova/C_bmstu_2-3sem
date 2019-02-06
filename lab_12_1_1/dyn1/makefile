CC := gcc
PARAMS := -std=c99 -Wall -Werror -pedantic
DEF := -D EXPORT
OBJ := io.o filter.o sort.o
H_FILES := arr_lib.h defines.h

ifeq ($(mode), debug)
	PARAMS += -g3
endif

ifeq ($(mode), drmemory)
	PARAMS += -ggdb
endif

io.o: io.c $(H_FILES)
	$(CC) $(PARAMS) $(DEF) -c $<
	
filter.o: filter.c $(H_FILES)
	$(CC) $(PARAMS) $(DEF) -c $<
	
sort.o: sort.c $(H_FILES)
	$(CC) $(PARAMS) $(DEF) -c $<
	
arr.dll: $(OBJ)
	$(CC) -shared $^ -Wl,--subsystem,windows -o $@
	
main.o: main.c $(H_FILES)
	$(CC) $(PARAMS) -c $<
	
app.exe: main.o arr.dll
	$(CC) $< -L. -larr -o $@
	
test.o: test.c $(H_FILES)
	$(CC) $(PARAMS) -c $<
	
test.exe: test.o arr.dll
	$(CC) $< -L. -larr -o $@
	
clean:
	rm *.o *.exe *.dll
