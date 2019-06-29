OBJ      := obj
SRC      := src
INC      := include
CFLAGS   := -g -w -O3
EXE 	 := indexador
PROJETO  := trab2-AtilioDadalto-TiagoSantos

# Cria objetos de todos os arquivos de código-fonte para então linká-los no programa final
main: $(OBJ)/lista_encadeada.o $(OBJ)/arvore_binaria.o $(OBJ)/arvore_AVL.o $(OBJ)/indexador.o $(OBJ)/arquivos.o $(OBJ)/$(PROJETO).o
	gcc $(OBJ)/*.o -o $(EXE) $(CFLAGS)

$(OBJ)/indexador.o: $(SRC)/indexador.c $(INC)/indexador.h
	gcc -c $(CFLAGS) "$(SRC)/indexador.c" -o "$(OBJ)/indexador.o"

$(OBJ)/lista_encadeada.o: $(SRC)/lista_encadeada.c $(INC)/lista_encadeada.h
	gcc -c $(CFLAGS) "$(SRC)/lista_encadeada.c" -o "$(OBJ)/lista_encadeada.o"

$(OBJ)/arvore_binaria.o: $(SRC)/arvore_binaria.c $(INC)/arvore_binaria.h
	gcc -c $(CFLAGS) "$(SRC)/arvore_binaria.c" -o "$(OBJ)/arvore_binaria.o"

$(OBJ)/arvore_AVL.o: $(SRC)/arvore_AVL.c $(INC)/arvore_AVL.h
	gcc -c $(CFLAGS) "$(SRC)/arvore_AVL.c" -o "$(OBJ)/arvore_AVL.o"

# $(OBJ)/tabela_hash.o: $(SRC)/tabela_hash.c $(INC)/tabela_hash.h
# 	gcc -c $(CFLAGS) "$(SRC)/tabela_hash.c" -o "$(OBJ)/tabela_hash.o"

$(OBJ)/arquivos.o: $(SRC)/arquivos.c $(INC)/arquivos.h
	gcc -c $(CFLAGS) "$(SRC)/arquivos.c" -o "$(OBJ)/arquivos.o"


$(OBJ)/$(PROJETO).o: $(PROJETO).c
	gcc -c $(CFLAGS) $(PROJETO).c -o "$(OBJ)/$(PROJETO).o"

# Executa o programa
run:
	./$(EXE)

# Compila e executa o programa
voado: main run

# Apenas Linux
time:
	time ./$(EXE)

# Executa o programa com valgrind e flags úteis
val:
	valgrind --leak-check=full -v --track-origins=yes \
	--show-leak-kinds=all ./$(EXE)

# Executa o programa com valgrind sem flags
valzin:
	valgrind ./$(EXE)

# Executa o programa com valgrind e salva resultados num .txt
valtxt:
	valgrind --leak-check=full -v --show-leak-kinds=all --track-origins=yes --verbose --log-file="valgrind-out.txt" ./$(EXE)

# Limpa objetos e o executável do programa (para Windows)
cleanW:
	del /F/Q/S "$(OBJ)\*.o"
	del /F/Q/S $(EXE).exe

# Limpa objetos e o executável do programa (para Linux)
clean:
	-rm $(OBJ)/*.o
	-rm $(EXE)
