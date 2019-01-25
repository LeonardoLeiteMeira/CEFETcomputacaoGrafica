#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "escreve.h"
#include "desenha.h"

GLuint GameOver;

void texturaTextos(){
  GameOver = SOIL_load_OGL_texture(
      "../img/menu/perdeu.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
    );
    
    if (GameOver == 0) {
      printf("Erro do SOIL104: '%s'\n", SOIL_last_result());
    }
}

void DesenhaTexto(void *font, char *string) {
  while(*string){
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*string++);
  }
}

void escreveGameOver(void){
  glBindTexture(GL_TEXTURE_2D, GameOver);
  desenhaComTextura(65,95,55,85,1,0,1,0,1);

  glRasterPos2f(76,50);
  glColor3f(1,1,0);
  DesenhaTexto(GLUT_BITMAP_TIMES_ROMAN_10,"Pontos:");
}
void escrevePontos(int recorde, int local){
  char pontos[5];
  sprintf(pontos,"%i",recorde);

  glColor3f(1,1,0);
  if(local){
    glColor3f(1,0,0);
    glRasterPos2f(5,86); 
  }
  else{
    glColor3f(1,1,0.5);
    glRasterPos2f(85,50); 
  }

  DesenhaTexto(GLUT_BITMAP_TIMES_ROMAN_10,pontos);
}