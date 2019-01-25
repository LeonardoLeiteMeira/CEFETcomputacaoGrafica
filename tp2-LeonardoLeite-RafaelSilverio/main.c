#include <GL/glew.h>
#include <GL/freeglut.h>
#include <string.h>
#include <stdio.h>
#include <SOIL/SOIL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL.h>
#include <SDL/SDL.h>
#include <math.h>

#include "glm.h"
#include "glmint.h"
#include "desenha.h"
#include "skybox.h"
#include "elementosCenario.h"

#define TRUE 1
#define FALSE 0
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define PI 3.14159265359

void tocaMusica(char const nome[40], int loop);

typedef struct camera{
    int controle;//1-->por cima   2-->os 4 lados
    float distancia;//aqui altera a distancia da camera para o objeto
    float dentroZeppelin;
}Camera;

typedef struct movimento{
    double X;
    double Y;
    double Z;
    double incremento;
    double rotacao;
}Movimento;

typedef struct Mouse{
    double x,y;
}Mouse;

Movimento movimenta;
Movimento movimentoAnterior;
Camera cameras;
Mouse mouse;

GLuint modoNeblina[]= { GL_EXP, GL_EXP2, GL_LINEAR };
GLuint filtroNeblina= 1;
GLfloat CorNeblina[4]= {0.6, 0.6, 0.6, 1.0};

// Propriedades das fontes de luz
float ambiente0[] = { 1.0, 1.0, 1.0, 1.0 };
float difusa0[] = { 1.0, 1.0, 1.0, 1.0 };
float specular0[] = { 1.0, 1.0, 1.0, 1.0 };
float posicaoLuz0[] = { 0.0, 100.0, 0.0, 0.0 };
float luzAmbienteGlobal[] = { 0.2, 0.2, 0.2, 1.0 };

float ambiente1[] = { 0.8, 0.5, 0.0, 1.0 };
float difusa1[] = { 1.0, 0.5, 0.0, 1.0 };
float specular1[] = { 1.0, 0.5, 0.0, 1.0 };
float posicaoLuz1[] = { 0.0, 100.0, 0.0, 0.0 };

float xmundo=2000;
float zmundo=2000;
float alturaMundo=950;

int luzLigada = 1;
int escurecer = 1;
int neblinaLigada = 0;

GLdouble rotacaoElise = 0;


void inicializa() {
    glClearColor(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);
    texturas();

    movimenta.X=0;
    movimenta.Y=130;
    movimenta.Z=0;
    movimenta.incremento=7;
    movimenta.rotacao = 0;

    cameras.controle = 1;
    cameras.distancia = 30;//distancia da camera para o objeto
    cameras.dentroZeppelin=0;

    mouse.x=0;
    mouse.y=0;

    tocaMusica("Bohemian_Rhapsody_8_bit .ogg", -1);

    //configurando neblina
    glFogi(GL_FOG_MODE, modoNeblina[filtroNeblina]);
    glFogfv(GL_FOG_COLOR, CorNeblina);
    glFogf(GL_FOG_DENSITY, 0.0005);
    glHint(GL_FOG_HINT, GL_FASTEST);

    iniciaNumeroElementos();
}

void movimentoMouse(int x, int y) {
    mouse.x = -(-10 + ((double)x)/glutGet(GLUT_WINDOW_WIDTH)*20);
    mouse.y = -(-10 + ((double)y)/glutGet(GLUT_WINDOW_HEIGHT)*20);
    glutPostRedisplay();
}

void tocaMusica(char const nome[40], int loop)
{
        Mix_Chunk *som = NULL;
        int canal;
    int canal_audio=2;
        int taxa_audio = 22050;
        Uint16 formato_audio = AUDIO_S16SYS;
        int audio_buffers = 4096;
        if(Mix_OpenAudio(taxa_audio, formato_audio, canal_audio, audio_buffers) != 0) {
                printf("Não pode inicializar audio: %s\n", Mix_GetError());
        }
       som = Mix_LoadWAV(nome);
        if(som == NULL) {
                printf("Não pode inicializar audio: %s\n", Mix_GetError());
        }
       Mix_HaltChannel(-1);
       canal = Mix_PlayChannel( -1, som, loop);
        if(canal == -1) {
                printf("Não pode inicializar audio: %s\n", Mix_GetError());
        }
}

