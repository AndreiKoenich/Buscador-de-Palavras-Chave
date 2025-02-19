# ESTRUTURAS DE DADOS

# BUSCADOR DE PALAVRAS-CHAVE

# Autor: Andrei Pochmann Koenich

# Makefile

# Variáveis de flags de compilação e de diretórios
FLAGS := -g -fsanitize=address -Wall -o

ABP := 		ABP/Sources/main.c \
			ABP/Sources/arvoreABP.c \
			ABP/Sources/listas.c \
			ABP/Sources/gerais.c

AVL := 		AVL/Sources/main.c \
			AVL/Sources/arvoreAVL.c \
			AVL/Sources/listas.c \
			AVL/Sources/gerais.c

# Comando para linkar os arquivos compilados e gerar o executável
link: 
	gcc $(FLAGS) buscadorABP $(ABP)
	gcc $(FLAGS) buscadorAVL $(AVL)

# Comando padrão do Makefile
.DEFAULT_GOAL := link