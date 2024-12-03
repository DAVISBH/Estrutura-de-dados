CC = gcc
CFLAGS = -Wall -Iinclude
OBJDIR = obj
BINDIR = bin
SRCDIR = src
INCDIR = include

OBJS = $(OBJDIR)/main.o $(OBJDIR)/heap.o

all: $(BINDIR)/pa2.out

$(BINDIR)/pa2.out: $(OBJS)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/main.o: $(SRCDIR)/main.c $(INCDIR)/heap.h
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/heap.o: $(SRCDIR)/heap.c $(INCDIR)/heap.h
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(BINDIR)
