#include <GL/glew.h>
#include <GL/freeglut.h>
#include <string.h>
#include <stdio.h>
#include <SOIL/SOIL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL.h>
#include <SDL/SDL.h>
#include <time.h>

#include "glm.h"
#include "glmint.h"
#include "desenha.h"
#include "skybox.h"
#include "elementosCenario.h"

#define totalElementos 400

typedef struct quantElemento{
    int arvoreOBJ;
    int ilhaMoinho;
    int ilhaPredio;
    int arvore;
}QuantElemento;

typedef struct controleDesenhaElementos{
    int quantArvoreOBJ;
    int quantIlhaMoinho;
    int quantIlhaPredio;
    int quantArvore;
}ControleDesenhaElementos;

QuantElemento quantidades;
ControleDesenhaElementos controle;
int posicoes[2][totalElementos];//matriz com as posicoes x e z de cada elemento

void iniciaNumeroElementos(){
	srand(time(0));

	quantidades.arvoreOBJ = totalElementos/2;
	quantidades.ilhaMoinho = 1;
	quantidades.ilhaPredio = 1;
	quantidades.arvore = (totalElementos/2)-2;

	int i,j;

	for(i=0; i<2 ; i++){
		for(j=0; j<totalElementos; j++){
			if(j<2){
				posicoes[i][j]=(rand()%2000)-1000;
			}else{
				posicoes[i][j]=(rand()%5000)-2500;
			}
			
		}
	}
}

void desenhaCone(int x, int y, int z){
	glPushMatrix();
		glTranslated(x,y,z);
		glRotated(270,1,0,0);
		glutSolidCone(1,2,10,10);
	glPopMatrix();
}
void desenhaCubo(int x, int y, int z, double tam, double altura){
	glPushMatrix();
		glTranslated(x,y,z);
		glScaled(1,altura,1);
		glutSolidCube(tam);
	glPopMatrix();
}

void desenhaArvore(int x, int z, int altura, int tamanho){
	glPushMatrix();
		 // Propriedades do material
	    float corAmbiente[] = {0, 0.5, 0, 1.0};
	    float corDifusa[] = {0, 0.7, 0, 1.0};
	    float corEspecular[] = { 1.0, 1.0, 1,0, 1.0 };
	    float brilhosidade[] = {100};

	    // Definindo as propriedades do material
	    glMaterialfv(GL_FRONT, GL_AMBIENT, corAmbiente);
	    glMaterialfv(GL_FRONT, GL_DIFFUSE, corDifusa);
	    glMaterialfv(GL_FRONT, GL_SPECULAR, corEspecular);
	    glMaterialfv(GL_FRONT, GL_SHININESS, brilhosidade);

		glColor3f(0,0.6,0.1);
		glTranslated(x,0,z);
		glScaled(tamanho,tamanho,tamanho);
		desenhaCubo(0,0,0, 0.5,5);

		int i;
		for(i=0; i<altura; i++){
			desenhaCone(0,i+1,0);
		}
	glPopMatrix();
}

void desenhaElementosDoCenario(){

	controle.quantArvoreOBJ=0;
    controle.quantIlhaMoinho=0;
    controle.quantIlhaPredio=0;
    controle.quantArvore=0;

	int i;


	for(i=0; i<totalElementos; i++){

		if(controle.quantIlhaMoinho < quantidades.ilhaMoinho){
			desenhaIlhaMoinho(posicoes[0][i],posicoes[1][i],60);
			controle.quantIlhaMoinho++;
			continue;
		}	
		if(controle.quantIlhaPredio < quantidades.ilhaPredio){
			desenhaIlhaPredio(posicoes[0][i],posicoes[1][i],60);
			controle.quantIlhaPredio++;
			continue;
		}
		if(controle.quantArvoreOBJ < quantidades.arvoreOBJ){
			desenhaArvoreOBJ(posicoes[0][i], posicoes[1][i], 20);
			controle.quantArvoreOBJ++;
			continue;
		}
		if(controle.quantArvore < quantidades.arvore){
			desenhaArvore(posicoes[0][i],posicoes[1][i],6,6);
			controle.quantArvore++;
			continue;
		}
			
	}
}
