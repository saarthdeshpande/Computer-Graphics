#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void Triangle();
void Rhombus();
void initTriangle();
void initRhombus();
void DDALine(int,int,int,int);
void matmul(int);
void translateTriangle();
void translateRhombus();
void rotateTriangle();
void rotateRhombus();
void shearTriangle();
void shearRhombus();
void scaleTriangle();
void scaleRhombus();

int before[10][3];
float trans[3][3], after[10][3];

int main(int argc, char**argv)
{
    int choice;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("2-D Transformations");
    
    printf("\n2-D TRANSFORMATIONS\n\n1. Equilateral Triangle\n2. Rhombus\n3. Exit\nYour Choice: ");
    scanf("%d", &choice);
    switch(choice)
    {
        case 1: glutDisplayFunc(Triangle);
          		glutMainLoop();
        	    break;
        case 2: glutDisplayFunc(Rhombus);
            	glutMainLoop();
           		break;
        case 3: return 1;
	}
	return 0;
}

void Triangle()
{
    int choice;
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D(-1000, 1000, -1000, 1000);
    
    glColor3f(0.5, 0.5, 0.5);
    DDALine(0, -1000, 0, 1000);
    DDALine( -1000, 0, 1000, 0);
    
    initTriangle();		// original figure
    glColor3f(0.0, 1.0, 0.0);
    DDALine(before[0][0], before[0][1], before[1][0], before[1][1]);
    DDALine(before[1][0], before[1][1], before[2][0], before[2][1]);
    DDALine(before[0][0], before[0][1], before[2][0], before[2][1]);

    
    printf("\nEQUILATERAL TRIANGLE\n\n1. Translation\n2. Rotation\n3. Shearing\n4. Scaling\nYour Choice: ");
    scanf("%d", &choice);
    switch(choice)
    {
        case 1: translateTriangle();
            	break;
        case 2: rotateTriangle();
            	break;
        case 3: shearTriangle();
           		break;
        case 4: scaleTriangle();
            	break;
    }
    
}

void Rhombus()
{
    int choice;
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D(-1000, 1000, -1000, 1000);
    
    glColor3f(0.5, 0.5, 0.5);
    DDALine(0, -1000, 0, 1000);
    DDALine( -1000, 0, 1000, 0);
    
    initRhombus();	// original figure
    glColor3f(0.0, 1.0, 0.0);
    DDALine(before[0][0], before[0][1], before[1][0], before[1][1]);
    DDALine(before[1][0], before[1][1], before[2][0], before[2][1]);
    DDALine(before[3][0], before[3][1], before[2][0], before[2][1]);
    DDALine(before[0][0], before[0][1], before[3][0], before[3][1]);

    
    printf("\nRHOMBUS\n\n1. Translation\n2. Rotation\n3. Shearing\n4. Scaling\nYour Choice: ");
    scanf("%d", &choice);
    switch(choice)
    {
        case 1: translateRhombus();
            	break;
        case 2: rotateRhombus();
            	break;
        case 3: shearRhombus();
            	break;
        case 4: scaleRhombus();
            	break;
    } 
}

void initTriangle()
{
    for(int i = 0;i < 10;i++)
        before[i][2] = after[i][2] = 1;
    
    before[0][0] = 500;
    before[0][1] = 500;
    before[1][0] = 0;
    before[1][1] = -500;
    before[2][0] = 1000;
    before[2][1] = -500;
}

void initRhombus()
{
    for(int i = 0;i < 10;i++)
        before[i][2] = after[i][2] = 1;
    
    before[0][0] = 100;
    before[0][1] = 0;
    before[1][0] = 500;
    before[1][1] = 0;
    before[2][0] = 700;
    before[2][1] = 700;
    before[3][0] = 300;
    before[3][1] = 700;
}


void DDALine(int x1, int y1, int x2, int y2)
{
    float dx = x2 - x1,dy = y2 - y1,xi,yi;
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
		glVertex2f(round(x1 + xi * i),round(y1 + yi * i));
		glEnd();
	}
    glFlush();   
}

