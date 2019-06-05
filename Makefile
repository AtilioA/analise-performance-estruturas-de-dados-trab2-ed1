OBJ      := obj
SRC      := src
INC      := include
CFLAGS   := -g -Wall -O3 # Sinto que esse O3 pode dar divergência no compactador
EXE 	 := compactador


# Cria objetos de todos os arquivos de código-fonte para então linká-los no programa final
main: $(OBJ)/Modulo1.o $(OBJ)/trab1.o
	gcc $(OBJ)/*.o -o $(EXE) $(CFLAGS)

$(OBJ)/Modulo1.o: $(SRC)/Modulo1.c $(INC)/Modulo1.h
	gcc -c $(CFLAGS) "$(SRC)/Modulo1.c" -o "$(OBJ)/Modulo1.o"

$(OBJ)/trab1.o: trab1.c
	gcc -c $(CFLAGS) trab1.c -o "$(OBJ)/trab1.o"

# Roda o programa
run:
	./$(EXE)

# Compila e roda o programa
voado: main run

# Roda o programa com valgrind e flags úteis
val:
	valgrind --leak-check=full -v --track-origins=yes \
	--show-leak-kinds=all ./$(EXE)

# Roda o programa com valgrind sem flags
valzin:
	valgrind ./$(EXE)

# Roda o programa com valgrind e salva resultados num .txt
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
