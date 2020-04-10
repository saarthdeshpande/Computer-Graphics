#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>

float trans[3][3], ans[20][3], mat[20][3];
int tx,ty;
float x, y;

void __init__();
void putPixel(int,int);

void draw();


typedef struct Color
{
	GLubyte r;
	GLubyte g;
	GLubyte b;
}Color;

Color b_clr,f_clr;

void __init__()
{
	b_clr.r = 0;
	b_clr.g = 0;
	b_clr.b = 0;

	f_clr.r = 150;
	f_clr.g = 150;
	f_clr.b = 150;

	float x1,y1;
	printf("X Co-ordinate: ");
	scanf("%f",&x);
	printf("Y Co-ordinate: ");
	scanf("%f",&y);
	x1 = x;
	y1 = y;
	for(int i = 0;i < 10;i += 2)
	{
		mat[i][0] = x;
		mat[i][1] = y;
		mat[i][2] = 1;

		mat[i+1][0] = x + 120;
		mat[i+1][1] = y;
		mat[i+1][2] = 1;

		y += 30;
	}
	y = y1;
	for(int i = 10;i < 20;i += 2)
	{
		mat[i][0] = x;
		mat[i][1] = y;
		mat[i][2] = 1;

		mat[i+1][0] = x;
		mat[i+1][1] = y + 120;
		mat[i+1][2] = 1;

		x += 30;
	}

	float root2 = 1/(sqrt(2));
	trans[0][0] = trans[0][1] = trans[1][1] = root2;
	trans[1][0] = -root2;
	trans[0][2] = trans[1][2]=0;

	tx = mat[0][0];
	ty = mat[0][1];

	trans[2][0] = ((ty - tx) * root2) + tx;
	trans[2][1] = ((-ty - tx) * root2) + ty;
	trans[2][2] = 1;

	for(int i = 0;i < 20;i++)
	{
		for(int j = 0;j < 3;j++)
		{
			ans[i][j]=0;
			for(int k = 0;k < 3;k++)
				ans[i][j] += mat[i][k] * trans[k][j];
		}
	}
	x = x1;
	y = y1;
}

void putPixel(int x,int y)
{
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();
	glFlush();
}

void bresenhamLine(int x1,int y1,int x2,int y2)
{
	float dx = abs(x2 - x1),dy = abs(y2 - y1),xi = x1,yi = y1;
	int xinc = x1 < x2 ? 1 : -1;
	int yinc = y1 < y2 ? 1 : -1;
	int n = dx > dy ? dx : dy;
	if(dx > dy)
	{
		int p = 2 * dy - dx;
		for(int i = 0;i < n;i++)
		{
			putPixel(round(xi),round(yi));
			xi += xinc;
			p += (2 * dy);
			if(p >= 0)
			{
				p -= (2 * dx);
				yi += yinc;
			}
		}
	}
	else
	{
		int p = 2 * dx - dy;
		for(int i = 0;i < n;i++)
		{
			putPixel(round(xi),round(yi));
			yi += yinc;
			p += (2 * dx);
			if(p >= 0)
			{
				p -= (2 * dy);
				xi += xinc;
			}
		}
	}
}

void boundaryFill(float x,float y)
{
	Color current;
	glReadPixels(x,y,1,1,GL_RGB,GL_UNSIGNED_BYTE,&current);

	if((current.r != b_clr.r || current.g != b_clr.g || current.b != b_clr.b) && (current.r != f_clr.r || current.g != f_clr.g || current.b != f_clr.b))
	{
		glBegin(GL_POINTS);
		glVertex2d(x,y);
		glColor3ub(f_clr.r,f_clr.g,f_clr.b);
		glEnd();
		glFlush();
		boundaryFill(x,y+1);
		boundaryFill(x-1,y);
		boundaryFill(x,y-1);
		boundaryFill(x+1,y);
  }
}

void draw()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3i(0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(0,750,0,750);
	for(int i = 0;i < 20;i += 2)
		bresenhamLine(ans[i][0],ans[i][1],ans[i+1][0],ans[i+1][1]);

	float factor = 60 / (sqrt(2));
	float add = 30 / sqrt(2);
	y += add;

	boundaryFill(x,y);

	for(int i = 2;i <= 6;i++)
		boundaryFill(x,y + i * add);

	y += factor;
	boundaryFill(x + factor,y);
	boundaryFill(x + factor,y + factor);
	boundaryFill(x - factor,y);
	boundaryFill(x - factor,y + factor);

	glEnd();
	glFlush();
}

int main(int argc,char **argv)
{
	__init__();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(750,750);
  glutCreateWindow("4x4 Chessboard Rotated at 45°");
	glutDisplayFunc(draw);
	glutMainLoop();
}
