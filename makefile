CXX = g++
CFLAGS = -std=c++14 -Wall -Werror
COMPILER = -c

SRCDIR  = src
OBJDIR = obj
BINDIR = bin
LIBDIR= /usr/include
LIB=python2.7
INCLUDE= /usr/include/boost

SRC= main.cc
OBJ = $(SRC:.cc=.o)
BIN = find_path

SRC_EXT = .cc
OBJ_EXT = .o

all: $(SRCDIR)/$(SRC) $(BINDIR)/$(BIN)

$(BINDIR)/$(BIN): $(OBJDIR)/$(OBJ) 
	$(CXX) -I $(INCLUDE) $(OBJDIR)/$(OBJ) $(CFLAGS) -o $@ -L $(LIBDIR) -l$(LIB0) -L$(LIBDIR) -l$(LIB)

$(OBJDIR)/$(OBJ):
	$(CXX) $(COMPILER) -I $(INCLUDE) $(CFLAGS) $(SRCDIR)/$(SRC) -o $(OBJDIR)/$(OBJ) -L$(LIBDIR) -l$(LIB)

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

