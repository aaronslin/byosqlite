# Tutorial: https://makefiletutorial.com/
# Remember that commands must start with a tab, not spaces!

# := declares a variable when it is defined, while = declares a variable when it is called
SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:src/%.c=build/objects/%.o)
OUTPUT := build/main

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

print:
	@echo "Sources: $(SRCS)"
	@echo "Objects: $(OBJS)"
	@echo "Objects: $(OUTPUT)"

clean:
	rm -rf $(OUTPUT) $(OBJS)
