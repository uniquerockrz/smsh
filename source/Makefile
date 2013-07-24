# Embarrassing little makefile.
# Barely works.
# Remove -ggdb from CFLAGS if you don't likey debug symbols for gdb.
# Feel free to edit and improve this. I suck with makefiles.
# I plan on using CMake once I get back to working on this.
# Till then, let your eyes bleed on this makefile. :3

# - Krishnashish Gogoi

 

CFLAGS = -Wall -ggdb -std=c99
LDFLAGS = -lcurl

all: smsh

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
	
smsh: main.o get_page.o start.o trim.o analyze.o
	${CC} ${CFLAGS} start.o get_page.o trim.o analyze.o main.o -o smsh ${LDFLAGS}

clean:
	rm -rf *.o smsh
