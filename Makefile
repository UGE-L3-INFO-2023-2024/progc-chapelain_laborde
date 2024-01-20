# Author : LABORDE Quentin, CHAPELAIN Nathan
# Date : 16-11-2023

CC = gcc
CFLAGS = -std=c17 -pedantic -Wall -Wfatal-errors -MMD
LDLIBS = -lm -lMLV

# We define the directories we use
SRC_DIR = src
OBJ_DIR = bin
INC_DIR = include
DOC_DIR = doc
RESOURCES_DIR = resources

# We use find to get all the files in the SRC_DIR recursively
SRCS = $(shell find $(SRC_DIR) -depth -name "*.c")
# We replace the SRC_DIR by the OBJ_DIR and the .c by .o to get the object files
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
# We use a foreach to get all the directories in the INC_DIR and add -I before
# to get the -I flag for gcc on each directory
INCLUDES = $(foreach file,$(shell find $(INC_DIR) -type d),-I$(file))
# We replace the SRC_DIR by the OBJ_DIR and the .c by .d to get the dependencies
DEPENDENCIES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.d, $(SRCS))

EXEC = gemcraft

all: $(EXEC)

# We include the dependencies to make sure that the object files are updated
# when the header files are modified
-include $(DEPENDENCIES)

# We create the executable with all the object files
$(EXEC): $(OBJS)
	$(CC) $(INCLUDES) $^ -o $@ $(LDLIBS)

# We create the object files from the source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@

# Run the executable after compilation
run: $(EXEC)
	./$(EXEC)

# Generate the report
rapport: $(DOC_DIR)/rapport.md
	pandoc --pdf-engine=xelatex $< -H $(RESOURCES_DIR)/metadata.tex -o $(DOC_DIR)/$@.pdf

# Generate the documentation
doxygen:
	doxygen Doxyfile

# Clean the object files
clean:
	rm -fr $(OBJ_DIR)/*

# Clean the object files, executable and documentation
distclean: clean
	rm -f $(EXEC)
	rm -fr $(DOC_DIR)/html
