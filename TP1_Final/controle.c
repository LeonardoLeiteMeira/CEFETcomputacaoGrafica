#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "controle.h"

#define LARGURA_DO_MUNDO 160
#define ALTURA_DO_MUNDO 90

void redimensiona(int width, int height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, LARGURA_DO_MUNDO, 0, ALTURA_DO_MUNDO, -5, 5);

    float razaoAspectoJanela = ((float)width)/height;
    float razaoAspectoMundo = ((float) LARGURA_DO_MUNDO)/ ALTURA_DO_MUNDO;
    // se a janela está menos larga do que o mundo (16:9)...
    if (razaoAspectoJanela < razaoAspectoMundo) {
        // vamos colocar barras verticais (acima e abaixo)
        float hViewport = width / razaoAspectoMundo;
        float yViewport = (height - hViewport)/2;
        glViewport(0, yViewport, width, hViewport);
    }
    // se a janela está mais larga (achatada) do que o mundo (16:9)...
    else if (razaoAspectoJanela > razaoAspectoMundo) {
        // vamos colocar barras horizontais (esquerda e direita)
        float wViewport = ((float)height) * razaoAspectoMundo;
        float xViewport = (width - wViewport)/2;
        glViewport(xViewport, 0, wViewport, height);
    } else {
        glViewport(0, 0, width, height);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void velocidadeDoJogo(double *velocidade){
  if(*velocidade<=5.5){
    *velocidade = *velocidade * 1.0025;
  }
}

int atualizaMovimento(double *movObstaculo,double *velocidade, int *obtstaculoAleatorio){
  srand(time(0));
  *movObstaculo = *movObstaculo + *velocidade;
  if(*movObstaculo>=LARGURA_DO_MUNDO || *obtstaculoAleatorio == 0){
    *movObstaculo = 0;//faz o obstaculo voltar ao inicio da tela
    *obtstaculoAleatorio = rand()%10 + 1;
  }
  return *obtstaculoAleatorio;
}
double atualizaMovimentoCenario(double velCenario){
  velCenario = velCenario + 1.5;
  if(velCenario>=LARGURA_DO_MUNDO)
    velCenario = 0;
  return velCenario;
}
void variaTextura(int *controleTexturaPersonagem, int *mudaTextura, int mudaPara){
  *controleTexturaPersonagem = mudaPara;
  *mudaTextura = 0;
}
void controlaVida(int *vidas){
  *vidas--;
}

void atulaizaVelocidadeAmbiente(double velAmbient[]){
  velAmbient[4] +=0.5;//velocidade do cenario no fundo

  for(int i=0;i<4;i++){
    velAmbient[i]+=1;//incrementa a velocidade com que os elementos do fundo se movimentam
  }
  if(velAmbient[0]>=183)//posição dos elementos que movimentam no fundo
    velAmbient[0]=0;
  if(velAmbient[1]>=308)
    velAmbient[1]=0;
  if(velAmbient[2]>=218)
    velAmbient[2]=0;
  if(velAmbient[3]>=278)
    velAmbient[3]=0;
  if(velAmbient[4]>=160)
    velAmbient[4]=0;
}