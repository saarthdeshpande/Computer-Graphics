/*
Name: Saarth Deshpande
Roll number: 23150
Batch: G9
Assignment No.: 5
*/

#include<iostream>
#include<cmath>
#include<GL/glut.h>
using namespace std;

int n_vertices;
float xL, yL, xH, yH;   // window coordinates
float x[20], y[20];   // arrays to store x and y coordinates of points

void plotLine(int x1, int y1, int x2, int y2)
{
	glBegin(GL_LINES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
}

void lineClipping(int x1, int y1,int x2, int y2)
{
  int a[4] = {0}, b[4] = {0}, c[4];
	int xa = x1, ya = y1, xb = x2, yb = y2;
  // initialize Acode
	if(x1 < xL)
		a[3] = 1;
	if(x1 > xH)
		a[2] = 1;
	if(y1 < yL)
		a[1] = 1;
	if(y1 > yH)
		a[0] = 1;
  // initialize Bcode
	if(x2 < xL)
		b[3] = 1;
	if(x2 > xH)
		b[2] = 1;
	if(y2 < yL)
		b[1] = 1;
	if(y2 > yH)
		b[0] = 1;

	if(a[0] == 0 && a[1] == 0 && a[2] == 0 && a[3] == 0 && b[0] == 0 && b[1] == 0 && b[2] == 0 && b[3] == 0)
		plotLine(xa, ya, xb, yb);

	else
	{
		c[0] = a[0] && b[0];
		c[1] = a[1] && b[1];
		c[2] = a[2] && b[2];
		c[3] = a[3] && b[3];

		if(c[0] == 0 && c[1] == 0 && c[2] == 0 && c[3] == 0)
		{
			if(a[0] == 0 && a[1] == 0 && a[2] == 0 && a[3] == 1)
			{
				xa = xL;
				ya = (xa - x1) * (y1 - y2) / (x1 - x2) + y1;
			}
			else if(a[0] == 0 && a[1] == 0 && a[2] == 1 && a[3] == 0)
			{
				xa = xH;
				ya = (xa - x1) * (y1 - y2) / (x1 - x2) + y1;
			}
			else if(a[0] == 0 && a[1] == 1 && a[2] == 0 && a[3] == 0)
			{
				ya = yL;
				xa = (ya - y1) * (x1 - x2) / (y1 - y2) + x1;
			}
			else if(a[0] == 1 && a[1] == 0 && a[2] == 0 && a[3] == 0)
			{
				ya = yH;
				xa = (ya - y1) * (x1 - x2) / (y1 - y2) + x1;
			}
			else if(a[0] == 1 && a[1] == 0 && a[2] == 0 && a[3] == 1)
			{
				ya = yH;
				xa = (ya - y1) * (x1 - x2) / (y1 - y2) + x1;

				if((xa - x1) * (y1 - y2) - (ya - y1) * (y1 - y2) != 0)
				{
					xa = xL;
					ya = (xa - x1) * (y1 - y2) / (x1 - x2) + y1;
				}
			}
			else if(a[0] == 1 && a[1] == 0 && a[2] == 1 && a[3] == 0)
			{
				ya = yH;
				xa = (ya - y1) * (x1 - x2) / (y1 - y2) + x1;

				if((xa - x1) * (y1 - y2) - (ya - y1) * (y1 - y2) != 0)
				{
					xa = xH;
					ya = (xa - x1) * (y1 - y2) / (x1 - x2) + y1;
				}
			}
			else if(a[0] == 0 && a[1] == 1 && a[2] == 0 && a[3] == 1)
			{
				ya = yL;
				xa = (ya - y1) * (x1 - x2) / (y1 - y2) + x1;

				if((xa - x1) * (y1 - y2) - (ya - y1) * (y1 - y2) != 0)
				{
					xa = xL;
					ya = (xa - x1) * (y1 - y2) / (x1 - x2) + y1;
				}
			}
			else if(a[0] == 0 && a[1] == 1 && a[2] == 1 && a[3] == 0)
			{
				ya = yL;
				xa = (ya - y1) * (x1 - x2) / (y1 - y2) + x1;

				if((xa - x1) * (y1 - y2) - (ya - y1) * (y1 - y2) != 0)
				{
					xa = xH;
					ya = (xa - x1) * (y1 - y2) / (x1 - x2) + y1;
				}
			}

			if(b[0] == 0 && b[1] == 0 && b[2] == 0 && b[3] == 1)
			{
				xb = xL;
				yb = (xb - x1) * (y1 - y2) / (x1 - x2) + y1;
			}
			else if(b[0] == 0 && b[1] == 0 && b[2] == 1 && b[3] == 0)
			{
				xb = xH;
				yb = (xb - x1) * (y1 - y2) / (x1 - x2) + y1;
			}
			else if(b[0] == 0 && b[1] == 1 && b[2] == 0 && b[3] == 0)
			{
				yb = yL;
				xb = (yb - y1) * (x1 - x2) / (y1 - y2) + x1;
			}
			else if(b[0] == 1 && b[1] == 0 && b[2] == 0 && b[3] == 0)
			{
				yb = yH;
				xb = (yb - y1) * (x1 - x2) / (y1 - y2) + x1;
			}
			else if(b[0] == 1 && b[1] == 0 && b[2] == 0 && b[3] == 1)
			{
				yb = yH;
				xb = (yb - y1) * (x1 - x2) / (y1 - y2) + x1;

				if((xb - x1) * (y1 - y2) - (yb - y1) * (y1 - y2) != 0)
				{
					xb = xL;
					yb = (xb - x1) * (y1 - y2) / (x1 - x2) + y1;
				}
			}
			else if(b[0] == 1 && b[1] == 0 && b[2] == 1 && b[3] == 0)
			{
				yb = yH;
				xb = (yb - y1) * (x1 - x2) / (y1 - y2) + x1;

				if((xb - x1) * (y1 - y2) - (yb - y1) * (y1 - y2) != 0)
				{
					xb = xH;
					yb = (xb - x1) * (y1 - y2) / (x1 - x2) + y1;
				}
			}
			else if(b[0] == 0 && b[1] == 1 && b[2] == 0 && b[3] == 1)
			{
				yb = yL;
				xb = (yb - y1) * (x1 - x2) / (y1 - y2) + x1;

				if((xb - x1) * (y1 - y2) - (yb - y1) * (y1 - y2) != 0)
				{
					xb = xL;
					yb = (xb - x1) * (y1 - y2) / (x1 - x2) + y1;
				}
			}
			else if(b[0] == 0 && b[1] == 1 && b[2] == 1 && b[3] == 0)
			{
				yb = yL;
				xb = (yb - y1) * (x1 - x2) / (y1 - y2) + x1;

				if((xb - x1) * (y1 - y2) - (yb - y1) * (y1 - y2) != 0)
				{
					xb = xH;
					yb = (xb - x1) * (y1 - y2) / (x1 - x2) + y1;
				}
			}
			plotLine(xa,ya,xb,yb);
		}
	}
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
	// plot window
	glBegin(GL_LINE_LOOP);
	glVertex2f(xL,yL);
	glVertex2f(xH,yL);
	glVertex2f(xH,yH);
	glVertex2f(xL,yH);
	glEnd();

	glPointSize(2.0);
	glColor3f(1.0,1.0,0.0);

	if(n_vertices == 2)
		lineClipping(x[0],y[0],x[1],y[1]);
	else
	{
		for(int i = 0;i < n_vertices;i++)
			lineClipping(x[i],y[i],x[i + 1],y[i + 1]);
		lineClipping(x[n_vertices - 1],y[n_vertices - 1],x[0],y[0]);
	}
	glFlush();
}

int main(int argc, char **argv)
{
	cout << "\nWindow Coordinates:\nLower Left Point: ";
	cin >> xL >> yL;
	cout<<"Top Right Point: ";
	cin >> xH >> yH;

	cout << "\nNo. of Vertices of Polygon: ";
	cin >> n_vertices;
  cout << endl;

	for(int i = 0; i < n_vertices;i++)
	{
		cout << "Vertex #" << i + 1 << ": ";
		cin >> x[i] >> y[i];
  }

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1366,768);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Line / Polygon Clipping");

	glClearColor(0.0,0.0,0.0,0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-780,780,-420,420);

	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
