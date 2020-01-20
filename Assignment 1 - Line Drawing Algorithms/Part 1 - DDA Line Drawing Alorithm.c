#include <GL/freeglut.h>
#include <GL/gl.h>
#include<stdio.h>
#include<math.h>

void DDALine(float x1,float y1,float x2,float y2)
{
	float dx = x2-x1,dy = y2-y1,xi,yi;
	int steps,i;
	if(abs(dx) > abs(dy))	
		steps = abs(dx);	
	else	
		steps = abs(dy);
	xi = dx / steps;
	yi = dy / steps;
	for(i = 0;i < steps;i++)
	{
		glBegin(GL_POINTS);
		glVertex2f(round(x1+xi*i),round(y1+yi*i));
		glEnd();
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
	
	DDALine(x1,y1,x1,y1+y2);
	DDALine(x1,y1+y2,x1+x2,y1+y2);
	DDALine(x1+x2,y1,x1+x2,y1+y2);
	DDALine(x1,y1,x1+x2,y1);

	// Inner Diamond	
	
	DDALine(x1,(y1+y2/2),(x1+x2/2),y1+y2);
	DDALine(x1+x2,(y1+y2/2),(x1+x2/2),y1+y2);
	DDALine((x1+x2/2),y1,x1+x2,(y1+y2/2));	
	DDALine((x1+x2/2),y1,x1,(y1+y2/2));

	// Inner Square

	DDALine((x1+x2/4),(y1+y2/4),(x1+x2/4),(y1+3*y2/4));	
	DDALine((x1+x2/4),(y1+3*y2/4),(x1+3*x2/4),(y1+3*y2/4));
	DDALine((x1+x2/4),(y1+y2/4),(x1+3*x2/4),(y1+y2/4));
	DDALine((x1+3*x2/4),(y1+y2/4),(x1+3*x2/4),(y1+3*y2/4));
	
	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(512,384);
	glutInitWindowPosition(100,100);
	glutCreateWindow("DDA Line Drawing Algorithm");
	glutDisplayFunc(renderFunction);
	glutMainLoop();    
	return 0;
}
