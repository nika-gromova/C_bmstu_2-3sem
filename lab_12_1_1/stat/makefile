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

app.exe: main.c libarr.a defines.h
	$(CC) $(PARAMS) $< libarr.a -o $@
	
test.exe: test.c libarr.a defines.h
	$(CC) $(PARAMS) $< libarr.a -o $@
	
io.o: io.c defines.h arr_lib.h
	$(CC) $(PARAMS) -c $<
	
filter.o: filter.c defines.h arr_lib.h
	$(CC) $(PARAMS) -c $<
	
sort.o: sort.c defines.h arr_lib.h
	$(CC) $(PARAMS) -c $<
	
libarr.a: $(OBJ)
	ar rc $@ $^
	ranlib $@
	
clean:
	rm *.o *.exe *.a