void parar_musica(){
    Mix_HaltChannel(-1);
}

void redimensiona(int w, int h) {
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float)(w)/h, 1, 10000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


int momentoAnterior;
float fps = 0;

void desenhaCena() 
{
    int momentoAtual = glutGet(GLUT_ELAPSED_TIME);
    int delta = momentoAtual - momentoAnterior;

    // apaga a tela para desenhar de novo
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Propriedades da fonte de luz LIGHT0
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);

    // Propriedades da fonte de luz LIGHT1
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambiente1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, difusa1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular1);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbienteGlobal);     // Luz ambiente global
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, TRUE);   // Local viewpoint sempre ativado
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz0);
     glLightfv(GL_LIGHT1, GL_POSITION, posicaoLuz1);

    // Ativa a fonte de luz
    if (luzLigada == 1) 
    {
        glEnable(GL_LIGHTING);
    } 
    else if(luzLigada == 0)
    {
        glDisable(GL_LIGHTING);
    }

    glEnable(GL_LIGHT0);

    //gluLookAt(olho,centro,up)

    // Ativa a neblina
    if (neblinaLigada == 1) 
    {
        glFogf(GL_FOG_START, (movimenta.Z - 10));
        glFogf(GL_FOG_END, (movimenta.Z - 20));
        glFogf(GL_FOG_DENSITY, 0.0010);
        glEnable(GL_FOG);
    } 
    else if(neblinaLigada == 0)
    {
        glDisable(GL_FOG);
    }

    glPushMatrix();
        
        switch(cameras.controle){
            case 1://camera padrao
                gluLookAt(movimenta.X-(cameras.distancia*sin(movimenta.rotacao*PI/180)), movimenta.Y+(cameras.distancia*0.3), (movimenta.Z-cameras.distancia*cos(movimenta.rotacao*PI/180)),     (movimenta.X), movimenta.Y + mouse.y, movimenta.Z,      0, 2, 0);
                desenhaZeppelin(movimenta.X, movimenta.Y, movimenta.Z, rotacaoElise, movimenta.rotacao);
                break;

            case 2: //camera para ver os lados
                gluLookAt(movimenta.X-(cameras.distancia*sin(movimenta.rotacao*PI/180)), movimenta.Y, (movimenta.Z-cameras.distancia*cos(movimenta.rotacao*PI/180)),     (movimenta.X), movimenta.Y + mouse.y, movimenta.Z,      0, 2, 0);
                desenhaZeppelin(movimentoAnterior.X, movimentoAnterior.Y, movimentoAnterior.Z, rotacaoElise, movimentoAnterior.rotacao);
                break;

            case 3: //camera por cima
                gluLookAt(movimenta.X-(cameras.distancia*sin(movimenta.rotacao*PI/180)), movimenta.Y+(cameras.distancia*3), (movimenta.Z-cameras.distancia*cos(movimenta.rotacao*PI/180)),     (movimenta.X), movimenta.Y + mouse.y, movimenta.Z,      0, 2, 0);
                desenhaZeppelin(movimenta.X, movimenta.Y, movimenta.Z, rotacaoElise, movimenta.rotacao);
                break;

            case 4://camera dentro da cabine
                gluLookAt(movimenta.X+(cameras.distancia*0.15*sin(movimenta.rotacao*PI/180)), movimenta.Y-3, movimenta.Z+cameras.distancia*0.15*cos(movimenta.rotacao*PI/180),     movimenta.X+(cameras.distancia*sin(movimenta.rotacao*PI/180))+cameras.dentroZeppelin, movimenta.Y + mouse.y-3, movimenta.Z+(cameras.distancia*cos(movimenta.rotacao*PI/180)),      0, 2, 0);
                desenhaZeppelin(movimenta.X, movimenta.Y, movimenta.Z, rotacaoElise, movimenta.rotacao);
                break;

            default:
                gluLookAt(movimenta.X-(cameras.distancia*sin(movimenta.rotacao*PI/180)), movimenta.Y+(cameras.distancia*0.3), (movimenta.Z-cameras.distancia*cos(movimenta.rotacao*PI/180)),     (movimenta.X), movimenta.Y + mouse.y, movimenta.Z,      0, 2, 0);
                desenhaZeppelin(movimenta.X, movimenta.Y, movimenta.Z, rotacaoElise, movimenta.rotacao);
                break;
        }

        glColor3f(1,1,1);
        skybox(movimenta.X,movimenta.Z);
        desenhaElementosDoCenario();
        glColor3f(1,1,1);
    glPopMatrix();

    fps = 1000.0f / MAX(delta, 1.0f);

    momentoAnterior = momentoAtual;

    glutSwapBuffers();
}

