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
OBJ := $(patsubst %.c,$(BUILDDIR)/%.o,$(SRC))
DEP := $(patsubst %.o,%.deps,$(OBJ))

TESTSRC := $(shell find $(SRCDIR)/ $(TESTSDIR)/ -type f -name '*.c')
TESTSRC := $(filter-out $(SRCDIR)/main.c, $(TESTSRC))
TESTOBJ := $(patsubst %.c,$(BUILDDIR)/%.o,$(TESTSRC))
TESTDEP := $(patsubst %.c,%.deps,$(TESTSRC))

all: $(PROG)

-include $(DEP)

%.deps: %.c
	$(CC) -MM $< >$@

build/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CCDYNAMICFLAGS) -c -MMD $(patsubst $(BUILDDIR)/%.o,%.c,$@) -o $@

clean:
	rm -rf $(BINDIR) $(BUILDDIR)

$(PROG): $(OBJ)
	mkdir -p $(BINDIR)
	$(CC) -o $(BINDIR)/$@ $^ $(LDFLAGS)

test: $(TESTOBJ)
	mkdir -p $(BINDIR)
	$(CC) -o $(BINDIR)/$@ $^ $(LDFLAGS)
