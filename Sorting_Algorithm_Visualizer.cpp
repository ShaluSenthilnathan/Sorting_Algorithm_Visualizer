#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<GL\glut.h>

#define SORT_NO  1 //the number of sorting algorithms 
#define MAX_ELE  50
#define SPEED  1000 //Speed of sorting

int a[MAX_ELE];	
int k = 0, sorting = 0, sort_count = 0;
int i, j, flag, count, dirflag;

const char* sort_algo_string[] = { "Bubble Sort" };  //array containing the sorting algorithms 


void text_output(int x, int y, const char* string, void* font)
{
	int len, i;
	len = (int)strlen(string);

	// Calculate the center position
	int screenWidth = glutGet(GLUT_WINDOW_WIDTH);
	int screenHeight = glutGet(GLUT_WINDOW_HEIGHT);
	int textWidth = glutBitmapLength(font, (const unsigned char*)string);

	// Adjust the x-coordinate to center the text
	int centerX = (screenWidth - textWidth) / 2;
	int newY = y; // Keep the y-coordinate as specified

	glRasterPos2f(centerX, newY);

	for (i = 0; i < len; i++) {
		glutBitmapCharacter(font, string[i]);
	}
}



void frontend_display()
{
	glColor3f(0.0,0.0,1.0);
	text_output(0, 500, "SORTING ALGORITHM VISUALIZER",GLUT_BITMAP_TIMES_ROMAN_24);
	glColor3f(1.0,0.0,0.0);
	text_output(0,450, "Press Enter to continue",GLUT_BITMAP_HELVETICA_18);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	if(k==0)
		frontend_display();
	
	glFlush();
}



void init()
{
	// Reseting the array prior to every sorting algorithm execution
    for (i = 0;i < MAX_ELE;i++)
    {
        a[i] = rand() % 100 + 1;
		printf("%d ",a[i]);
	}

	// Reseting all other values
	i=j=0;
	dirflag=0;
	count=1;
	flag=0;

    glMatrixMode(GL_PROJECTION_MATRIX);
    glLoadIdentity();
    gluOrtho2D(0, 1000, 0, 1000);
    glMatrixMode(GL_MATRIX_MODE);
}


//Keyboard Function
void keyboard (unsigned char key, int x, int y)
{
	if(key==13)  //carraige return (enter) 
		k=1;
	if (k==1 && sorting!=1)
	{
		switch (key)
		{
			case 27	 :	exit (0); // 27 is the ascii code for the ESC key
            case 's':	sorting = 1;
                        break;
            case 'r':	init();  //called to reinitialise the array
                        break;
            case 'c':	sort_count = (sort_count + 1) % SORT_NO;
                        break;
        }
	}
	if(k==1 && sorting==1)
        if (key == 'p')   //pause action
            sorting = 0;
}

int main(int argc, char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(1000,600);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Dynamic Sorting Algorithms Visualizer");
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	//glutTimerFunc(1000,makedelay,1);
	glutMainLoop();
}