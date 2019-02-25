CC = gcc
CFLAGS = -g -Wall

SQLOBJS = sqlite3.o sqltest.o

.PHONY: clean

sqltest: $(SQLOBJS)
	$(CC) $(CFLAGS) -o sqltest $(SQLOBJS)

sqltest.o: sqltest.c
	$(CC) $(CFLAGS) -c -o sqltest.o sqltest.c

sqlite3.o: sqlite3.c sqlite3.h
	$(CC) $(CFLAGS) -c -o sqlite3.o sqlite3.c

clean:
	rm -rf $(SQLOBJS) sqltest
