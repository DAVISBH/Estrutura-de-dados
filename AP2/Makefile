# Nome do compilador
CC = gcc

# Diretórios
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INC_DIR = include

# Arquivos fonte
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
# Criação dos arquivos objeto a partir dos arquivos fonte
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Nome do executável
EXEC = $(BIN_DIR)/pa1.out

# Opções do compilador
CFLAGS = -I$(INC_DIR) -Wall -Wextra -lm -lrt

# Regra padrão para compilar o executável
all: $(EXEC)

# Regra para compilar arquivos .c em .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(EXEC): $(OBJ_FILES)
	$(CC) -o $@ $^

# Limpeza dos arquivos gerados
.PHONY: clean
clean:
	rm -f $(OBJ_DIR)/*.o $(EXEC)

# Regra para criar diretórios, se necessário
.PHONY: dirs
dirs:
	mkdir -p $(OBJ_DIR) $(BIN_DIR)
