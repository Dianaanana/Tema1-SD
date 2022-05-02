CC = gcc
CFALGS = -Wall -Wextra -std=c99

build:
	$(CC) $(CFLAGS) tema1.c CircularDoublyLinkedList.c -o tema1
	
run:
	./tema1

clean:
	rm -r tema1
