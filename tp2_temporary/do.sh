rm *.o
gcc -c *.c -Wall
gcc -o run *.o
valgrind -v --leak-check=full --show-leak-kinds=all ./run
