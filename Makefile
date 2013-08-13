include Rules.make

all: $(OUTPUT)

$(OUTPUT):
		$(MAKE) -C src $(OUTPUT)
		$(CP) $(CPFLAGS) src/$(OUTPUT) bin/$(OUTPUT)

install:	bin/$(OUTPUT)
		install bin/$(OUTPUT) /usr/local/bin/$(OUTPUT)

uninstall:	/usr/local/bin/$(OUTPUT)
		$(RM) $(RMFLAGS) /usr/local/bin/$(OUTPUT)

clean:
		$(MAKE) -C src clean
		$(RM) $(RMFLAGS) bin/$(OUTPUT)
