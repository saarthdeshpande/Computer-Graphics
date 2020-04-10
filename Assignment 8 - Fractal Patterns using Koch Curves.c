#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

GLfloat Xold = -0.7, Yold = 0.5;

void kochCurve(GLfloat dir,GLfloat len,GLint iter)
{
	GLdouble dirRad = 0.0174533 * dir;
	GLfloat Xnew = Xold + len * cos(dirRad);
	GLfloat Ynew = Yold + len * sin(dirRad);
	if(iter == 0) 
	{
		glVertex2f(Xold, Yold);
		glVertex2f(Xnew, Ynew);
		Xold = Xnew;
		Yold = Ynew;
	}
	else
	{
		iter -= 1;	
		len = len / 3;			//Keeps the shape size same so that it doesn't scale up for larger iterations
		kochCurve(dir, len, iter);	//draw the four parts of the side _/\_
		dir += 60.0;
		kochCurve(dir, len, iter);
		dir -= 120.0;
		kochCurve(dir, len, iter);
		dir += 60.0;
		kochCurve(dir, len, iter);
	}
}

void displayFunction()
{
	 glClear(GL_COLOR_BUFFER_BIT);
	 glBegin(GL_LINES);
	 glColor3f(1.0, 0.0, 0.0);

	 kochCurve(0.0,0.5,1);
	 kochCurve(-120.0, 0.5, 1);
	 kochCurve(120.0,0.5,1);

	 glEnd();
	 glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("Fractal Patterns using Koch Curves");
	glutDisplayFunc(displayFunction);
	glutMainLoop();
}
