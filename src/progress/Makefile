include ../../Rules.make

CXXFLAGS += -I../../include

OBJS=ProgressHandler.o

progress.o: $(OBJS)
	$(LD) -r -o $@ $(OBJS)

ProgressHandler.o:

clean:
	rm -rf $(OBJS)
	rm -rf progress.o
