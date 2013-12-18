APPNAME:= conqueror
PROG   := conqueror
CC     := gcc
INCL   :=
CFLAGS := -g -O2 -Wall -Wextra -Wwrite-strings -Wformat=2 -Wconversion -Wmissing-declarations -Wmissing-prototypes
LDFLAGS:=
CCDYNAMICFLAGS := ${CFLAGS} ${LDFLAGS} -fPIC
LDDYNAMICFLAGS := -shared

INSTALL=install -D

SRC := $(wildcard src/*.c src/*/*.c src/*/*/*.c)
OBJ := $(patsubst %.c,%.o,$(SRC))
DEP := $(patsubst %.c,%.deps,$(SRC))

APPDIR=$(DESTDIR)/etc/$(APPNAME)
INCLDIR=$(DESTDIR)/usr/include

all: $(PROG)

-include $(DEP)

%.deps: %.c
	$(CC) -MM $< >$@

%.o: %.c
	$(CC) $(CCDYNAMICFLAGS) -c -MMD $< -o $@

clean:
	find . -name '*.o' -delete -o -name '*.d' -delete -o -name '*.deps' -delete  -o -name "$(PROG)" -delete

$(PROG): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

