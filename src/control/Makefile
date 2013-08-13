include ../../Rules.make

CXXFLAGS += -I../../include

OBJS=ProcessControl.o StaticContext.o DynamicContext.o

control.o:	$(OBJS)
		$(LD) -r -o $@ $(OBJS)

ProcessControl.o:

StaticContext.o:

DynamicContext.o:

clean:
	$(RM) $(RMFLAGS) $(OBJS)
	$(RM) $(RMFLAGS) control.o
