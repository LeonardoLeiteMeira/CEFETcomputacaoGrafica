#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "desenha.h"

//BOOLEAN
int verdadeiro = 1, falso = 0;

//TEXTURAS
GLuint texturaFundo[2];
GLuint texturaObstaculo[4];
GLuint texturaMostro;
GLuint ambiente[4];

void desenhaQuadrado(int x1, int x2, int y1,int y2,int z){
  glBegin(GL_TRIANGLE_FAN);
    glVertex3f(x1, y1, z);
    glVertex3f(x2, y1, z);
    glVertex3f(x2, y2, z);
    glVertex3f(x1, y2, z);
  glEnd();
}
void desenhaComTextura(int x1, int x2, int y1,int y2,int z,double xt1, double xt2, double yt1,double yt2){
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glColor3f(1,1,1);
  glEnable(GL_TEXTURE_2D);
  glBegin(GL_TRIANGLE_FAN);
    glTexCoord2f(xt1, yt1);glVertex3f(x1, y1, z);
    glTexCoord2f(xt2, yt1);glVertex3f(x2, y1, z);
    glTexCoord2f(xt2, yt2);glVertex3f(x2, y2, z);
    glTexCoord2f(xt1, yt2);glVertex3f(x1, y2, z);
  glEnd();
  glDisable(GL_TEXTURE_2D);
}


void TexturaCenario(){
    glClearColor(1, 1, 1, 1);
    glEnable(GL_BLEND );
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    texturaFundo[0] = SOIL_load_OGL_texture(
      "../img/fundos/fundo.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
    );

    if (texturaFundo[0] == falso) {
      printf("Erro do SOIL4: '%s'\n", SOIL_last_result());
    }

    texturaFundo[1] = SOIL_load_OGL_texture(
      "../img/fundos/piso.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
    );

    if (texturaFundo[1] == falso) {
      printf("Erro do SOIL5: '%s'\n", SOIL_last_result());
    }


    texturaObstaculo[0] = SOIL_load_OGL_texture(
      "../img/obstaculos/pedra.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
    );

    if (texturaObstaculo[0] == falso) {
      printf("Erro do SOIL-Pedra: '%s'\n", SOIL_last_result());
    }

    texturaObstaculo[1] = SOIL_load_OGL_texture(
      "../img/obstaculos/spike.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
    );

    if (texturaObstaculo[1] == falso) {
      printf("Erro do SOIL-Spike: '%s'\n", SOIL_last_result());
    }

    texturaObstaculo[2] = SOIL_load_OGL_texture(
      "../img/obstaculos/toco.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
    );

    if (texturaObstaculo[2] == falso) {
      printf("Erro do SOIL-Toco: '%s'\n", SOIL_last_result());
    }

    texturaObstaculo[3] = SOIL_load_OGL_texture(
      "../img/obstaculos/serra.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
    );

    if (texturaObstaculo[2] == falso) {
      printf("Erro do SOIL-serra: '%s'\n", SOIL_last_result());
    }

    texturaMostro = SOIL_load_OGL_texture(
      "../img/obstaculos/mostro.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
    );

    if (texturaMostro == falso) {
      printf("Erro do SOIL-Toco: '%s'\n", SOIL_last_result());
    }

    ambiente[0] = SOIL_load_OGL_texture(
      "../img/fundos/arbusto.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
    );

    if (ambiente[0] == falso) {
      printf("Erro do SOIL-arbusto: '%s'\n", SOIL_last_result());
    }
    ambiente[1] = SOIL_load_OGL_texture(
      "../img/fundos/arbusto2.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
    );

    if (ambiente[1] == falso) {
      printf("Erro do SOIL-arbusto2: '%s'\n", SOIL_last_result());
    }
    ambiente[2] = SOIL_load_OGL_texture(
      "../img/fundos/tree2.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
    );

    if (ambiente[2] == falso) {
      printf("Erro do SOIL-tree2: '%s'\n", SOIL_last_result());
    }
    ambiente[3] = SOIL_load_OGL_texture(
      "../img/fundos/tree3.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
    );

    if (ambiente[3] == falso) {
      printf("Erro do SOIL-tree3: '%s'\n", SOIL_last_result());
    }
}

