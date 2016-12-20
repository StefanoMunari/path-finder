CXX = g++
CFLAGS = -std=c++14 -Wall -Werror
COMPILER = -c
LINKER = -o 
LIB = -I

SRCDIR  = src
OBJDIR = obj
BINDIR = bin
LIBDIR= /usr/include/boost

SRC= main.cc
OBJ = $(SRC:.cc=.o)
BIN = find_path

SRC_EXT = .cc
OBJ_EXT = .o

all: $(SRCDIR)/$(SRC) $(BINDIR)/$(BIN)

$(BINDIR)/$(BIN): $(OBJDIR)/$(OBJ) 
	$(CXX) $(LIB) $(LIBDIR) $(OBJDIR)/$(OBJ) $(CFLAGS) $(LINKER) $@

$(OBJDIR)/$(OBJ):
	$(CXX) $(COMPILER) $(LIB) $(LIBDIR) $(CFLAGS) $(SRCDIR)/$(SRC) $(LINKER) $(OBJDIR)/$(OBJ)

.PHONY: run
run:
	sh $(BINDIR)/$(BIN)

.PHONY: clean
clean:
	@if [ "$(ls -A ./$BINDIR/)" ]; \
		then \
		rm $(OBJDIR)/* ; \
	fi \
	$(info ${OBJDIR} cleaned)

.PHONY: remove
remove:
	@if [ "$(ls -A ./$BINDIR/)" ]; \
		then \
		rm $(BINDIR)/* ; \
	fi \
	$(info ${BINDIR} cleaned)

