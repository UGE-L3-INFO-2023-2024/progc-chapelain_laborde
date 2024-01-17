# Author : LABORDE Quentin, CHAPELAIN Nathan
# Date : 2023-11-16

CC = gcc
CFLAGS = -std=c17 -pedantic -Wall -Wfatal-errors -g -g3 -MMD
LDLIBS = -lm -lMLV

SRC_DIR = src
OBJ_DIR = bin
INC_DIR = include
DOC_DIR = doc
RESOURCES_DIR = resources

SRCS = $(shell find $(SRC_DIR) -depth -name "*.c")
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
INCLUDES = $(foreach file,$(shell find $(INC_DIR) -type d),-I$(file))
DEPENDENCIES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.d, $(SRCS))

EXEC = gemcraft

all: $(EXEC)

-include $(DEPENDENCIES)

$(EXEC): $(OBJS)
	$(CC) $(INCLUDES) $^ -o $@ $(LDLIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@

run: $(EXEC)
	./$(EXEC)

rapport:
	pandoc --pdf-engine=xelatex $(DOC_DIR)/$@.md -H $(RESOURCES_DIR)/metadata.tex -o $(DOC_DIR)/$@.pdf -V colorlinks=true

doxygen:
	doxygen Doxyfile

clean:
	rm -fr $(OBJ_DIR)/*

distclean: clean
	rm -f $(EXEC)
	rm -fr $(DOC_DIR)/html
