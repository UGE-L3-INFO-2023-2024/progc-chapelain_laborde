# Author : LABORDE Quentin, CHAPELAIN Nathan
# Date : 14-11-2023

CC = gcc
CFLAGS = -std=c17 -pedantic -Wall -Wfatal-errors -g -g3
LDLIBS = -lm -lMLV
SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:src/%.c=obj/%.o)
EXEC = gemcraft

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) -Iinclude $^ -o $@ $(LDLIBS)

obj/%.o: src/%.c
	@mkdir -p obj
	$(CC) -Iinclude $(CFLAGS) -c $< -o $@

run: $(EXEC)
	./$(EXEC)

clean:
	rm -fr obj

distclean: clean
	rm -f $(EXEC)
