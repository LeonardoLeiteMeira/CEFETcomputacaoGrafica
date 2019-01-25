#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "desenha.h"
#include "escreve.h"
#include "personagem.h"
#include "controle.h"
#include "menus.h"
#include "som.h"

#define totalVidas 3;

//BOOLEAN
int truE = 1, falsE = 0;

//VELOCIDADE CENARIO
int velCenario = 0;
double velAmbiente[5] = {0,0,0,0,0};

//MOVIMENTO DO OBSTACULO
double movObstaculo = 0;
int obtstaculoAleatorio = 0;
int monstro = 1;

//VARIAVEIS PARA CONTROLAR O PULO
double pulo = 0, alturaAtual = 0;//pulo inicia o movimento,alturaAtual controla a altura
int sobeDesce=1;//1 ta indo pra cima, 0 ta indo pra baixo
double incremento, incrementoInicial = 3;
int alturaMax = 22;//altura max do salto

//VARIAVEIS QUE CONTROLAM O AGACHAMENTO 
double abaixar = 0;

//VELOCIDADE INICIAL DO JOGO
double velocidade, velocidadeInicial = 1.5;

//COLISÃO
int colide = 0;

//PAUSA COMEÇANDO COM FALSE
int pausa = 0;

//REINICIA GAME
int confirmarReset = 0;

//FINALIZA GAME
int confirmarSaida=0;

//VARIVEL QUE CONTROLA AS VIDAS
int vidas = totalVidas;
int fimDeJogo = 0;

//PONTUAÇÃO
int recorde = 0;
int pontuacaoFinal;

//CONTROLAR A MOVIMENTAÇÃO DO PERSONAGEM
int controleTexturaPersonagem = 0, mudaTextura=0;

//Tela de inicio
int menu = 1;
int opcaoMenu=1;
int menuAjuda=0;

void reinicia(){
  velocidade = velocidadeInicial;
  incremento = incrementoInicial;
  pulo = falsE;
  alturaAtual = 0;
  sobeDesce = truE;
  movObstaculo = 0;
  colide = falsE;
  controleTexturaPersonagem = 0;
  fimDeJogo=falsE;
}

void desenhaCena(){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);


    if(!menu){
      desenhaCenario(velCenario, velAmbiente);
      desenhaVidas(vidas);
      if(!fimDeJogo)
        escrevePontos(recorde,1);//escreve o recorde em cima

      desenhaObstaculo(movObstaculo,obtstaculoAleatorio, &monstro);
      desenhaPersonagem(2,14,20+alturaAtual,32+alturaAtual,1,controleTexturaPersonagem, alturaAtual);

      if(fimDeJogo){
        escreveGameOver();
        escrevePontos(recorde,0);//escreve o recorde embaixo
        menuFinal(opcaoMenu);
      }
      if(pausa && !colide)
        menuPausa(opcaoMenu);
      if(confirmarReset==1)
        menuReset();
    }else{
      desenhaMenu(opcaoMenu);
      if(menu && menuAjuda){
        menuInfo();
      }
    }
    if(confirmarSaida==1)
        menuSair();
      
  glColor3f(1,1,1);

    
  glutSwapBuffers();

  glDisable(GL_DEPTH_TEST);
}



void puloPersonagem(){
  //mecanica do pulo
  if(pulo){//quando manda pular o 'pulo' recebe 1 em entra no if
    if(sobeDesce){
      alturaAtual+=incremento;
      incremento=incremento*0.91;
      //Diminuia velocidade na subida
    }
    else{
      incremento=incremento*1.098;
      alturaAtual-=incremento;
      //aumenta a velocidade na descida
    }

    if(alturaAtual>=alturaMax && sobeDesce){//quando atinge a altura max ele desce
      sobeDesce = falsE;//1 para subida e 0 para descida
    }
    if(sobeDesce==0 && alturaAtual<=0){//quando o pulo termina as variaveis sao reiniciadas
      pulo = falsE;
      alturaAtual = 0;
      sobeDesce = truE;
      incremento = incrementoInicial;
    }
    controleTexturaPersonagem = -1;//ativa atextura de pulo
  }
}

void abaixaPersonagem(){
  //mecanica de abaixar
  if(abaixar){
    alturaAtual = -3;
    pulo = falsE;
    sobeDesce = falsE;
    incremento = incrementoInicial;
  }else{
    alturaAtual=0;
  }
}

int colidir(){
  if( ((160-movObstaculo)<20 && (170-movObstaculo)>8 && (20+alturaAtual)<25) && obtstaculoAleatorio <= 7
    || ((160-movObstaculo)<20 && (170-movObstaculo)>8 && (32+alturaAtual)>31) && obtstaculoAleatorio > 7 ){
    vidas--;
    if(vidas<=0){
     return 1;
    }
    else{
      sleep(1);
      reinicia();
    }
  }
  return 0;
}

