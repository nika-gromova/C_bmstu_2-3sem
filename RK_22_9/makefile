CC := gcc
PARAMS := -std=c99 -Wall -Werror

main.exe : main.o input.o process.o print.o
	$(CC) -o main.exe $^
tests.exe : tests.o input.o process.o print.o
	$(CC) -o tests.exe $^
	
input.o: input.c input.h
	$(CC) $(PARAMS) -c input.c
process.o: process.c process.h
	$(CC) $(PARAMS) -c process.c
print.o: print.c print.h
	$(CC) $(PARAMS) -c print.c
main.o: main.c input.h process.h print.h
	$(CC) $(PARAMS) -c main.c
tests.o: tests.c input.h process.h print.h
	$(CC) $(PARAMS) -c tests.c

clean:
	rm *.o *.exe