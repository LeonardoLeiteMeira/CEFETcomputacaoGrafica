#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "menus.h"
#include "desenha.h"

GLuint dino;
GLuint fundoMenu;
GLuint escreveMenu;
GLuint jogar;
GLuint jogarSelecionado;
GLuint info;
GLuint infoSelecionado;
GLuint sair;
GLuint sairSelecionado;
GLuint voltar;
GLuint voltarSelecionado;
GLuint continuar;
GLuint continuarSelecionado;
GLuint box1;
GLuint box2;
GLuint ajuda;
GLuint telaConfirmarSaida;
GLuint telaConfirmarReset;
GLuint texturaCreditos;

void texturaMenu(){
  dino = SOIL_load_OGL_texture(
      "../img/menu/principal/dino.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
    );
    if (dino == 0) {
      printf("Erro do SOIL-dino-menu: '%s'\n", SOIL_last_result());
    }

    fundoMenu = SOIL_load_OGL_texture(
      "../img/menu/principal/fundo.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
    );
    if (fundoMenu == 0) {
      printf("Erro do SOIL-fundo-menu: '%s'\n", SOIL_last_result());
    }

    escreveMenu = SOIL_load_OGL_texture(
      "../img/menu/menu.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
    );    
    if (escreveMenu == 0) {
      printf("Erro do SOIL-menu: '%s'\n", SOIL_last_result());
    }

    jogar = SOIL_load_OGL_texture(
      "../img/menu/principal/jogar.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
    );
    if (jogar == 0) {
      printf("Erro do SOIL-jogar: '%s'\n", SOIL_last_result());
    }

    jogarSelecionado = SOIL_load_OGL_texture(
      "../img/menu/principal/jogarSelecionado.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
    );
    if (jogarSelecionado == 0) {
      printf("Erro do SOIL-jogarS: '%s'\n", SOIL_last_result());
    }

    info = SOIL_load_OGL_texture(
      "../img/menu/principal/info.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
    );
    if (info == 0) {
      printf("Erro do SOIL-info: '%s'\n", SOIL_last_result());
    }

    infoSelecionado = SOIL_load_OGL_texture(
      "../img/menu/principal/infoSelecionado.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
    );
    if (infoSelecionado == 0) {
      printf("Erro do SOIL-infoS: '%s'\n", SOIL_last_result());
    }

    sair = SOIL_load_OGL_texture(
      "../img/menu/principal/sair.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
    );
    if (sair == 0) {
      printf("Erro do SOIL-infoS: '%s'\n", SOIL_last_result());
    }

    sairSelecionado = SOIL_load_OGL_texture(
      "../img/menu/principal/sairSelecionado.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
    );
    if (sairSelecionado == 0) {
      printf("Erro do SOIL-infoS: '%s'\n", SOIL_last_result());
    }

    voltar = SOIL_load_OGL_texture(
      "../img/menu/pausa/voltar.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
    );
    if (voltar == 0) {
      printf("Erro do SOIL-voltar: '%s'\n", SOIL_last_result());
    }

    voltarSelecionado = SOIL_load_OGL_texture(
      "../img/menu/pausa/voltarSelecionado.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
    );  
    if (voltarSelecionado == 0) {
      printf("Erro do SOIL-voltarS: '%s'\n", SOIL_last_result());
    }

    continuar = SOIL_load_OGL_texture(
      "../img/menu/pausa/continuar.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
    );
    if (continuar == 0) {
      printf("Erro do SOIL-continuar: '%s'\n", SOIL_last_result());
    }

    continuarSelecionado = SOIL_load_OGL_texture(
      "../img/menu/pausa/continuarSelecionado.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
    );  
    if (continuarSelecionado == 0) {
      printf("Erro do SOIL-continuarS: '%s'\n", SOIL_last_result());
    }

    box1 = SOIL_load_OGL_texture(
      "../img/menu/menuAjuda/box.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
    );  
    if (box1 == 0) {
      printf("Erro do SOIL-box: '%s'\n", SOIL_last_result());
    }
    box2 = SOIL_load_OGL_texture(
      "../img/menu/principal/boxCreditos.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
    );  
    if (box2 == 0) {
      printf("Erro do SOIL-box: '%s'\n", SOIL_last_result());
    }

    ajuda = SOIL_load_OGL_texture(
      "../img/menu/menuAjuda/menuInfo.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
    );  
    if (ajuda == 0) {
      printf("Erro do SOIL-ajuda: '%s'\n", SOIL_last_result());
    }

    telaConfirmarSaida = SOIL_load_OGL_texture(
      "../img/menu/confirmar/telaConfirmarSaida.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
    );  
    if (telaConfirmarSaida == 0) {
      printf("Erro do SOIL-ajuda: '%s'\n", SOIL_last_result());
    }

    telaConfirmarReset = SOIL_load_OGL_texture(
      "../img/menu/confirmar/telaConfirmarReset.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
    );  
    if (telaConfirmarReset == 0) {
      printf("Erro do SOIL-ajuda: '%s'\n", SOIL_last_result());
    }

    texturaCreditos = SOIL_load_OGL_texture(
      "../img/menu/principal/texturaCreditos.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
    );  
    if (texturaCreditos == 0) {
      printf("Erro do SOIL-ajuda: '%s'\n", SOIL_last_result());
    }
}
void desenhaJogar(int opcao){
  if(opcao==1)
    glBindTexture(GL_TEXTURE_2D, jogarSelecionado);
  else
    glBindTexture(GL_TEXTURE_2D, jogar);

  desenhaEmCima();
}
void desenhaInfo(int opcao){
  if(opcao==2)
    glBindTexture(GL_TEXTURE_2D, infoSelecionado);
  else
    glBindTexture(GL_TEXTURE_2D, info);

  desenhaNoMeio();
}
void desenhaSair(int opcao){
  if(opcao==3)
    glBindTexture(GL_TEXTURE_2D, sairSelecionado);
  else
    glBindTexture(GL_TEXTURE_2D, sair);

  desenhaEmBaixo();
}

