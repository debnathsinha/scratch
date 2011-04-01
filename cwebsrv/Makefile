TARGETS = server client

OBJS = server.o client.o

all: server.c client.c
	gcc -o server server.c
	gcc -o client client.c

# %.o: %.c
# 	gcc -o $@ $<

clean:
	rm -rf *.o