# sample makefile for testing purposes

CFLAGS = -Wall -ggdb -std=c99
LDFLAGS = -lcurl


get_page.o:
	${CC} ${CFLAGS} -c get_page.c

start.o:
	${CC} ${CFLAGS} -c start.c
	
main.o:
	${CC} ${CFLAGS} -c main.c
	
trim.o:
	${CC} ${CFLAGS} -c trim.c
	
analyze.o:
	${CC} ${CFLAGS} -c analyze.c
	
smsfork: main.o get_page.o start.o trim.o analyze.o
	${CC} ${CFLAGS} start.o get_page.o trim.o analyze.o main.o -o smsfork ${LDFLAGS}

clean:
	rm -rf *.o smsfork