void matmul(int n_vertices)
{
    for(int i = 0;i < n_vertices + 1;i++)
        for(int j = 0;j < 3;j++)
            after[i][j] = 0;
            
    for (int i = 0; i < n_vertices + 1;i++)
    {
        for(int j = 0; j < 3;j++)
        {
            after[i][j] = 0;
            for(int k = 0; k < 3;k++)
                after[i][j] += (before[i][k] * trans[k][j]);
        }
    }
}

void translateTriangle()
{
    int tx, ty;
    
    printf("\nX Translation Factor: ");
    scanf("%d", &tx);
    printf("\nY Translation Factor: ");
    scanf("%d", &ty);
    
    for(int i = 0;i < 3;i++)
        for(int j = 0;j < 3;j++)
            (i == j) ? trans[i][j] = 1 : trans[i][j] = 0;
    
    trans[2][0] = tx;
    trans[2][1] = ty;
    
    matmul(3);
    
    glColor3f(1.0, 1.0, 0.0);
    DDALine(after[0][0], after[0][1], after[1][0], after[1][1]);
    DDALine(after[1][0], after[1][1], after[2][0], after[2][1]);
    DDALine(after[0][0], after[0][1], after[2][0], after[2][1]);
}

void translateRhombus()
{
    int tx, ty;
    
    printf("\nX Translation Factor: ");
    scanf("%d", &tx);
    printf("\nY Translation Factor: ");
    scanf("%d", &ty);
    
    for(int i = 0;i < 3;i++)
        for(int j = 0;j < 3;j++)
            (i == j) ? trans[i][j] = 1 : trans[i][j] = 0;

    trans[2][0] = tx;
    trans[2][1] = ty;
    
    matmul(4);
    
    glColor3f(1.0, 1.0, 0.0);
    DDALine(after[0][0], after[0][1], after[1][0], after[1][1]);
    DDALine(after[1][0], after[1][1], after[2][0], after[2][1]);
    DDALine(after[3][0], after[3][1], after[2][0], after[2][1]);
    DDALine(after[0][0], after[0][1], after[3][0], after[3][1]);
}

void rotateTriangle()
{
    float d;
    
    printf("\nAngle (degrees): ");
    scanf("%f", &d);
    d = (float)(3.14 * d / 180);
    
    for(int i = 0;i < 3;i++)
        for(int j = 0;j < 3;j++)
            trans[i][j] = 0;
            
    trans[0][0] = cos(d);
    trans[0][1] = sin(d);
    trans[1][0] = -cos(d);
    trans[1][1] = sin(d);
    trans[2][2] = 1;
    
    matmul(3);
    
    glColor3f(1.0, 1.0, 0.0);
    DDALine(after[0][0], after[0][1], after[1][0], after[1][1]);
    DDALine(after[1][0], after[1][1], after[2][0], after[2][1]);
    DDALine(after[0][0], after[0][1], after[2][0], after[2][1]);
}

void rotateRhombus()
{
    float d;
    
    printf("\nAngle (degrees): ");
    scanf("%f", &d);
    d = (float)(3.14 * d / 180);
 
    for(int i = 0;i < 3;i++)
        for(int j = 0;j < 3;j++)
            trans[i][j] = 0;
            
    trans[0][0] = cos(d);
    trans[0][1] = sin(d);
    trans[1][0] = -cos(d);
    trans[1][1] = sin(d);
    trans[2][2] = 1;
    
    matmul(4);
    
    glColor3f(1.0, 1.0, 0.0);
    DDALine(after[0][0], after[0][1], after[1][0], after[1][1]);
    DDALine(after[1][0], after[1][1], after[2][0], after[2][1]);
    DDALine(after[3][0], after[3][1], after[2][0], after[2][1]);
    DDALine(after[0][0], after[0][1], after[3][0], after[3][1]);
}
void shearTriangle()
{
    int tx, ty;
    
    printf("\nX-Shear: ");
    scanf("%d", &tx);
    printf("\nY-Shear: ");
    scanf("%d", &ty);
    
    for(int i = 0;i < 3;i++)
        for(int j = 0;j < 3;j++)
            (i == j) ? trans[i][j] = 1 : trans[i][j] = 0;
    
    trans[1][0] = tx;
    trans[0][1] = ty;
    
    after[0][0] = 600;
    after[0][1] = 500;
    after[1][0] = 0;
    after[1][1] = -500;
    after[2][0] = 1000;
    after[2][1] = -500;
    
    glColor3f(1.0, 1.0, 0.0);
    DDALine(after[0][0], after[0][1], after[1][0], after[1][1]);
    DDALine(after[1][0], after[1][1], after[2][0], after[2][1]);
    DDALine(after[0][0], after[0][1], after[2][0], after[2][1]);
}

