# Variáveis do projeto
CC = gcc
CFLAGS = -Wall -Iinclude
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INCLUDE_DIR = include
TARGET = $(BIN_DIR)/matop

# Variáveis para compilação de debug
CFLAGS_DEBUG = -Wall -g -Iinclude

# Lista de fontes e objetos
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Regras principais
all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

debug: $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS_DEBUG) -o $(BIN_DIR)/matop_debug $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Regras de limpeza
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Regra para limpar e recompilar
rebuild: clean all

# Regras auxiliares
.PHONY: all clean rebuild debug

# Executar com Valgrind
valgrind: debug
	valgrind --leak-check=full --show-leak-kinds=all ./$(BIN_DIR)/matop_debug

# Executar com GDB
gdb: debug
	gdb ./$(BIN_DIR)/matop_debug
