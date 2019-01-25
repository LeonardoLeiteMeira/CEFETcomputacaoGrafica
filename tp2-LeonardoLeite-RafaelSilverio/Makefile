CC=gcc
OPCOES_COMPILADOR=-I. -I/SOILUpdate -lglut -lGLU -lGLEW -lGL -lm -lSOIL  -lSDL -lSDL_mixer
TODOS_ARQUIVOS_PONTOH = glm.h glmint.h
TODOS_ARQUIVOS_OBJ = glm.o  glm_util.o  glmimg.o desenha.o skybox.o elementosCenario.o

%.o: ../%.c $(TODOS_ARQUIVOS_PONTOH)
	$(CC) -o $@ -c $< $(OPCOES_COMPILADOR)

run: $(TODOS_ARQUIVOS_OBJ) main.o 
	gcc -o main $^ $(OPCOES_COMPILADOR)
	./main

clean:
	rm *.o main

