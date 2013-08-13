include ../../Rules.make

CXXFLAGS += -I../../include

OBJS=SyntheticContext.o LowerContext.o EqualContext.o HigherContext.o \
     DiscretizatedContext.o sheet/sheet.o

synthetic.o:	$(OBJS)
		$(LD) -r -o $@ $(OBJS)

SyntheticContext.o:

LowerContext.o:

EqualContext.o:

HigherContext.o:

DiscretizatedContext.o:

sheet/sheet.o:
	$(MAKE) -C sheet sheet.o

clean:
	$(MAKE) -C sheet clean
	$(RM) $(RMFLAGS) $(OBJS)
	$(RM) $(RMFLAGS) synthetic.o