void desenhaVidas(int vidas){
  glColor3f(1,1,1);
  if(vidas == 3)
    glColor3f(1,0,0);
  desenhaQuadrado(150,152,86,88,0);
  if(vidas == 2)
    glColor3f(1,0,0);
  desenhaQuadrado(153,155,86,88,0);
  if(vidas == 1)
    glColor3f(1,0,0);
  desenhaQuadrado(156,158,86,88,0);
}

void desenhaObstaculo(double posicaoObstaculo, int obtstaculoAleatorio, int *monstro){
  int Yinicial, Yfinal;

  if(obtstaculoAleatorio>7){
    Yinicial = 30;
    Yfinal = 40;
    switch(*monstro){
      case 1:
        *monstro = 2;
        glBindTexture(GL_TEXTURE_2D, texturaMostro);
        desenhaComTextura(150-posicaoObstaculo,165-posicaoObstaculo, Yinicial, Yfinal,0 , 0,0.25,0,1);
        break;

      case 2:
        *monstro = 3;
        glBindTexture(GL_TEXTURE_2D, texturaMostro);
        desenhaComTextura(150-posicaoObstaculo,165-posicaoObstaculo, Yinicial, Yfinal,0 , 0.25,0.5,0,1);
        break;

      case 3:
        *monstro = 4;
        glBindTexture(GL_TEXTURE_2D, texturaMostro);
        desenhaComTextura(150-posicaoObstaculo,165-posicaoObstaculo, Yinicial, Yfinal,0 , 0.5,0.75,0,1);
        break;

      case 4:
        *monstro = 1;
        glBindTexture(GL_TEXTURE_2D, texturaMostro);
        desenhaComTextura(150-posicaoObstaculo,165-posicaoObstaculo, Yinicial, Yfinal,0 , 0.75,1,0,1);
        break;

      default:
        break;
    }
    
  }

  if(obtstaculoAleatorio<=7){
    Yinicial = 20;
    Yfinal = 30;
    
    switch(obtstaculoAleatorio){
      case 0:
      case 1:
        glBindTexture(GL_TEXTURE_2D, texturaObstaculo[0]);//PEDRA
        break;

      case 2:
      case 3:
        glColor3f(1,0,0);
        glBindTexture(GL_TEXTURE_2D, texturaObstaculo[3]);//SERRA
        break;
      case 4:
      case 5:
        glColor3f(1,0,0);
        glBindTexture(GL_TEXTURE_2D, texturaObstaculo[1]);//SPIKE
        break;

      case 6:
      case 7:
        glBindTexture(GL_TEXTURE_2D, texturaObstaculo[2]);//TOCO
        break;

      default:
        break;
    }
    desenhaComTextura(150-posicaoObstaculo,160-posicaoObstaculo, Yinicial, Yfinal,0,0,1,0,1);
    glColor3f(0,0,0);
  }
}

void desenhaCenario(double velCenario, double velAmbiente[]){
  glBindTexture(GL_TEXTURE_2D, texturaFundo[0]);
  desenhaComTextura(0-velAmbiente[4],160-velAmbiente[4],0,100,-2, 0,1,0,1);
  desenhaComTextura(160-velAmbiente[4],320-velAmbiente[4],0,100,-2, 0,1,0,1);

  glBindTexture(GL_TEXTURE_2D, texturaFundo[1]);
  desenhaComTextura(0-velCenario,320-velCenario,0,20,-1 ,0,1,0,1);

  glBindTexture(GL_TEXTURE_2D, ambiente[0]);
  desenhaComTextura(175-velAmbiente[0],183-velAmbiente[0],20,25,-1 ,0,1,0,1);

  glBindTexture(GL_TEXTURE_2D, ambiente[1]);
  desenhaComTextura(300-velAmbiente[1],308-velAmbiente[1],20,25,-1 ,0,1,0,1);

  glBindTexture(GL_TEXTURE_2D, ambiente[2]);
  desenhaComTextura(210-velAmbiente[2],218-velAmbiente[2],20,35,-1 ,0,1,0,1);

  glBindTexture(GL_TEXTURE_2D, ambiente[3]);
  desenhaComTextura(270-velAmbiente[3],278-velAmbiente[3],20,35,-1 ,0,1,0,1);
}