void teclado(unsigned char key, int x, int y) {
    switch (key) {
        case 27:
            exit(0);
            break;

        case 'w':
        case 'W':
            if(cameras.controle != 2){
                if(movimenta.Z+movimenta.incremento*cos(movimenta.rotacao*PI/180)<zmundo && movimenta.Z+movimenta.incremento*cos(movimenta.rotacao*PI/180)>-zmundo)
                    movimenta.Z+=movimenta.incremento*cos(movimenta.rotacao*PI/180);
                if(movimenta.X+movimenta.incremento*sin(movimenta.rotacao*PI/180)<xmundo && movimenta.X+movimenta.incremento*sin(movimenta.rotacao*PI/180)>-xmundo)
                    movimenta.X+=movimenta.incremento*sin(movimenta.rotacao*PI/180);
            }
            glutPostRedisplay();
            break;

        case 's':
        case 'S':
            if(cameras.controle != 2){
                if(movimenta.Z+movimenta.incremento*sin(movimenta.rotacao*PI/180)<zmundo && movimenta.Z+movimenta.incremento*sin(movimenta.rotacao*PI/180)>-zmundo)
                    movimenta.Z-=movimenta.incremento*cos(movimenta.rotacao*PI/180);
                if(movimenta.X+movimenta.incremento*cos(movimenta.rotacao*PI/180)<xmundo && movimenta.X+movimenta.incremento*cos(movimenta.rotacao*PI/180)>-xmundo)
                    movimenta.X-=movimenta.incremento*sin(movimenta.rotacao*PI/180);
            }
            glutPostRedisplay();
            break;

        case 'a':
        case 'A':
            movimenta.rotacao+=3;
            glutPostRedisplay();
            break; 

        case 'd':
        case 'D':
            movimenta.rotacao-=3;
            glutPostRedisplay();
            break;

        case 'z':
        case 'Z':
            if(movimenta.Y<alturaMundo)
            movimenta.Y+=movimenta.incremento;
            glutPostRedisplay();
            break;

        case 'x':
        case 'X':
            if(movimenta.Y>0)
                movimenta.Y-=movimenta.incremento;
            glutPostRedisplay();
            break;

        case '1':
            cameras.controle = 1;
            glutPostRedisplay();
            break;

        case '2':
            cameras.controle = 2;
            movimentoAnterior.X = movimenta.X;
            movimentoAnterior.Y = movimenta.Y;
            movimentoAnterior.Z = movimenta.Z;
            movimentoAnterior.incremento = movimenta.incremento;
            movimentoAnterior.rotacao = movimenta.rotacao;
            glutPostRedisplay();
            break;

        case '3':
            cameras.controle = 3;
            glutPostRedisplay();
            break;

        case '4':
            cameras.controle = 4;
            cameras.dentroZeppelin = 0;
            glutPostRedisplay();
            break;


        case 'l':
        case 'L':
            if(luzLigada == 1)
                luzLigada = 0;
            else if(luzLigada == 0)
                luzLigada = 1;
            
            glutPostRedisplay();
            break;

        case 'n':
        case 'N':
            if(neblinaLigada == 0)
                neblinaLigada = 1;
            else if(neblinaLigada == 1)
                    neblinaLigada = 0;
            
            glutPostRedisplay();
            break;

        default:
            break;


    }
}

