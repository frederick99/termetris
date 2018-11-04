gcc -o main.c -c main.c
gcc -o main main.o -lncurses
rm -f main.o