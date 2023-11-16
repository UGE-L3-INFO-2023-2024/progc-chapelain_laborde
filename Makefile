# Author : LABORDE Quentin, CHAPELAIN Nathan
# Date : 2023-11-16

CC = gcc
CFLAGS = -std=c17 -pedantic -Wall -Wfatal-errors -g -g3 -MMD
LDLIBS = -lm -lMLV

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

SRCS = $(shell find $(SRC_DIR) -depth -name "*.c")
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
INCLUDES = $(foreach file,$(shell find $(INC_DIR) -type d),-I$(file))

EXEC = gemcraft

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(INCLUDES) $^ -o $@ $(LDLIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@

run: $(EXEC)
	./$(EXEC)

clean:
	rm -fr obj

distclean: clean
	rm -f $(EXEC)
