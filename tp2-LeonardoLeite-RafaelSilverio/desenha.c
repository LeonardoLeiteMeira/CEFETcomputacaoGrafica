#include <GL/glew.h>
#include <GL/freeglut.h>
#include <string.h>
#include <stdio.h>
#include <SOIL/SOIL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL.h>
#include <SDL/SDL.h>

#include "glm.h"
#include "glmint.h"
#include "desenha.h"
#include "skybox.h"
#include "elementosCenario.h"

GLMmodel* pmodel = NULL;
GLMmodel* ilhaM = NULL;
GLMmodel* ilhaP = NULL;
GLMmodel* arvore2 = NULL;
GLMmodel* testeObj = NULL;
GLMmodel* elise = NULL;

void zeppelin(){

    if (!pmodel) 
    {
	pmodel = glmReadOBJ("obj/zeppelin3/untitled.obj");
	printf("new zeppelin\n");
	
	if (!pmodel) 
		exit(0);
	
	glmUnitize(pmodel);
	glmFacetNormals(pmodel);
	glmVertexNormals(pmodel, 90, 1);
    }

    glmDraw(pmodel, GLM_SMOOTH | GLM_COLOR | GLM_TEXTURE );
}

void ilhaMoinho(){

    if (!ilhaM) {
		ilhaM = glmReadOBJ("obj/ilhaMoinho/low-poly-mill.obj");
	
		if (!ilhaM)
			exit(0);
	
		glmUnitize(ilhaM);
		glmFacetNormals(ilhaM);
		glmVertexNormals(ilhaM, 90, 1);
    }

    glmDraw(ilhaM, GLM_SMOOTH | GLM_COLOR);

}

void ilhaPredio(){

    if (!ilhaP) {
		ilhaP = glmReadOBJ("obj/ilhaPredio/low_poly_bilding.obj");
	
		if (!ilhaP)
			exit(0);
	
		glmUnitize(ilhaP);
		glmFacetNormals(ilhaP);
		glmVertexNormals(ilhaP, 90, 1);
    }

    glmDraw(ilhaP, GLM_SMOOTH | GLM_COLOR);
}

void arvoreOBJ(){

    if (!arvore2) {
		arvore2 = glmReadOBJ("obj/arvore/Lowpoly_tree_sample.obj");
	
		if (!arvore2)
			exit(0);
	
		glmUnitize(arvore2);
		glmFacetNormals(arvore2);
		glmVertexNormals(arvore2, 90, 1);
    }


    glmDraw(arvore2, GLM_SMOOTH | GLM_COLOR);
}

void eliseOBJ(){

    if (!elise) {
		elise = glmReadOBJ("obj/elise/untitled.obj");
	
		if (!elise)
			exit(0);
	
		glmUnitize(elise);
		glmFacetNormals(elise);
		glmVertexNormals(elise, 90, 1);
    }


    glmDraw(elise, GLM_SMOOTH | GLM_COLOR);
}

void desenhaZeppelin(double X, double Y, double Z, double rotacaoElise, double roda){

	//Propriedades do material
	float ambienteZeppelin[] = {1.0, 1.0, 1.0, 1.0};
	float difusaZeppelin[] = {1.0, 1.0, 1.0, 1.0};
	float especularZeppelin[] = {1.0, 1.0, 1.0, 1.0};
	float brilhosidadeZeppelin[] = {100};

	// Definindo as propriedades do material
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambienteZeppelin);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, difusaZeppelin);
	glMaterialfv(GL_FRONT, GL_SPECULAR, especularZeppelin);
	glMaterialfv(GL_FRONT, GL_SHININESS, brilhosidadeZeppelin);


	glPushMatrix();
		glTranslated(X, Y, Z);
		glRotated(roda,0,1,0);

		glPushMatrix();
			glRotated(-65,0,1,0);
	        glScaled(10,10,10);
	        zeppelin();
	    glPopMatrix();

	    desenhaElise(X,Y,Z,3,rotacaoElise, 1.5, -2.2, -4.8);
	    desenhaElise(X,Y,Z,3,rotacaoElise, -1.5, -2.2, -4.8);
	    desenhaElise(X,Y,Z,3,rotacaoElise, 1.5, -2.9, -1.4);
	    desenhaElise(X,Y,Z,3,rotacaoElise, -1.5, -2.9, -1.4);

	    glPushMatrix();
	    	glColor3f(0.25,0.25,0.25);
	    	glTranslated(0,-3.8,7);
	    	glScaled(0.3,0.3,0.3);
	    	glutSolidTeapot(1);
	    glPopMatrix();
	glPopMatrix();
}

void desenhaIlhaMoinho(int x, int z, int tamanho){

	//Propriedades do material
	float ambienteMoinho[] = {1.0, 1.0, 1.0, 1.0};
	float difusaMoinho[] = {1.0, 1.0, 1.0, 1.0};
	float especularMoinho[] = {1.0, 1.0, 1.0, 1.0};
	float brilhosidadeMoinho[] = {100};

	// Definindo as propriedades do material
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambienteMoinho);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, difusaMoinho);
	glMaterialfv(GL_FRONT, GL_SPECULAR, especularMoinho);
	glMaterialfv(GL_FRONT, GL_SHININESS, brilhosidadeMoinho);

	glPushMatrix();
		glColor3f(1,1,1);
		glTranslated(x,200,z);		
		glScaled(tamanho,tamanho,tamanho);
		ilhaMoinho();
	glPopMatrix();
}

void desenhaIlhaPredio(int x, int z, int tamanho){

	//Propriedades do material
	float ambienteIlha[] = {1.0, 1.0, 1.0, 1.0};
	float difusaIlha[] = {1.0, 1.0, 1.0, 1.0};
	float especularIlha[] = {1.0, 1.0, 1.0, 1.0};
	float brilhosidadeIlha[] = {100};

	// Definindo as propriedades do material
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambienteIlha);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, difusaIlha);
	glMaterialfv(GL_FRONT, GL_SPECULAR, especularIlha);
	glMaterialfv(GL_FRONT, GL_SHININESS, brilhosidadeIlha);

	glPushMatrix();
		glColor3f(1,1,1);
		glTranslated(x,40,z);
		glScaled(tamanho,tamanho,tamanho);
		ilhaPredio();		
	glPopMatrix();
}

void desenhaArvoreOBJ(int x, int z, int tamanho){

	//Propriedades do material
	float ambienteArvore[] = {0, 0.5, 0, 1.0};
	float difusaArvore[] = {0, 0.5, 0, 1.0};
	float especularArvore[] = { 1.0, 1.0, 1,0, 1.0 };
	float brilhosidadeArvore[] = {100};

	// Definindo as propriedades do material
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambienteArvore);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, difusaArvore);
	glMaterialfv(GL_FRONT, GL_SPECULAR, especularArvore);
	glMaterialfv(GL_FRONT, GL_SHININESS, brilhosidadeArvore);

	glPushMatrix();
		glColor3f(1,1,1);
		glTranslated(x,20,z);
		glScaled(tamanho,tamanho,tamanho);	
		arvoreOBJ();
	glPopMatrix();
}

void desenhaElise(int x, int y, int z, int tamanho, int angulo, double posiX, double posiY, double posiZ){
	glPushMatrix();
		glColor3f(1,1,1);
		glTranslated(posiX, posiY, posiZ);
		glRotated(angulo,0,0,1);
		glRotated(-65,0,1,0);
		glScaled(tamanho,tamanho,tamanho);	
		eliseOBJ();
	glPopMatrix();
}