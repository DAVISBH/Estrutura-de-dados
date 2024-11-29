# Variáveis do projeto
CC = gcc
CFLAGS_COMMON = -Wall -Iinclude
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Targets principais
.PHONY: all clean debug release

# Configuração padrão
TARGET = $(BIN_DIR)/tp1.out
CFLAGS = $(CFLAGS_COMMON) # Por padrão, sem -g

all: release

# Compilação para produção (normal)
release: CFLAGS += -O2
release: $(TARGET)

# Compilação com debug (suporte ao Valgrind)
debug: CFLAGS += -g
debug: $(TARGET)

# Regra para criar o executável
$(TARGET): $(OBJS)
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# Regra para criar arquivos objeto
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza dos arquivos gerados
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
