BINDIR := bin
SRCDIR := src
TESTSDIR := tests
BUILDDIR := build

PROG   := conqueror
CC     := gcc
INCL   :=
CFLAGS := -g -O2 -Wall -Wextra -Wwrite-strings -Wformat=2 -Wconversion -Wmissing-declarations -Wmissing-prototypes
LDFLAGS:= -I./$(SRCDIR)
CCDYNAMICFLAGS := ${CFLAGS} ${LDFLAGS} -fPIC

SRC := $(shell find $(SRCDIR)/ -type f -name '*.c')
OBJ := $(patsubst %.c,%.o,$(SRC))
DEP := $(patsubst %.c,%.deps,$(SRC))

TESTSRC := $(shell find $(SRCDIR)/ $(TESTSDIR)/ -type f -name '*.c')
TESTSRC := $(filter-out $(SRCDIR)/main.c, $(TESTSRC))
TESTOBJ := $(patsubst %.c,%.o,$(TESTSRC))
TESTDEP := $(patsubst %.c,%.deps,$(TESTSRC))

all: $(PROG)

-include $(DEP)

%.deps: %.c
	$(CC) -MM $< >$@

%.o: %.c
	$(CC) $(CCDYNAMICFLAGS) -c -MMD $< -o $@

clean:
	find . -name '*.o' -delete -o -name '*.d' -delete -o -name '*.deps' -delete -o -name "$(PROG)" -delete -o -name "test" -delete

$(PROG): $(OBJ)
	mkdir -p $(BINDIR)
	$(CC) -o $(BINDIR)/$@ $^ $(LDFLAGS)

test: $(TESTOBJ)
	mkdir -p $(BINDIR)
	$(CC) -o $(BINDIR)/$@ $^ $(LDFLAGS)