void desenhaVoltar(int opcao){
  if(opcao==2)
    glBindTexture(GL_TEXTURE_2D, voltarSelecionado);
  else
    glBindTexture(GL_TEXTURE_2D, voltar);

  desenhaNoMeio();
}
void desenhaContinuar(int opcao){
  if(opcao==1)
    glBindTexture(GL_TEXTURE_2D, continuarSelecionado);
  else
    glBindTexture(GL_TEXTURE_2D, continuar);

  desenhaEmCima();
}
void desenhaReiniciar(int opcao){
  if(opcao==2)
    glBindTexture(GL_TEXTURE_2D, voltarSelecionado);
  else
    glBindTexture(GL_TEXTURE_2D, voltar);

  desenhaNoMeio();
}
void desenhaCaixa(int y1, int y2){
  desenhaComTextura(65,85,y1,y2,3,0,1,0,1);
}

void desenhaMenu(int opcao){
	glBindTexture(GL_TEXTURE_2D, fundoMenu);
	desenhaComTextura(0,160,0,90,-1,0,1,0,1);
  glBindTexture(GL_TEXTURE_2D, dino);
  desenhaComTextura(0,90,0,80,-0,0,1,0,1);

	glBindTexture(GL_TEXTURE_2D, escreveMenu);
	desenhaComTextura(65,85,77,87,1,0,1,0,1);

  desenhaJogar(opcao);
  desenhaInfo(opcao);
  desenhaSair(opcao);

  glBindTexture(GL_TEXTURE_2D, box2);
  desenhaComTextura(127,155,3,38,4,0,1,0,1);

  glBindTexture(GL_TEXTURE_2D, texturaCreditos);
  desenhaComTextura(130,150,5,35,5,0,1,0,1);
}
void menuPausa(int opcao){
  desenhaContinuar(opcao);
  desenhaReiniciar(opcao);
  desenhaSair(opcao);
}
void menuInfo(){
  glBindTexture(GL_TEXTURE_2D, box1);
  desenhaComTextura(30,130,15,75,4,0,1,0,1);
  glBindTexture(GL_TEXTURE_2D, ajuda);
  desenhaComTextura(40,120,26,66,5,0,1,0,1);

  glBindTexture(GL_TEXTURE_2D, sairSelecionado);
  desenhaComTextura(65,85,1,21,5,0,1,0,1);
}
void menuFinal(int opcao){
  desenhaReiniciar(opcao);
  desenhaSair(opcao);
}
void desenhaNoMeio(){
  desenhaCaixa(25,45);
}
void desenhaEmBaixo(){
  desenhaCaixa(1,21);
}
void desenhaEmCima(){
  desenhaCaixa(49,69);
}
void menuSair(){
  glBindTexture(GL_TEXTURE_2D, box1);
  desenhaComTextura(40,120,25,70,4,0,1,0,1);

  glBindTexture(GL_TEXTURE_2D, telaConfirmarSaida);
  desenhaComTextura(50,110,32,62,5,0,1,0,1); 
}
void menuReset(){
  glBindTexture(GL_TEXTURE_2D, box1);
  desenhaComTextura(40,120,25,70,4,0,1,0,1);

  glBindTexture(GL_TEXTURE_2D, telaConfirmarReset);
  desenhaComTextura(50,110,32,62,5,0,1,0,1); 
}