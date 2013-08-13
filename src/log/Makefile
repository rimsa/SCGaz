include ../../Rules.make

CXXFLAGS += -I../../include

OBJS=LogHandler.o

log.o: $(OBJS)
	$(LD) -r -o $@ $(OBJS)

LogHandler.o:

clean:
	rm -rf $(OBJS)
	rm -rf log.o
