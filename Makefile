CC = gcc
CFLAGS = -Wall -std=c99
SRCDIR = src
INCDIR = include
OBJDIR = obj
BINDIR = bin

SOURCES = $(SRCDIR)/fila.c $(SRCDIR)/tarefas.c $(SRCDIR)/jobs.c $(SRCDIR)/processos.c $(SRCDIR)/orquestrador.c $(SRCDIR)/main.c
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
TARGET = $(BINDIR)/processflow

all: $(TARGET)

$(TARGET): $(OBJECTS)
	mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $^ -I$(INCDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCDIR)

clean:
	rm -rf $(OBJDIR) $(BINDIR)

run: $(TARGET)
	./$(BINDIR)/processflow

.PHONY: all clean run
