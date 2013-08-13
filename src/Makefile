include ../Rules.make

CXXFLAGS += -I../include

OBJS=control/control.o synthetic/synthetic.o exceptions/exceptions.o \
     progress/progress.o log/log.o random/random.o
SUBDIRS=control synthetic exceptions progress log random

OBJS += scgaz.o

$(OUTPUT):	$(OBJS)
		$(CXX) -o $@ $(OBJS) $(LDFLAGS)

control/control.o:
	$(MAKE) -C control control.o

synthetic/synthetic.o:
	$(MAKE) -C synthetic synthetic.o

exceptions/exceptions.o:
	$(MAKE) -C exceptions exceptions.o

progress/progress.o:
	$(MAKE) -C progress progress.o

log/log.o:
	$(MAKE) -C log log.o

random/random.o:
	$(MAKE) -C random random.o

scgaz.o:

clean:
	$(MAKE) -C control clean
	$(MAKE) -C synthetic clean
	$(MAKE) -C exceptions clean
	$(MAKE) -C progress clean
	$(MAKE) -C log clean
	$(MAKE) -C random clean
	$(RM) $(RMFLAGS) scgaz.o
	$(RM) $(RMFLAGS) $(OUTPUT)
