include ../../Rules.make

CXXFLAGS += -I../../include

OBJS=RandomHandler.o

random.o:	$(OBJS)
		$(LD) -r -o $@ $(OBJS)

RandomHandler.o:

clean:
	rm -rf $(OBJS)
	rm -rf random.o
