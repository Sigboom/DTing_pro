CC = gcc

# -g 增加调试信息
# -Wall 打开大部分警告信息
CFLAGS = -g -Wall

DXTOBJS = entrance.o foundation.o 

SQLOBJS = sqlite3.o sqltest.o

.PHONY: clean

dxt: $(DXTOBJS)
	$(CC) $(CFLAGS) -o dxt $(DXTOBJS)

sqltest: $(SQLOBJS)
	$(CC) $(CFLAGS) -o sqltest $(SQLOBJS)

entrance.o: entrance.c 
	$(CC) $(CFLAGS) -c -o entrance.o entrance.c

foundation.o: foundation.c foundation.h
	$(CC) $(CFLAGS) -c -o foundation.o foundation.c

dxt.o: dxt.c
	$(CC) $(CFLAGS) -c -o dxt.o dxt.c

clean:
	rm -f $(DXTOBJS) $(SQLOBJS) dxt sqltest
