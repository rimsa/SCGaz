include ../../../Rules.make

CXXFLAGS += -I../../../include

OBJS=Queue.o Table.o

sheet.o:	$(OBJS)
		$(LD) -r -o $@ $(OBJS)

Queue.o:

Table.o:

clean:
	$(RM) $(RMFLAGS) $(OBJS)
	$(RM) $(RMFLAGS) sheet.o