void shearRhombus()
{
    int tx, ty;
    
    printf("\nX-Shear: ");
    scanf("%d", &tx);
    printf("\nY-Shear: ");
    scanf("%d", &ty);
    
    for(int i = 0;i < 3;i++)
        for(int j = 0;j < 3;j++)
            (i == j) ? trans[i][j] = 1 : trans[i][j] = 0;
    
    trans[1][0] = tx;
    trans[0][1] = ty;
    
    for(int i = 0;i < 5;i++)
        for(int j = 0;j < 3;j++)
            (j == 2) ? after[i][j] = 1 : after[i][j] = 0;
    
    // X-axis
    after[0][0] = 100;
    after[0][1] = 0;
    after[1][0] = 500;
    after[1][1] = 0;
    after[2][0] = 800;
    after[2][1] = 700;
    after[3][0] = 400;
    after[3][1] = 700;
    
    
    glColor3f(1.0, 0.5, 1.0);
    DDALine(after[0][0], after[0][1], after[1][0], after[1][1]);
    DDALine(after[1][0], after[1][1], after[2][0], after[2][1]);
    DDALine(after[3][0], after[3][1], after[2][0], after[2][1]);
    DDALine(after[0][0], after[0][1], after[3][0], after[3][1]);
    
    // Y-axis
    after[0][0] = 100;
    after[0][1] = 0;
    after[1][0] = 500;
    after[1][1] = 100;
    after[2][0] = 700;
    after[2][1] = 800;
    after[3][0] = 300;
    after[3][1] = 700;
    
    
    glColor3f(1.0, 1.0, 0.0);
    DDALine(after[0][0], after[0][1], after[1][0], after[1][1]);
    DDALine(after[1][0], after[1][1], after[2][0], after[2][1]);
    DDALine(after[3][0], after[3][1], after[2][0], after[2][1]);
    DDALine(after[0][0], after[0][1], after[3][0], after[3][1]);
}

void scaleTriangle()
{
    printf("\nX-Scale Factor: ");
    scanf("%f", &trans[0][0]);
    printf("\nY-Scale Factor: ");
    scanf("%f", &trans[1][1]);
    
    for(int i = 0;i < 3;i++)
        for(int j = 0;j < 3;j++)
            (i != j) ? trans[i][j] = 0 : 1;
            
    trans[2][2] = 1;
    
    matmul(3);
    
    glColor3f(1.0, 1.0, 0.0);
    DDALine(after[0][0], after[0][1], after[1][0], after[1][1]);
    DDALine(after[1][0], after[1][1], after[2][0], after[2][1]);
    DDALine(after[0][0], after[0][1], after[2][0], after[2][1]);
}

void scaleRhombus()
{
    printf("\nX-Scale Factor: ");
    scanf("%f", &trans[0][0]);
    printf("\nY-Scale Factor: ");
    scanf("%f", &trans[1][1]);
    
    for(int i = 0;i < 3;i++)
        for(int j = 0;j < 3;j++)
            (i != j) ? trans[i][j] = 0 : 1;
            
    trans[2][2] = 1;
    
    matmul(4);
    
    glColor3f(1.0, 1.0, 0.0);
    DDALine(after[0][0], after[0][1], after[1][0], after[1][1]);
    DDALine(after[1][0], after[1][1], after[2][0], after[2][1]);
    DDALine(after[3][0], after[3][1], after[2][0], after[2][1]);
    DDALine(after[0][0], after[0][1], after[3][0], after[3][1]);
}
