CC         = gcc
CFLAGS     = -std=c11 -Wall -Wextra -fmax-errors=10
LFLAGS     = -L.
LIBS       = 

OBJPIPE    = pipe.o
OBJPAIR    = socketpair.o 
OBJUDGRAM  = udgramread.o udgramsend.o
OBJDGRAM   = dgramread.o dgramsend.o
OBJUSTREAM = ustreamaccept.o  ustreamwrite.o
OBJSTREAM  = streamaccept.o streamselect.o streamwrite.o

OBJFILES   =  $(OBJPIPE) $(OBJPAIR) \
$(OBJUDGRAM) $(OBJDGRAM) \
$(OBJUSTREAM) $(OBJSTREAM)

all: $(OBJFILES)

clean: 
	rm -f $(OBJFILES)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: pipe socketpair udgram dgram ustream stream

pipe: $(OBJPIPE)

socketpair: $(OBJPAIR)

udgram: $(OBJUDGRAM)

dgram: $(OBJDGRAM)

ustream: $(OBJUSTREAM)

stream: $(OBJSTREAM)

