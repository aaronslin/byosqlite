# Tutorial: https://makefiletutorial.com/
# Remember that commands must start with a tab, not spaces!

# := declares a variable when it is defined, while = declares a variable when it is called
SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:src/%.c=build/objects/%.o)
OUTPUT := build/main

define HEADER_FILE_CONTENT
#ifndef byosqlite_$*_h
#define byosqlite_$*_h

#include "common.h"

#endif
endef

define SOURCE_FILE_CONTENT
#include "$*.h"
endef

export HEADER_FILE_CONTENT
export SOURCE_FILE_CONTENT

# If you just run `make`, the first target automatically runs.
hello-world:
	echo "hello world"

run: $(OUTPUT)
	@echo "[$@] Running $(OUTPUT)"
	@./$(OUTPUT)

build: $(OBJS)
	@echo "[$@] Linking $(OUTPUT) to outputs: $^"
	@gcc -o $(OUTPUT) $^

build/objects/%.o: src/%.c
	@echo "[$@] Compiling source $^ to $@"
	@gcc -o $@ -c $^

src/%:
	@echo "[$@] Creating $@.c and $@.h"
	@test -f $@.h \
		&& echo "\t$@.h already exists" \
		|| echo "$$HEADER_FILE_CONTENT" > $@.h
	@test -f $@.c \
		&& echo "\t$@.c already exists" \
		|| echo "$$SOURCE_FILE_CONTENT" > $@.c

print:
	@echo "Sources: $(SRCS)"
	@echo "Objects: $(OBJS)"
	@echo "Objects: $(OUTPUT)"

clean:
	rm -rf $(OUTPUT) $(OBJS)
