TARGET = workcrew
#TARGET = queue_driver
OBJS = queue.o control.o

all: ${OBJS}
	gcc -g -o ${TARGET} ${TARGET}.c ${OBJS}

$.o: %.c
	gcc -g -o $@ -c $<

clean:
	rm -rf *.o