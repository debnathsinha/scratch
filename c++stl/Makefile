OBJS = mytemplate.o #mynewfunctor.o oddeven.o myfunctor.o opload.o myexception.o myvec.o

all: $(OBJS)

%.o: %.cpp
	g++ -o $@ $<
	./$@

clean:
	rm -rf $(OBJS)