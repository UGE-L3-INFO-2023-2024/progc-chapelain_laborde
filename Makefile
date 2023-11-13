CC=gcc
BIN_DIR=bin
INC_DIR=include
SRC_DIR=src
OBJ = $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%.o,$(wildcard $(SRC_DIR)/*.c))
CFLAGS=-Wall -std=c17 -pedantic -Wfatal-errors -g -g3
LDFLAGS=-lm -lMLV
EXEC=gemcraft
# $(info $(OBJ))

# $@ : the current target
# $^ : all current prerequisites
# $< : the first current prerequisite

all : $(EXEC)

# Dépandances
Utils.o : $(SRC_DIR)/Utils.c
Mana.o : $(SRC_DIR)/Mana.c
Path.o : $(SRC_DIR)/Path.c $(INC_DIR)/Utils.h
Map.o : $(SRC_DIR)/Map.c $(INC_DIR)/Mana.h $(INC_DIR)/Path.h $(INC_DIR)/Utils.h
Main.o : $(SRC_DIR)/Main.c $(INC_DIR)/Map.h


$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

$(BIN_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean :
	rm -f $(BIN_DIR)/*.o
	rm -f $(EXEC)

