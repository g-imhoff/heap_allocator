CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic
EXEC = heap_allocator 
SRC = $(wildcard src/*.c)
OBJ = $(SRC:src/%.c=obj/%.o)
DEPS = $(wildcard src/*.h)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

obj/%.o: src/%.c $(DEPS)
	mkdir -p obj
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(EXEC)
	rm -rf obj

format:
	@for file in $(SRC) $(DEPS); do \
		clang-format -i $$file; \
	done \

.phony: clean format 
