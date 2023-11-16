# Author : LABORDE Quentin, CHAPELAIN Nathan
# Date : 15-11-2023

CC = gcc
CFLAGS = -std=c17 -pedantic -Wall -Wfatal-errors -g -g3
LDLIBS = -lm -lMLV
INCLUDES = -Iinclude -Iinclude/tools -Iinclude/graphic
SRCS = $(wildcard src/*.c) $(wildcard src/graphic/*.c) $(wildcard src/tools/*.c)
OBJS = $(SRCS:src/%.c=obj/%.o)
EXEC = gemcraft

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(INCLUDES) $^ -o $@ $(LDLIBS)

obj/%.o: src/%.c
	@mkdir -p obj
	@mkdir -p obj/graphic
	@mkdir -p obj/tools
	$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@

run: $(EXEC)
	./$(EXEC)

clean:
	rm -fr obj

distclean: clean
	rm -f $(EXEC)
