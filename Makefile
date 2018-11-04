gcc -o main.o -c main.c
gcc -o main main.o -lncursesw
rm -f main.o