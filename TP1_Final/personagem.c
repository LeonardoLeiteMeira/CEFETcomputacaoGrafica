#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "desenha.h"
#include "personagem.h"
#include "controle.h"

//TEXTURAS
GLuint texturaPersonagem1;
GLuint texturaPersonagem2;
GLuint texturaPersonagem3;
GLuint texturaPersonagem4;
GLuint texturaPersonagem5;
GLuint texturaPersonagem6;
GLuint texturaPersonagem7;
GLuint texturaPersonagem8;
GLuint texturaPersonagemPulo;
GLuint texturaPersonagemMorte;

//GLuint texturaPersonagem[10];O CODIGO NÃO FOI ATUALIZADO PARA USAR ESSE VETOR 

//boolean
int fake = 0, verdade = 1;

void TexturaPersonagem(){

	texturaPersonagem1 = SOIL_load_OGL_texture(
      "../img/dino/dino1.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
    );
    
    if (texturaPersonagem1 == fake) {
      printf("Erro do SOIL1: '%s'\n", SOIL_last_result());
    }

    texturaPersonagem2 = SOIL_load_OGL_texture(
      "../img/dino/dino1.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
    );
    
    if (texturaPersonagem2 == fake) {
      printf("Erro do SOIL1: '%s'\n", SOIL_last_result());
    }

    texturaPersonagem3 = SOIL_load_OGL_texture(
      "../img/dino/dino3.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
    );

    if (texturaPersonagem3 == fake) {
      printf("Erro do SOIL2: '%s'\n", SOIL_last_result());
    }

    texturaPersonagem4 = SOIL_load_OGL_texture(
      "../img/dino/dino4.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
    );

    if (texturaPersonagem4 == fake) {
      printf("Erro do SOIL3: '%s'\n", SOIL_last_result());
    }

    texturaPersonagem5 = SOIL_load_OGL_texture(
      "../img/dino/dino5.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
    );

    if (texturaPersonagem5 == fake) {
      printf("Erro do SOIL90: '%s'\n", SOIL_last_result());
    }
    texturaPersonagem6 = SOIL_load_OGL_texture(
      "../img/dino/dino6.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
    );

    if (texturaPersonagem6 == fake) {
      printf("Erro do SOIL91: '%s'\n", SOIL_last_result());
    }

    texturaPersonagem7 = SOIL_load_OGL_texture(
      "../img/dino/dino7.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
    );

    if (texturaPersonagem7 == fake) {
      printf("Erro do SOIL91: '%s'\n", SOIL_last_result());
    }

    texturaPersonagem8 = SOIL_load_OGL_texture(
      "../img/dino/dino8.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
    );

    if (texturaPersonagem8 == fake) {
      printf("Erro do SOIL91: '%s'\n", SOIL_last_result());
    }

    texturaPersonagemPulo = SOIL_load_OGL_texture(
      "../img/dino/pulo.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
    );

    if (texturaPersonagemPulo == fake) {
      printf("Erro do SOIL-pulo: '%s'\n", SOIL_last_result());
    }

    texturaPersonagemMorte = SOIL_load_OGL_texture(
      "../img/dino/morreu.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
    );

    if (texturaPersonagemMorte == fake) {
      printf("Erro do SOIL morte: '%s'\n", SOIL_last_result());
    }
}

