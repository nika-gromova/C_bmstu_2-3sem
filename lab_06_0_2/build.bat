gcc -std=c99 -Wall -Werror -c main.c
gcc -std=c99 -Wall -Werror -c io.c
gcc -std=c99 -Wall -Werror -c get_max.c
gcc -std=c99 -Wall -Werror -o get_max_sum.exe main.o io.o get_max.o