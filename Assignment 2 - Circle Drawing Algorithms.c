#include <GL/freeglut.h>
#include <GL/gl.h>
#include <math.h>
#include <stdio.h>

void draw_pixel(int x,int y)
{
	glBegin(GL_POINTS);
	glVertex2i(x,y);
   	glEnd();
}

void bresenhamCircle(int r,int xc,int yc)
{
	int x1 = 0,y1 = r;
	int d = 3 - (2 * r);
	while(x1 <= y1)
	{
		draw_pixel(xc+x1, yc+y1);
		draw_pixel(xc+x1, yc-y1);
		draw_pixel(xc-x1, yc+y1);
		draw_pixel(xc-x1, yc-y1);
		draw_pixel(xc+y1, yc+x1);
		draw_pixel(xc+y1, yc-x1);
		draw_pixel(xc-y1, yc+x1);
		draw_pixel(xc-y1, yc-x1);
		if(d <= 0)
		{
			x1++;
			d = d + (4 * x1) + 6;
		}
		else
		{
			x1++;
			y1--;
			d = d + 4 * (x1 - y1) + 10;
		}
	}
}

void midpointCircle(int radius,int xc,int yc)
{
	int x = radius;
	int y = 0;
	int pk = 1 - radius;
	while(x > y)
	{
		draw_pixel(x + xc,y + yc);
		draw_pixel(-x + xc,-y + yc);
		draw_pixel(-x + xc,y + yc);
		draw_pixel(x + xc,-y + yc);
		draw_pixel(y + xc,x + yc);
		draw_pixel(-y + xc,-x + yc);
		draw_pixel(y + xc,-x + yc);
		draw_pixel(-y + xc,x + yc);
		y++;
		if(pk <= 0)
			pk = pk + (2 * y) + 1;
		else
		{
			x--;
			pk = pk + (2 * y) - (2 * x) + 1; 
		}

	}
}

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
	int r,xc,yc;
	printf("\nEnter Coordinates of Inner Circle:\n");
	printf("Enter Radius : ");
	scanf("%d",&r);
	printf("Enter Xc and Yc :");
	scanf("%d%d",&xc,&yc);
	
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0); 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-320,320,-240,240);
	glBegin(GL_LINES);
	glVertex2i(-320, 0);
	glVertex2i(320, 0);
	glVertex2i(0, -240);
	glVertex2i(0, 240);
	glEnd();

	// Middle Triangle

	bresenhamLine(xc-r*1.732, yc-r, xc+r*1.732, yc-r);
	bresenhamLine(xc, yc+2*r, xc+r*1.732, yc-r);
	bresenhamLine(xc-r*1.732, yc-r, xc, yc+2*r);
	
	bresenhamCircle(r,xc,yc);	// Inner Small Circle
	midpointCircle(2*r,xc,yc);	// Outer Large Circle
	glFlush();
}

int main(int argc, char** argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(1024,768);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Assignment 2");
	glutDisplayFunc(renderFunction);
	glutMainLoop();    
	return 0;
}
