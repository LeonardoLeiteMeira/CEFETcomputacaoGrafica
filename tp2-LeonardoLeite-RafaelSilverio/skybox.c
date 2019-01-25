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

GLuint chao;
GLuint parede[4];
GLuint ceu;

void texturas(){

  glClearColor(1, 1, 1, 1);
    glEnable(GL_BLEND );
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //-----------------------
    chao = SOIL_load_OGL_texture(
      "img/chao.tga",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
    );

    if (chao == 0) {
      printf("Erro do SOIL chao: '%s'\n", SOIL_last_result());
    }

    //-----------------------

    parede[0] = SOIL_load_OGL_texture(
      "img/parede0.tga",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
    );

    if (parede[0] == 0) {
      printf("Erro do SOIL parede0: '%s'\n", SOIL_last_result());
    }

    //---------------------------

    parede[1] = SOIL_load_OGL_texture(
      "img/parede1.tga",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
    );

    if (parede[1] == 0) {
      printf("Erro do SOIL parede1: '%s'\n", SOIL_last_result());
    }

    //---------------------------

    parede[2] = SOIL_load_OGL_texture(
      "img/parede2.tga",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
    );

    if (parede[2] == 0) {
      printf("Erro do SOIL parede2: '%s'\n", SOIL_last_result());
    }

    //---------------------------

    parede[3] = SOIL_load_OGL_texture(
      "img/parede3.tga",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
    );

    if (parede[3] == 0) {
      printf("Erro do SOIL parede3: '%s'\n", SOIL_last_result());
    }

    //---------------------------

    ceu = SOIL_load_OGL_texture(
      "img/ceu.tga",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
    );

    if (ceu == 0) {
      printf("Erro do SOIL parede3: '%s'\n", SOIL_last_result());
    }

    //---------------------------
}

void desenhaComTextura(int x1, int x2, int y1, int y2, int z1, int z2){

  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glColor3f(1,1,1);
  glEnable(GL_TEXTURE_2D);
  glBegin(GL_TRIANGLE_FAN);
    glTexCoord2f(0, 0);glVertex3f(x1, y1, z1);
    glTexCoord2f(1, 0);glVertex3f(x2, y1, z1);
    glTexCoord2f(1, 1);glVertex3f(x2, y2, z2);
    glTexCoord2f(0, 1);glVertex3f(x1, y2, z2);
  glEnd();
  glDisable(GL_TEXTURE_2D);
}

void desenhaComTextura2(int x1, int x2, int y1, int y2, int z1, int z2){
//para desenhar os lados do skybox teve que criar outra função
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glColor3f(1,1,1);
  glEnable(GL_TEXTURE_2D);
  glBegin(GL_TRIANGLE_FAN);
    glTexCoord2f(0, 0);glVertex3f(x1, y1, z1);
    glTexCoord2f(1, 0);glVertex3f(x2, y1, z2);
    glTexCoord2f(1, 1);glVertex3f(x2, y2, z2);
    glTexCoord2f(0, 1);glVertex3f(x1, y2, z1);
  glEnd();
  glDisable(GL_TEXTURE_2D);
}

void desenhaCeuComTextura(int x1, int x2, int y1, int y2, int z1, int z2){
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glColor3f(1,1,1);
  glEnable(GL_TEXTURE_2D);
  glBegin(GL_TRIANGLE_FAN);
    glTexCoord2f(0, 0);glVertex3f(x1, y1, z1);
    glTexCoord2f(1, 0);glVertex3f(x2, y1, z1);
    glTexCoord2f(1, 1);glVertex3f(x2, y2, z2);
    glTexCoord2f(0, 1);glVertex3f(x1, y2, z2);
  glEnd();
  glDisable(GL_TEXTURE_2D);
}

void skybox(double x, double z){

  glBindTexture(GL_TEXTURE_2D, chao);
  desenhaComTextura(-4000, 4000, 0, 0, -4000, 4000);

  glBindTexture(GL_TEXTURE_2D, parede[0]);
  desenhaComTextura(-2000+x, 2000+x, 0, 1000, 2000+z, 2000+z);

  glBindTexture(GL_TEXTURE_2D, parede[2]);
  desenhaComTextura2(-2000+x, -2000+x, 0, 1000, -2000+z, 2000+z);

  glBindTexture(GL_TEXTURE_2D, parede[1]);
  desenhaComTextura(2000+x, -2000+x, 0, 1000, -2000+z, -2000+z);

  glBindTexture(GL_TEXTURE_2D, parede[3]);
  desenhaComTextura2(2000+x, 2000+x, 0, 1000, 2000+z, -2000+z);

  glBindTexture(GL_TEXTURE_2D, ceu);
  desenhaCeuComTextura(-2000+x, 2000+x, 1000, 1000, 2000+z, -2000+z);

}