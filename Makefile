CC=gcc
CFLAGS=-Wall -I.
DEPS=myBank.h
SLFLAGS=-lmyBank

.PHONY: all
all: mains maind

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

libmyBank.a: myBank.o
	ar rcs libmyBank.a myBank.o

libmyBank.so: myBank.o
	$(CC) $(CFLAGS) -fPIC -c myBank.c
	$(CC) -shared myBank.o -o libmyBank.so
	
	
mybanks: libmyBank.a
	
mybankd: libmyBank.so
	
mains: main.o libmyBank.a
# 	$(CC) -L. main.o -lmyMath -o mains
	$(CC) -o mains main.o libmyBank.a

maind: main.o libmyBank.so
	$(CC) -o maind main.o libmyBank.so
	sudo cp libmyBank.so /usr/lib/
	sudo ldconfig

.PHONY: clean
clean:
	-rm -f mains maind *.o *.a *.so
