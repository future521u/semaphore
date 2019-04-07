main: main.o semaphore.o

main.o:main.c
	gcc -c main.c -o main.o
semaphore.o:semaphore.c
	gcc -c semaphore.c -o semaphore.o

.PHONY:clean
clean:
	rm -rf *.o main
