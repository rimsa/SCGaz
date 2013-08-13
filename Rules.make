WIN32=no
DEBUG=no

ifeq ($(WIN32), yes)
  MAKE=mingw32-make
else
  MAKE=make
endif

CC=gcc
CFLAGS=-g -O2 -Wall -D_GNU_SOURCE

CXX=g++
CXXFLAGS=-g -O2 -Wall -D_GNU_SOURCE

LD=ld
LDFLAGS=

RM=rm
RMFLAGS=-rf

CP=cp
CPFLAGS=

ifeq ($(WIN32), yes)
  OUTPUT=scgaz.exe

  CPSRC=src\$(OUTPUT)
  CPDEST=.
else
  OUTPUT=scgaz

  CPSRC=src/$(OUTPUT)
  CPDEST=.
endif

ifeq ($(DEBUG), yes)
  CFLAGS += -DDEBUG
  CXXFLAGS += -DDEBUG
endif

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

.cc.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<