void anima(){
  if(!menu){//o jogo so funciona quando nã esta na tela de menu

    if( !(colidir()) ){
      if(!pausa){//quando o jogo ta pausado as variaveis nao atualizam
        recorde++;
        velocidadeDoJogo(&velocidade);//função que controla a velocidade do jogo
        obtstaculoAleatorio = atualizaMovimento(&movObstaculo, &velocidade ,&obtstaculoAleatorio);
        atulaizaVelocidadeAmbiente(velAmbiente);
        velCenario = atualizaMovimentoCenario(velCenario);
        puloPersonagem();//função que controla o pulo     
        
        if(!pulo)//se o pulo não ta ativado o jogo atualiza a textura de corrida
          atualizaCorrida(&controleTexturaPersonagem, &mudaTextura);
      }
    }else{
      colide = truE;//parar o jogo quando tiver colisao
      controleTexturaPersonagem = -2;
      if(vidas == 0){
        fimDeJogo=truE;
        pausa = truE;
        alturaAtual = 0;
      }
    }
  }

  glutPostRedisplay();
  glutTimerFunc(33,anima,0);
}

void apertaTeclado(unsigned char key, int x, int y){
  switch(key){

    case 27://botao esc
      if(!menu){
        pausa = truE;
        if(confirmarReset==1){
          confirmarReset=0;
          pausa = falsE;
          glutPostRedisplay();
          break;
        }
        if(confirmarSaida==1){
          pausa = falsE;
          opcaoMenu = 1;
          confirmarSaida=0;
        }
        else 
          confirmarSaida = 1;
        opcaoMenu=3;
      }else{
        if(confirmarSaida==1)
          confirmarSaida = 0;
        else{
          confirmarSaida=1;
          opcaoMenu = 3;
        }
      }
      
      glutPostRedisplay();
      break;

    case 13://botao enter
      if(menuAjuda){
        menuAjuda=falsE;
        break;
      }
      switch(opcaoMenu){//quando aperto enter ele verifica em qual menu estou

        case 1:
          if(menu){
            menu=0;
            confirmarSaida = 0;
          }
          if(!menu && pausa){
            pausa=falsE;
            confirmarSaida=0;
          }
          glutPostRedisplay();
          break;

        case 2:
          if(menu){
            if(menuAjuda==1)
              menuAjuda=0;
            else if(menuAjuda==0)
              menuAjuda=1;
          }
          if(!menu && pausa){
            confirmarReset++;
            if(confirmarReset==2){
              confirmarReset = 0;
              pausa=falsE;
              reinicia();//reinicia o jogo,
              recorde = 0;//volta o recorde pra zero e
              vidas = totalVidas;//reinicia as vidas
              opcaoMenu=1;
            }

          }
          glutPostRedisplay();
          break;

        case 3:
          if(menu){
            confirmarSaida++;//com isso a função desenha chama a caixa de confirmação
            if(confirmarSaida==2)
              exit(0);
          }            
          if(!menu && pausa){
            confirmarSaida++;
            if(confirmarSaida==2){
              reinicia();
              recorde=0;
              vidas = totalVidas;
              menu=truE;
              confirmarSaida=0;
              opcaoMenu=1;
            }
          }
          glutPostRedisplay();
          break;

        default:
          break;
      }
      glutPostRedisplay();
      break;

    case 'W':
    case 'w':
      if(menu == truE || pausa == truE){
        if(opcaoMenu!=1 && confirmarSaida!=1 && confirmarReset!=1){
          opcaoMenu--;
        }
      }else{
        pulo = truE;
      }
      
      glutPostRedisplay();
      break;

    case 'p':
    case 'P':
      if(pausa==truE){
        pausa = falsE;
      }
      else if(pausa==falsE){
        pausa = truE;
        opcaoMenu=1;
      }
      glutPostRedisplay();
      break;

    case 'r':
    case 'R':
      if(!menu){
        confirmarReset=1;
        pausa = truE;
        opcaoMenu = 2;
      }
      glutPostRedisplay();
      break;

    case 'c':
    case 'C':
      confirmarReset = falsE;
      confirmarSaida = falsE;
      glutPostRedisplay();
      break;

    case 's':
    case 'S':
      if(menu==truE || pausa==truE){
        if(opcaoMenu!=3 && confirmarSaida!=1 && confirmarReset!=1){
          opcaoMenu++;
        }
      }else {
        abaixar = truE;
      }

      abaixaPersonagem();
      glutPostRedisplay();
      break;

    default:
      break;
  }
  //printf("\nCode: %02x\n", key);
}
void soltaTeclado(unsigned char key, int x, int y){
  switch(key){
    case 's':
    case 'S':
      if(pausa==falsE){
        abaixar = falsE;
        sobeDesce = truE;
        abaixaPersonagem();
      }
      glutPostRedisplay();
      break;
  }
}
int main(int argc, char **argv){
  glutInit(&argc, argv);

  glutInitContextVersion(1, 1);
  glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(1600, 900);
  glutInitWindowPosition(100, 100);

  glutCreateWindow("Dino Run");

  glutDisplayFunc(desenhaCena);

  glutReshapeFunc(redimensiona);
  glutKeyboardUpFunc(soltaTeclado);
  glutKeyboardFunc(apertaTeclado);

  TexturaCenario();
  TexturaPersonagem();
  texturaTextos();
  texturaMenu();

  tocar_musica("som.ogg",-1);

  glutTimerFunc(33,anima, 0);
  reinicia();//zera as variavei para o jogo começar

  glutMainLoop();

  return 0;
}
