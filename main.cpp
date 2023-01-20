#include <stdlib.h>
#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

int tabuleiro[3][3];
int turno, resultado, mainmenu = 0, i = 0, j = 0, k = 0;
bool fim = false;
char p1[10],p2[10];

void Inicializacao();

void DesenhandoString(void *font,const char s[],float x,float y);

void PressionandoBotao(unsigned char tecla,int x,int y);

void CliquedoMouse(int bt,int tecla2,int x,int y);

void DesenhandoLinhas();

void DesenhandoCirculo(float cx, float cy, float r, int num);

void DesenhodoXO();

bool ChecandoVencedor();

bool ChecandoDesenho();

void Display();

void Reshape(int x, int y);

int main(int argc, char **argv)
{
	Inicializacao();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
	glutInitWindowPosition(550,200);
	glutInitWindowSize(600,650);
	glutCreateWindow("Jogo da Velha");
	glutReshapeFunc(Reshape);
	glutDisplayFunc(Display);
	glutKeyboardFunc(PressionandoBotao);
	glutMouseFunc(CliquedoMouse);
	glutIdleFunc(Display);
	glutMainLoop();
    return 0;
}
void Inicializacao()
{
	turno=1;
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
			tabuleiro[i][j]=0;
	}
	i = 0;j = 0;k = 0;
}
void DesenhandoString(void *font,const char s[],float x,float y)
{
	unsigned int i;
	glRasterPos2f(x,y);
	for(i=0;i<strlen(s);i++)
	{
        glutBitmapCharacter(font,s[i]);
	}
}
void PressionandoBotao(unsigned char tecla,int x,int y)
{
	if(mainmenu == 1)
	{
		if(k == 0 && tecla != 13) p1[i++] = tecla;
		else if(tecla == 13 && k == 0) k = 1;
		else if(k == 1 && tecla != 13) p2[j++] = tecla;
		else if(tecla == 13 && k == 1) mainmenu = 2;
	}

	else
    {
        switch(tecla)
        {
            case 'p':
                mainmenu = 1;
                fim=false;
                Inicializacao();
                glutPostRedisplay();

            break;

            case 's':
                if(fim==true)
            {
                mainmenu = 0;
                fim=false;
                Inicializacao();
            }
            break;
            case 'n':
            if(fim==true)
            {
                exit(0);
            }
            break;
            default: exit(0);
        }
    }
}
void CliquedoMouse(int bt,int tecla2,int x,int y)
{
	if(fim==false && bt==GLUT_LEFT_BUTTON && tecla2==GLUT_DOWN)
	{
		if(turno==1)
		{
			if(tabuleiro[(y-50)/200][x/200]==0)
			{
				tabuleiro[(y-50)/200][x/200]=1;
				turno=2;
			}
		}
		else if(turno==2)
		{
			if(tabuleiro[(y-50)/200][x/200]==0)
			{
				tabuleiro[(y-50)/200][x/200]=2;
				turno=1;
			}
		}
	}
}
void DesenhandoLinhas()
{
	glBegin(GL_LINES);
	glColor3f(1,1,1);

	glVertex2f(200,50);
	glVertex2f(200,640);
	glVertex2f(400,640);
	glVertex2f(400,50);

	glVertex2f(0,250);
	glVertex2f(600,250);
	glVertex2f(0,450);
	glVertex2f(600,450);

	glEnd();
}
void DesenhandoCirculo(float cx, float cy, float r, int num)
{
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < num; i++)
    {
        float teta = 2.0f * 3.1415926f * float(i) / float(num);
        float x = r * cosf(teta);
        float y = r * sinf(teta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}
void DesenhodoXO()
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(tabuleiro[i][j]==1)
			{
				glBegin(GL_LINES);
				glVertex2f(50 + j * 200 - 25, 100 + i * 200 - 25);
				glVertex2f(150 + j * 200 + 25, 200 + i * 200 + 25);
				glVertex2f(50 + j * 200 - 25, 200 + i * 200 + 25);
				glVertex2f(150 + j * 200 + 25, 100 + i * 200 - 25);
				glEnd();
			}
			else if(tabuleiro[i][j]==2)
			{
				DesenhandoCirculo(100 + j*200 , 150 + i*200 , 60 , 50);
			}
		}
	}
}
bool ChecandoVencedor()
{
	int i, j;
	for(i=0;i<3;i++)
	{
		for(j=1;j<3;j++)
		{
			if(tabuleiro[i][0]!=0 && tabuleiro[i][0]==tabuleiro[i][j])
			{
				if(j==2)
				{
					return true;
				}
			}
			else
				break;
		}
	}
	for(i=0;i<3;i++)
	{
		for(j=1;j<3;j++)
		{
			if(tabuleiro[0][i]!=0 && tabuleiro[0][i]==tabuleiro[j][i])
			{
				if(j==2)
					return true;
			}
			else
				break;
		}
	}
	if((tabuleiro[0][0]!=0 && tabuleiro[0][0]==tabuleiro[1][1] && tabuleiro[0][0]==tabuleiro[2][2])
	|| (tabuleiro[2][0]!=0 && tabuleiro[2][0]==tabuleiro[1][1] && tabuleiro[2][0]==tabuleiro[0][2]))
		return true;
	return false;
}
bool ChecandoDesenho()
{
	int i, j;
	bool draw;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			if(tabuleiro[i][j]==0)
				return false;
		}
	}
	return true;
}
void Display(){
	if(mainmenu == 0)
		{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0,0.3,0.7,0.1);
		glColor3f(1, 1, 1);
		DesenhandoString(GLUT_BITMAP_HELVETICA_18, "Jogo da Velha", 220, 180);
		glColor3f(1, 1, 1);
		DesenhandoString(GLUT_BITMAP_HELVETICA_18, "Pressione P para iniciar", 180, 230);
		glColor3f(1, 1, 1);
		glutSwapBuffers();
		}

	if(mainmenu == 1)
		{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0,0.3,0.7,0.1);
		glColor3f(1, 1, 1);
		DesenhandoString(GLUT_BITMAP_HELVETICA_18, "Jogador 1: ", 60, 230);
		glColor3f(1, 1, 1);
		DesenhandoString(GLUT_BITMAP_HELVETICA_18, p1, 260, 230);
		glColor3f(1, 1, 1);
		DesenhandoString(GLUT_BITMAP_HELVETICA_18, "Jogador 2: ", 60, 280);
		glColor3f(1, 1, 1);
		DesenhandoString(GLUT_BITMAP_HELVETICA_18, p2, 260, 280);
		glutSwapBuffers();
		}

	if(mainmenu == 2)
	{

	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0,0.3,0.7,0.1);
	glColor3f(0, 0, 0);
	if(!fim){

	DesenhandoLinhas();
	DesenhodoXO();
	}

	if(ChecandoVencedor() == true)
	{
		if(turno == 2 || turno == -1)
		{
			usleep(800000);
			fim = true;
			resultado = 1;
		}
		else if(turno == 1 )
		{
			usleep(800000);
			fim = true;
			resultado = 2;
		}

	}
	else if(ChecandoDesenho() == true)
	{
		usleep(800000);
		fim = true;
		resultado = 0;
	}
	if(fim == true)
	{
		glColor3f(1, 1, 1);
		DesenhandoString(GLUT_BITMAP_HELVETICA_18, "Fim de Jogo", 250, 160);
		if(resultado == 0)
			DesenhandoString(GLUT_BITMAP_HELVETICA_18, "Velha", 250, 235);
		else {
		DesenhandoString(GLUT_BITMAP_HELVETICA_18, "Vencedor: ", 250, 235);
		if(resultado == 1)
			DesenhandoString(GLUT_BITMAP_HELVETICA_18, p1, 250, 260);
		if(resultado == 2)
			DesenhandoString(GLUT_BITMAP_HELVETICA_18, p2, 250, 260);
		}
		DesenhandoString(GLUT_BITMAP_HELVETICA_18, "Deseja continuar (S/N)", 190, 310);
	}

	glutSwapBuffers();
}
}
void Reshape(int x, int y)
{
	glViewport(0, 0, x, y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, x, y, 0, 0, 1);
	glMatrixMode(GL_MODELVIEW);
}