void escurecerCenario()
{
    int contador;
    
    if(luzLigada == 1)
    {
        if(escurecer == 1)
        {
            if(ambiente0[0] <= 0.1)
                escurecer = 0;

            if(ambiente0[0] <= 0.6)
            {
                glEnable(GL_LIGHT1);
            }

            if(ambiente0[0] <= 0.2)
            {
                glDisable(GL_LIGHT1);
            }

            for(contador = 0; contador < 3; contador++)
            {
                ambiente0[contador] -= 0.05;
                difusa0[contador] -= 0.05;
                specular0[contador] -= 0.05;

                if(ambiente0[0] <= 0.6)
                {
                    ambiente1[contador] -= 0.05;
                    difusa1[contador] -= 0.05;
                    specular1[contador] -= 0.05;
                }                    
            }
        }
        if(escurecer == 0)
        {
            if(ambiente0[0] >= 1)
                escurecer = 1;

            if(ambiente0[0] >= 0.6)
            {
                glDisable(GL_LIGHT1);
            }

            if(ambiente0[0] >= 0.2)
            {
                glEnable(GL_LIGHT1);
            }
            
            for(contador = 0; contador < 3; contador++)
            {
                ambiente0[contador] += 0.05;
                difusa0[contador] += 0.05;
                specular0[contador] += 0.05;

                if(ambiente0[0] <= 0.6)
                {
                    ambiente1[contador] += 0.05;
                    difusa1[contador] += 0.05;
                    specular1[contador] += 0.05;
                } 
            }
        }
    }

    glutPostRedisplay();
    glutTimerFunc(1000, escurecerCenario, 0);
}

void atualiza() {
    int momentoAtual = glutGet(GLUT_ELAPSED_TIME);
    int delta = momentoAtual - momentoAnterior;

    //atualiza a rotação da elise
    rotacaoElise += 2 * delta;
    if (rotacaoElise > 360.0f) {
      rotacaoElise -= 360.0f;
    }
    if(mouse.x>3)
        movimenta.rotacao+=2;
    if(mouse.x<-3)
        movimenta.rotacao-=2;

    glFogf(GL_FOG_START, (movimenta.Z - 100));
    glFogf(GL_FOG_END, (movimenta.Z - 200)); 

    glutPostRedisplay();
}

char tituloDaJanela[200];
void atualizaFPS(int periodo) {
    sprintf(tituloDaJanela,
        "TP2 (%.2f fps)",
        fps);
    glutSetWindowTitle(tituloDaJanela);
    glutTimerFunc(periodo, atualizaFPS, periodo);
}

void SpecialInput(int key, int x, int y){
    switch(key){

    case GLUT_KEY_LEFT:
        if(cameras.dentroZeppelin<17)
            cameras.dentroZeppelin+=0.5;
        break; 

    case GLUT_KEY_RIGHT:
        if(cameras.dentroZeppelin>-17)
            cameras.dentroZeppelin-=0.5;
        break; 
    }
}

int main(int argc, char* argv[]) {

    glutInit(&argc, argv);

    glutInitContextVersion(2, 1);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(1600, 900);
    glutCreateWindow("TP2");

    glutReshapeFunc(redimensiona);
    glutDisplayFunc(desenhaCena);
    glutIdleFunc(atualiza);
    glutTimerFunc(0, atualizaFPS, 1000);
    glutKeyboardFunc(teclado);
    glutPassiveMotionFunc(movimentoMouse);
    glutTimerFunc(5000, escurecerCenario, 0);
    glutSpecialFunc(SpecialInput);

    glewInit();
    inicializa();

    glutMainLoop();
    return 0;
}