void desenhaPersonagem(int x1, int x2, int y1,int y2,int z, int controleTexturaPersonagem, double alturaAtual){
 
  if(controleTexturaPersonagem == -2)
    glBindTexture(GL_TEXTURE_2D, texturaPersonagemMorte);

  if(controleTexturaPersonagem == -1)
    glBindTexture(GL_TEXTURE_2D, texturaPersonagemPulo);

  if(controleTexturaPersonagem == 0)
    glBindTexture(GL_TEXTURE_2D, texturaPersonagem1);

  if(controleTexturaPersonagem == 1)
    glBindTexture(GL_TEXTURE_2D, texturaPersonagem1);
      
  if(controleTexturaPersonagem == 2)
    glBindTexture(GL_TEXTURE_2D, texturaPersonagem2);

  if(controleTexturaPersonagem == 3)
     glBindTexture(GL_TEXTURE_2D, texturaPersonagem2);

  if(controleTexturaPersonagem == 4)
    glBindTexture(GL_TEXTURE_2D, texturaPersonagem3);

  if(controleTexturaPersonagem == 5)
    glBindTexture(GL_TEXTURE_2D, texturaPersonagem3);

  if(controleTexturaPersonagem == 6)
    glBindTexture(GL_TEXTURE_2D, texturaPersonagem4);

  if(controleTexturaPersonagem == 7)
    glBindTexture(GL_TEXTURE_2D, texturaPersonagem4);

  if(controleTexturaPersonagem == 8)
    glBindTexture(GL_TEXTURE_2D, texturaPersonagem5);

  if(controleTexturaPersonagem == 9)
    glBindTexture(GL_TEXTURE_2D, texturaPersonagem5);
      
  if(controleTexturaPersonagem == 10)
    glBindTexture(GL_TEXTURE_2D, texturaPersonagem6);

  if(controleTexturaPersonagem == 11)
     glBindTexture(GL_TEXTURE_2D, texturaPersonagem6);

  if(controleTexturaPersonagem == 12)
    glBindTexture(GL_TEXTURE_2D, texturaPersonagem7);

  if(controleTexturaPersonagem == 13)
    glBindTexture(GL_TEXTURE_2D, texturaPersonagem7);

  if(controleTexturaPersonagem == 14)
    glBindTexture(GL_TEXTURE_2D, texturaPersonagem8);

  if(controleTexturaPersonagem == 15)
    glBindTexture(GL_TEXTURE_2D, texturaPersonagem8);

  desenhaComTextura(2,22,18+alturaAtual,33+alturaAtual,1, 0,1,0,1);
}

void atualizaCorrida(int *controleTexturaPersonagem, int *mudaTextura){

  switch(*controleTexturaPersonagem){
    case -2:
      variaTextura(&(*controleTexturaPersonagem),&(*mudaTextura),0);
      break;

    case -1:
      variaTextura(&(*controleTexturaPersonagem),&(*mudaTextura),0);
      break;

    case 0:
      variaTextura(&(*controleTexturaPersonagem),&(*mudaTextura),1);
      break;

    case 1:
      variaTextura(&(*controleTexturaPersonagem),&(*mudaTextura),2);
      break;

    case 2:
      variaTextura(&(*controleTexturaPersonagem),&(*mudaTextura),3);
      break;

    case 3:
      variaTextura(&(*controleTexturaPersonagem),&(*mudaTextura),4);
      break;

    case 4:
      variaTextura(&(*controleTexturaPersonagem),&(*mudaTextura),5);
      break;

    case 5:
      variaTextura(&(*controleTexturaPersonagem),&(*mudaTextura),6);
      break;

    case 6:
      variaTextura(&(*controleTexturaPersonagem),&(*mudaTextura),7);
      break;

    case 7:
      variaTextura(&(*controleTexturaPersonagem),&(*mudaTextura),8);
      break;

    case 8:
      variaTextura(&(*controleTexturaPersonagem),&(*mudaTextura),9);
      break;

    case 9:
      variaTextura(&(*controleTexturaPersonagem),&(*mudaTextura),10);
      break;

    case 10:
      variaTextura(&(*controleTexturaPersonagem),&(*mudaTextura),11);
      break;

    case 11:
      variaTextura(&(*controleTexturaPersonagem),&(*mudaTextura),12);
      break;

    case 12:
      variaTextura(&(*controleTexturaPersonagem),&(*mudaTextura),13);
      break;

    case 13:
      variaTextura(&(*controleTexturaPersonagem),&(*mudaTextura),14);
      break;

    case 14:
      variaTextura(&(*controleTexturaPersonagem),&(*mudaTextura),15);
      break;

    case 15:
      variaTextura(&(*controleTexturaPersonagem),&(*mudaTextura),0);
      break; 

  default:
      break;
    }
}
