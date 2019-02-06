CC := gcc
PARAMS := -std=gnu99 -Wall -Werror -pedantic

ifeq ($(mode), debug)
	PARAMS += -g3
endif
ifeq ($(mode), drmemory)
	PARAMS += -ggdb
endif
	
test_list.exe: test.o set_list.o
	$(CC) -o $@ $^
	
test_array.exe: test.o set_array.o
	$(CC) -o $@ $^
	
test.o: test.c set.h defines.h
	$(CC) $(PARAMS) -c $<

set_list.o: set_list.c set.h defines.h
	$(CC) $(PARAMS) -c $<
	
set_array.o: set_array.c set.h defines.h
	$(CC) $(PARAMS) -c $<
	
clean:
	rm *.o *.exe