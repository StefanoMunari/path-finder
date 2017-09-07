################################################################################
## NodeJS bindings for path-finder library written in C++
################################################################################

all: compile

compile:
	CXXFLAGS="-std=c++17 -pthread -fexceptions" node-gyp rebuild

.PHONY: clean
clean:
	node-gyp clean

.PHONY: help
help:
	@echo "Usage: make [commands]\n"\
	"Commands:\n" \
	"\t {compile, clean, help}\n" \
	"\t compile \t generates NodeJS bindings using node-gyp \n"\
	"\t clean \t\t remove any generated build file \n"