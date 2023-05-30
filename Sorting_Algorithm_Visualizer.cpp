#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<GL\glut.h>

#define SORT_NO  2 //the number of sorting algorithms 
#define MAX_ELE  50
#define SPEED  800 //Speed of sorting

int a[MAX_ELE];
int k = 0, sorting = 0, sort_count = 0, swapflag = 0;
int i, j, flag, count, dirflag;

const char* sort_algo_string[] = { "Bubble Sort" ,"Insertion Sort"};  //array containing the sorting algorithms 


void text_output(int x, int y, const char* string, void* font)
{
	int len, i;
	len = (int)strlen(string);

	glRasterPos2f(x,y);

	for (i = 0; i < len; i++) {
		glutBitmapCharacter(font, string[i]);
	}
}


int notsorted() {
	int q;
	for(q=0;q<MAX_ELE-1;q++)
	{
		if(a[q]>a[q+1])
			return 1;
	}
	return 0;
}


//Bubble Sort Code
void bubblesort()
{
	int temp;
	while(notsorted())
	{
		while(j<MAX_ELE-1)
		{
			if(a[j]>a[j+1])
			{
				swapflag=1;
				temp=a[j];
				a[j]=a[j+1];
				a[j+1]=temp;

				goto A;
			}
			j++;
			if (j == MAX_ELE - 1)
				j = 0;
		}
	}
	sorting=0;
	A: printf("");
}


// Insertion Sort
void insertionsort()
{
    int i = 0;
    int j = 0;
	int temp;
	
	while (i < MAX_ELE)
    {
        if (flag == 0)
        {
            j = i;
            flag = 1;
        }
        while (j < MAX_ELE - 1)
        {
            if (a[j] > a[j + 1])
            {
                swapflag = 1;
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;

                goto A;
            }

            j++;
            if (j == MAX_ELE - 1)
            {
                flag = 0;
            }
        }

        i++;
    }

    sorting = 0;
    A:
    i = j = 0;
}


void frontend_display()
{
	glColor3f(0.0, 0.0, 1.0);
	text_output(330, 600, "SORTING ALGORITHM VISUALIZER", GLUT_BITMAP_TIMES_ROMAN_24);
	glColor3f(1.0, 0.0, 0.0);
	text_output(420, 535, "Press Enter to continue", GLUT_BITMAP_HELVETICA_18);
	
}


void second_page_display()
{
	glColor3f(0, 0, 1);
	text_output(300, 750, "SORTING ALGORITHM VISUALIZER", GLUT_BITMAP_TIMES_ROMAN_24);
	
	// other text small font
	text_output(10, 700, "This program sorts a random set of numbers(represented as bars of different heights) in ascending order  ", GLUT_BITMAP_9_BY_15);
    
	if (sorting == 0)	// if not sorting display menu
	{
		text_output(10, 660, "MENU :", GLUT_BITMAP_9_BY_15);
		
		text_output(10, 630, "Press s to SORT", GLUT_BITMAP_9_BY_15);
		
		text_output(10, 600, "Press c to SELECT the sort algorithm", GLUT_BITMAP_9_BY_15);
		
		text_output(10, 570, "Press r to RANDOMISE", GLUT_BITMAP_9_BY_15);
		
		text_output(10, 540, "Esc to QUIT", GLUT_BITMAP_9_BY_15);
		
		text_output(10, 510, "Selected sort: ", GLUT_BITMAP_9_BY_15);
		
		text_output(150, 510, *(sort_algo_string + sort_count), GLUT_BITMAP_9_BY_15);
	}
	else if (sorting == 1)	// while sorting
	{
		glColor3f(0.5, 0.5, 0.5);
		text_output(10, 630, "Sorting in progress...", GLUT_BITMAP_9_BY_15);
		text_output(10, 600, "Press p to PAUSE", GLUT_BITMAP_9_BY_15);
		glColor3f(0.0, 0.0, 0.0);
	}
}


void int_str(int rad, char r[])
{
	itoa(rad, r, 10);
}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	if (k == 0)
		frontend_display();
	else {
		second_page_display();
		char text[10];

		for (i = 0;i < MAX_ELE;i++)
		{
			glColor3f(1, 0, 0);
			glBegin(GL_LINE_LOOP);
			glVertex2f(10 + (1000 / (MAX_ELE + 1)) * i, 50);
			glVertex2f(10 + (1000 / (MAX_ELE + 1)) * (i + 1), 50);
			glVertex2f(10 + (1000 / (MAX_ELE + 1)) * (i + 1), 50 + a[i] * 4);
			glVertex2f(10 + (1000 / (MAX_ELE + 1)) * i, 50 + a[i] * 4);
			glEnd();

			int_str(a[i], text);
			
			glColor3f(0, 0, 0);
			text_output(12 + (700 / (MAX_ELE + 1)) * i, 35, text, GLUT_BITMAP_TIMES_ROMAN_10);
		}

		if (swapflag || sorting == 0)
		{
			glColor3f(0, 0, 1);
			glBegin(GL_POLYGON);
			glVertex2f(10 + (1000 / (MAX_ELE + 1)) * j, 50);
			glVertex2f(10 + (1000 / (MAX_ELE + 1)) * (j + 1), 50);
			glVertex2f(10 + (1000 / (MAX_ELE + 1)) * (j + 1), 50 + a[j] * 4);
			glVertex2f(10 + (1000 / (MAX_ELE + 1)) * j, 50 + a[j] * 4);
			glEnd();
			swapflag = 0;
		}
	}

	glFlush();
}


void init()
{
	// Reseting the array prior to every sorting algorithm execution
	for (i = 0;i < MAX_ELE;i++)
	{
		a[i] = rand() % 100 + 1;  //setting elements of the array randomly 
		printf("%d ", a[i]);
	}
	// Reseting all other values
	i = j = 0;
	dirflag = 0;
	count = 1;
	flag = 0;

	glMatrixMode(GL_PROJECTION_MATRIX);
	glLoadIdentity();
	gluOrtho2D(0, 1000, 0, 1000);
	glMatrixMode(GL_MATRIX_MODE);
}


//Keyboard Function
void keyboard(unsigned char key, int x, int y)
{
	if (key == 13)  //carraige return (enter) 
		k = 1;
	if (k == 1 && sorting != 1)
	{
		switch (key)
		{
		case 27:
			exit(0); // 27 is the ascii code for the ESC key
		case 's':
			sorting = 1;
			break;
		case 'r':
			init();  //called to reinitialise the array
			break;
		case 'c':
			sort_count = (sort_count + 1) % SORT_NO;
			break;
		}
	}
	if (k == 1 && sorting == 1)
		if (key == 'p')   //pause action
			sorting = 0;
}


void makedelay(int)
{
	if(sorting)
	{
		switch(sort_count)
		{
		case 0:	bubblesort();
			    break;
		case 1: insertionsort();
			    break;

		}
	}
	glutPostRedisplay();
	glutTimerFunc(SPEED/MAX_ELE,makedelay,1);
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1000, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Dynamic Sorting Algorithms Visualizer");
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(1000, makedelay, 1);
	glutMainLoop();
}