CC := gcc
PARAMS := -std=c99 -Wall -Werror -pedantic
DEF := -D EXPORT
OBJ := io.o filter.o sort.o
H_FILES := .\..\dyn1\arr_lib.h defines.h

ifeq ($(mode), debug)
	PARAMS += -g3
endif

ifeq ($(mode), drmemory)
	PARAMS += -ggdb
endif

io.o: .\..\dyn1\io.c $(H_FILES)
	$(CC) $(PARAMS) $(DEF) -c $<
	
filter.o: .\..\dyn1\filter.c $(H_FILES)
	$(CC) $(PARAMS) $(DEF) -c $<
	
sort.o: .\..\dyn1\sort.c $(H_FILES)
	$(CC) $(PARAMS) $(DEF) -c $<
	
arr.dll: $(OBJ)
	$(CC) -shared $^ -Wl,--subsystem,windows -o $@

app.exe: main_d2.c defines.h arr.dll
	$(CC) $(PARAMS) $< -o $@
	
test.exe: test_d2.c defines.h arr.dll
	$(CC) $(PARAMS) $< -o $@
	
clean:
	rm *.exe *.dll *.o