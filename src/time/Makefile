include ../../Rules.make

CXXFLAGS += -I../../include

OBJS=TimeHandler.o

time.o: $(OBJS)
	$(LD) -r -o $@ $(OBJS)

TimeHandler.o:

clean:
	rm -rf $(OBJS)
	rm -rf time.o
