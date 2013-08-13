include ../../Rules.make

CXXFLAGS += -I../../include

OBJS=DensityException.o InputException.o InitException.o \
     ValidationException.o MemoryException.o

exceptions.o:	$(OBJS)
		$(LD) -r -o $@ $(OBJS)

DensityException.o:

InputException.o:

InitException.o:

ValidationException.o:

clean:
	$(RM) $(RMFLAGS) $(OBJS)
	$(RM) $(RMFLAGS) exceptions.o
