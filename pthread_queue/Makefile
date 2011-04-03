TARGET = workcrew
#TARGET = queue_driver
OBJS = queue.o control.o workcrew.o

all: ${OBJS}
	gcc -g -o ${TARGET} ${OBJS} -lpthread

$.o: %.c
	gcc -g -o $@ -c $<

clean:
	rm -rf *.o