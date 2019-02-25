CC = gcc
CFLAGS = -g -Wall

DXTOBJS = dxt.o sqlite3.o

.PHONY: clean

dxt: $(DXTOBJS)
	$(CC) $(CFLAGS) -o dxt $(DXTOBJS)

dxt.o: interviewer.c
	$(CC) $(CFLAGS) -c -o dxt.o interviewer.c

sqlite3.o: sqlite3.c sqlite3.h
	$(CC) $(CFLAGS) -c -o sqlite3.o sqlite3.c

clean:
	rm -rf $(DXTOBJS) dxt
