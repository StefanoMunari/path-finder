CXX=g++
CFLAGS=-std=c++17 -Wall -Werror -pthread $(CDBG) $(CVGD)
SRCDIR=$(PATH_FINDER_ROOT)/src$(MODE)
TIMESDIR=$(PATH_FINDER_ROOT)/times
OBJDIR=$(PATH_FINDER_ROOT)/obj
BINDIR=$(PATH_FINDER_ROOT)/bin

LIBDIR=/usr/include
LIB=-ljsoncpp
INCLUDE=/usr/include/boost

SRC=$(wildcard $(SRCDIR)/*.cc) $(wildcard $(SRCDIR)/*/*.cc) $(wildcard $(SRCDIR)/*/*/*.cc) $(wildcard $(SRCDIR)/*/*/*/*.cc)
OBJ=$(SRC:%.cc=%.o)
BIN=find_path

ifeq ($(OPT),times)
	# use the correct main (times)
	AUX := $(filter-out $(SRCDIR)/main.cc, $(SRC)) $(wildcard $(TIMESDIR)/*.cc)
	SRC := $(AUX)
	# link filesystem experimental lib
	LIB := $(LIB) -lstdc++fs
endif

all: compile

%.o: %.cc
	@echo "\n=>Compiling: $@"
	$(CXX) $(CFLAGS) $(CVG) -I $(INCLUDE) -c $< -o $(OBJDIR)/$(lastword $(subst /, ,$@))

$(BINDIR)/$(BIN): $(OBJ)
	@echo "\n=>Linking: $(OBJDIR)/*.o"
	$(CXX) $(CFLAGS) $(OBJDIR)/*.o -o $@ -L$(LIBDIR) $(LIB)


compile: $(BINDIR)/$(BIN)
	@echo "$(SRC)"

.PHONY: run
run: compile
	@echo "=>Running: $(BINDIR)/$(BIN)"
	$(BINDIR)/$(BIN) $(ARGS)

.PHONY: profile
profile: compile
	@echo "=>Profiled: $(BINDIR)/$(BIN)"
	valgrind $(VGDOPTS) $(BINDIR)/$(BIN) $(ARGS) 2>&1 | tee -a make_run.log && rm make_run.log

.PHONY: times
times: compile
	@echo "=>Running Times: $(BINDIR)/$(BIN)"
	$(BINDIR)/$(BIN)

.PHONY: help
help:
	@echo "Usage: make [commands] [options]\n"\
	"Options:\n"\
	"\t ARGS=<arg_list>\t\t\t  Runs with the argument list for main process. e.g. ARGS=\"Source Destination\"\n"\
	"\t CDBG=-DDEBUG=1\t\t\t\t  Compiles with the debugging flag activated.\n"\
	"\t CVGD=-g\t\t\t\t\t  Compiles with the valgrind flag activated.\n"\
	"\t VGDOPTS=<valgrind_options>\t  Execs with the defined options for valgrind (only in profile mode).\n"\
	"\t MODE=<subdir_path>\t\t  Compiles only specificied subfolder. e.g. MODE=\"/core\"\n"\
	"\n"\
	"Commands:\n" \
	"\t {compile, run, profile, clean, help}\n"


.PHONY: clean
clean:
	@echo ""\
	$$(find $(PATH_FINDER_ROOT) -type f -name "*.o" -delete) >/dev/null
	@echo "=>Cleaned object files"