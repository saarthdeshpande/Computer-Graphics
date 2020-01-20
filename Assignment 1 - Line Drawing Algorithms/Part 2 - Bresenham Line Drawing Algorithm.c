#include <GL/freeglut.h>
#include <GL/gl.h>
#include<stdio.h>
#include<math.h>

void bresenhamLine(float x1,float y1,float x2,float y2)
{
	float dx = abs(x2 - x1),dy = abs(y2 - y1),xi = x1,yi = y1;
	int xinc = x1 < x2 ? 1 : -1;
	int yinc = y1 < y2 ? 1 : -1;
	int inc1,inc2,p;
	int n = dx > dy ? dx : dy;
	if(dx > dy)
	{
		p = 2 * dy - dx;
		inc1 = 2 * (dy - dx);
		inc2 = 2 * dy;
		for(int i = 0;i < n;i++)
		{
			glBegin(GL_POINTS);
			glVertex2f(round(xi),round(yi));
			glEnd();
			xi += xinc;
			if(p <= 0)
				p += inc2;
			else
			{
				p += inc1;
				yi += yinc;
			}
		}
	}
	else
	{
		p = 2 * dx - dy;
		inc1 = 2 * (dx - dy);
		inc2 = 2 * dx;
		for(int i = 0;i < n;i++)
		{
			glBegin(GL_POINTS);
			glVertex2f(round(xi),round(yi));
			glEnd();
			yi += yinc;
			if(p <= 0)
				p += inc2;
			else
			{
				p += inc1;
				xi += xinc;
			}
		}
	}
}

void renderFunction()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();	
	gluOrtho2D(0.0,1024.0,0.0,768.0);
	printf("Enter Coordinates:\n");
	float x1,y1,x2,y2;
	printf("Point A: ");
	scanf("%f%f",&x1,&y1);
	printf("Point B: ");
	scanf("%f%f",&x2,&y2);

	// Outer Square
	
	bresenhamLine(x1,y1,x1,y1+y2);
	bresenhamLine(x1,y1+y2,x1+x2,y1+y2);
	bresenhamLine(x1+x2,y1,x1+x2,y1+y2);
	bresenhamLine(x1,y1,x1+x2,y1);

	// Inner Diamond

	bresenhamLine(x1,(y1+y2/2),(x1+x2/2),y1+y2);
	bresenhamLine(x1+x2,(y1+y2/2),(x1+x2/2),y1+y2);
	bresenhamLine((x1+x2/2),y1,x1+x2,(y1+y2/2));	
	bresenhamLine((x1+x2/2),y1,x1,(y1+y2/2));

	// Inner Square

	bresenhamLine((x1+x2/4),(y1+y2/4),(x1+x2/4),(y1+3*y2/4));	
	bresenhamLine((x1+x2/4),(y1+3*y2/4),(x1+3*x2/4),(y1+3*y2/4));
	bresenhamLine((x1+x2/4),(y1+y2/4),(x1+3*x2/4),(y1+y2/4));
	bresenhamLine((x1+3*x2/4),(y1+y2/4),(x1+3*x2/4),(y1+3*y2/4));

	glFlush();
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(512,384);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Bresenham's Line Drawing Algorithm");
	glutDisplayFunc(renderFunction);
	glutMainLoop();    
	return 0;
}
