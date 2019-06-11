OBJ      := obj
SRC      := src
INC      := include
CFLAGS   := -g -w -O3 # Sinto que esse O3 pode dar divergência no indexador
EXE 	 := indexador
PROJETO  := trab2-AtilioDadalto-TiagoSantos

# Cria objetos de todos os arquivos de código-fonte para então linká-los no programa final
main: $(OBJ)/ListaEncadeada.o $(OBJ)/Indexador.o $(OBJ)/Indexador.o $(OBJ)/$(PROJETO).o
	gcc $(OBJ)/*.o -o $(EXE) $(CFLAGS)

$(OBJ)/ListaEncadeada.o: $(SRC)/ListaEncadeada.c $(INC)/ListaEncadeada.h
	gcc -c $(CFLAGS) "$(SRC)/ListaEncadeada.c" -o "$(OBJ)/ListaEncadeada.o"

$(OBJ)/Indexador.o: $(SRC)/Indexador.c $(INC)/Indexador.h
	gcc -c $(CFLAGS) "$(SRC)/Indexador.c" -o "$(OBJ)/Indexador.o"

$(OBJ)/ArvoreBinaria.o: $(SRC)/ArvoreBinaria.c $(INC)/ArvoreBinaria.h
	gcc -c $(CFLAGS) "$(SRC)/ArvoreBinaria.c" -o "$(OBJ)/ArvoreBinaria.o"

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
