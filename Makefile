main:main.o parseAccess.o config.o cJSON.o queue.o
	gcc -o nlog main.o parseAccess.o config.o cJSON.o queue.o -L/usr/local/lib/ -lhiredis
main.o:src/main.c src/parseAccess.h src/config.h
	gcc -c src/main.c
parseAccess.o:src/parseAccess.c src/parseAccess.h
	gcc -c src/parseAccess.c
config.o:src/config.c src/config.h
	gcc -c src/config.c
cJSON.o:src/cJSON.c src/cJSON.h
	gcc -c src/cJSON.c
queue.o:src/queue.c src/queue.h
	gcc -c src/queue.c
