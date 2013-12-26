#include<conio.h>
#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<dos.h>
# define MAX_LENGTH 2001


int cutter=0;

void showcon()
{
    system("cls");
    printf("\n\n    '-' :- Zoom in");
    printf("\n    '+' :- Zoom out");
    printf("\n    'w' :- Move window up");
    printf("\n    'a' :- Move window left");
    printf("\n    's' :- Move window down");
    printf("\n    'd' :- Move window right");
    printf("\npress any key...");
    getch();
}
int main1()
{
    char ch;
    system("cls");
    printf("\n\n  ASSIGNMENT BY:-                                  SUBMITTED TO:-\n");
    printf("  Rahul Bhojwani                                   Sir Ravindranath Choudhary\n");
    printf("  Rabindra Chhanch                                   \n");
    printf("  Radheshyam Verma                                   \n");
    printf("  Rahul Das\n");
    printf("\npress any key...");
    printf("\n\n");
    getch();
    system("cls");

    printf("\n 'p' :- Go to program");
    printf("\n 'c' :- Controls");
    printf("\n 'h' :- Help");
    printf("\n 'a' :- Go to home page");
    printf("\n 'q' :- Quit");
    printf("\npress any key...");
    fflush(stdin);
    ch=getch();
    if(ch=='p')
    {
	return(0);
    }
    else if(ch=='c')
    {
	showcon();
	return(1);
    }
    else if(ch=='h')
    {
	system("cls");
	printf("\n      This Program finds the edit distance between two strings");
	printf(".\n      Edit Distance in a measure of similarity between two strings\n\n");
	printf("\n  *To Use Program press 'p' and enter the two strings");
	  printf("\n  *Then if result does'nt fit window then move the window using 'w' 'a' 's' 'd'");
	  printf("\n  *if want to zoom in or zoom out the window use '+' and '-'");
	  printf("\npress any key...");
	  getch();
    }
    else if(ch=='a')
    {
        return(1);
    }
    if(ch=='q')
    {
        exit(0);
    }
    return 0;
}





float column_width=150,row_width=150;
int table_width=25,table_height=25;
float start_tablex=-(table_width*column_width)/2,start_tabley=(table_height*row_width)/2;
int arrow[MAX_LENGTH][MAX_LENGTH][3];
int color[MAX_LENGTH][MAX_LENGTH];


int arrow_color[MAX_LENGTH][MAX_LENGTH][3];



int ** edit_distance;
char str1[MAX_LENGTH];
char str2[MAX_LENGTH];


static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1000.0, 1000.0, -1000.0, 1000.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

static void display(void)
{

    int i,j;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(0,0,0);
    glBegin(GL_LINES);
        glVertex3f(start_tablex,start_tabley,0.0);
        glVertex3f(start_tablex+table_width*column_width,start_tabley,0.0);

        glVertex3f(start_tablex,start_tabley,0.0);
        glVertex3f(start_tablex,start_tabley+table_height*row_width,0.0);

        glVertex3f(start_tablex+table_width*column_width,start_tabley,0.0);
        glVertex3f(start_tablex+table_width*column_width,start_tabley+table_height*row_width,0.0);

        glVertex3f(start_tablex,start_tabley+table_height*row_width,0.0);
        glVertex3f(start_tablex+table_width*column_width,start_tabley+table_height*row_width,0.0);
    glEnd();

    //_sleep(300);

    for(i=1;i<table_width;i++)
    {
        glBegin(GL_LINES);
            glVertex3f(start_tablex+i*column_width,start_tabley,0.0);
            glVertex3f(start_tablex+i*column_width,start_tabley+table_height*row_width,0.0);
        glEnd();
        glRasterPos3f(start_tablex+(i+0.25)*column_width,start_tabley+(table_height+0.35)*row_width,0);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str2[i-1]);
    }

    for(i=1;i<table_height;i++)
    {
        glBegin(GL_LINES);
            glVertex3f(start_tablex,start_tabley+i*row_width,0.0);
            glVertex3f(start_tablex+table_width*column_width,start_tabley+i*row_width,0.0);
        glEnd();
        glRasterPos3f(start_tablex-0.35*column_width,start_tabley+(table_height-(i+1)+0.35)*row_width,0);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str1[i-1]);
    }

    int digits[5],no,index;



    for(i=0;i<table_height;i++)
    {
        for(j=0;j<table_width;j++)
        {
            if(color[table_height-i-1][j]==1)
                glColor3d(0,0,1);
            else
                glColor3d(0,0,0);
             glRasterPos3f(start_tablex+(j+0.35)*column_width,start_tabley+(i+0.35)*row_width,0);
                no=edit_distance[table_height-1-i][j];
                index=0;
                if(no==0)
                {
                    digits[0]=0;
                    index=1;
                }
                while(no!=0)
                {
                    digits[index]=no%10;
                    no/=10;
                    index++;
                }
       //         _sleep(30);
                while(index)
                {
                    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,digits[index-1]+48);
                    index--;
                }


             if(arrow[i][j][0]==1)
             {
                glColor3d(arrow_color[table_height-1-i][j][0],0,0);
                 glBegin(GL_LINES);
                    glVertex3f(start_tablex+(j-0.25)*column_width,start_tabley+(i+0.5)*row_width,0);
                    glVertex3f(start_tablex+(j+0.25)*column_width,start_tabley+(i+0.5)*row_width,0);

                    glVertex3f(start_tablex+(j+0.25)*column_width,start_tabley+(i+0.5)*row_width,0);
                    glVertex3f(start_tablex+(j+0.1)*column_width,start_tabley+(i+0.5)*row_width+(0.15)*column_width,0);

                    glVertex3f(start_tablex+(j+0.25)*column_width,start_tabley+(i+0.5)*row_width,0);
                    glVertex3f(start_tablex+(j+0.1)*column_width,start_tabley+(i+0.5)*row_width-(0.15)*column_width,0);
                 glEnd();

             }

             if(arrow[i][j][1]==1)
             {
                 glColor3d(arrow_color[table_height-1-i][j][1],0,0);
                glPushMatrix();
                    glTranslatef((start_tablex+(j-0.25)*column_width),(start_tabley+(i+1.25)*row_width),0);
                    glRotatef(315,0,0,1);
                    glTranslatef(-(start_tablex+(j-0.25)*column_width),-(start_tabley+(i+1.25)*row_width),0);

                glBegin(GL_LINES);
                    glVertex3f(start_tablex+(j-0.25)*column_width,start_tabley+(i+1.25)*row_width,0);
                    glVertex3f(start_tablex+(j+0.25)*column_width,start_tabley+(i+1.25)*row_width,0);

                    glVertex3f(start_tablex+(j+0.25)*column_width,start_tabley+(i+1.25)*row_width,0);
                    glVertex3f(start_tablex+(j+0.1)*column_width,start_tabley+(i+1.25)*row_width+(0.15)*column_width,0);

                    glVertex3f(start_tablex+(j+0.25)*column_width,start_tabley+(i+1.25)*row_width,0);
                    glVertex3f(start_tablex+(j+0.1)*column_width,start_tabley+(i+1.25)*row_width-(0.15)*column_width,0);
                 glEnd();
                 glPopMatrix();

             }

             if(arrow[i][j][2]==1)
             {
                glColor3d(arrow_color[table_height-1-i][j][2],0,0);
                 glBegin(GL_LINES);
                    glVertex3f(start_tablex+(j+0.5)*column_width,start_tabley+(i+1.25)*row_width,0);
                    glVertex3f(start_tablex+(j+0.5)*column_width,start_tabley+(i+0.75)*row_width,0);

                    glVertex3f(start_tablex+(j+0.5)*column_width,start_tabley+(i+0.75)*row_width,0);
                    glVertex3f(start_tablex+(j+0.5)*column_width+0.15*row_width,start_tabley+(i+0.90)*row_width,0);

                    glVertex3f(start_tablex+(j+0.5)*column_width,start_tabley+(i+0.75)*row_width,0);
                    glVertex3f(start_tablex+(j+0.5)*column_width-0.15*row_width,start_tabley+(i+0.90)*row_width,0);

                 glEnd();

             }
            //_sleep(3);
        }
    }
    glutSwapBuffers();
}


static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;

        case '+':
            column_width+=10;
            row_width+=10;
            break;

        case '-':
            if (column_width>80)
            {
                column_width-=10;
                row_width-=10;
            }
            break;
        case 'd':
            start_tablex+=10;
            break;
        case 'a':
            start_tablex-=10;
            break;
        case 's':
            start_tabley-=10;
            break;
        case 'w':
            start_tabley+=10;
            break;
    }

    glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}
/*
const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

*/
void init (void)
{
/* select clearing (background) color */
glClearColor (1.0, 1.0, 1.0, 0.0);
/* initialize viewing values */
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glOrtho(-1000.0, 1000.0, -1000.0, 1000.0, -1.0, 1.0);
}

//edit distance code;


struct wrap
{
	int i,j;
};


int min_edit_distance(int i,int j)
{
	int k,a,b,c,min;
	if(str1[i-1]==str2[j-1])
	{
        a=edit_distance[i][j-1] + 1;
        b=edit_distance[i-1][j] + 1;
        c=edit_distance[i-1][j-1];

        if(a<=b)
        {
            if(a<=c)
                min=a;
            else
                min=c;
        }
        else
        {
            if(b<=c)
                min=b;
            else
                min=c;
        }
        if(min==a)
        {
            arrow[table_height-1-i][j][0]=1;
        }
        if(min==b)
        {
            arrow[table_height-1-i][j][2]=1;
        }
        if(min==c)
        {
            arrow[table_height-1-i][j][1]=1;
        }

		return min;
	}
	else
	{
        a=edit_distance[i][j-1] + 1;
        b=edit_distance[i-1][j] + 1;
        c=edit_distance[i-1][j-1] +1;

        if(a<=b)
        {
            if(a<=c)
                min=a;
            else
                min=c;
        }
        else
        {
            if(b<=c)
                min=b;
            else
                min=c;
        }
        if(min==a)
        {
            arrow[table_height-1-i][j][0]=1;
        }
        if(min==b)
        {
            arrow[table_height-1-i][j][2]=1;
        }
        if(min==c)
        {
            arrow[table_height-1-i][j][1]=1;
        }

		return min;
	}
}

void tracking(int i,int j,wrap array[],int n)
{
    if(cutter)
    {
       return;
    }
    wrap w1;
	if(i==0 && j==0)
	{

        int k;
		for(k=0;k<n-1;k++)
		{

			color[array[k].i][array[k].j]=1;   // color of element

			if(array[k+1].i==array[k].i && array[k+1].j==array[k].j-1)
			{
                arrow_color[array[k].i][array[k].j][0]=1;
            }
            else if(array[k+1].i==array[k].i - 1 && array[k+1].j==array[k].j-1)
            {
                arrow_color[array[k].i][array[k].j][1]=1;
            }
            else if(array[k+1].i==array[k].i - 1 && array[k+1].j==array[k].j)
            {
                arrow_color[array[k].i][array[k].j][2]=1;
            }
		}
            if(array[k].i==1 && array[k].j==1)
			{
                arrow_color[array[k].i][array[k].j][1]=1;
            }
            else if(array[k].i==1 && array[k].j==0)
            {
                arrow_color[array[k].i][array[k].j][2]=1;
            }
            else if(array[k].i==0 && array[k].j==1)
            {
                arrow_color[array[k].i][array[k].j][0]=1;
            }
          //  printf("ag");
            cutter=1;
		return;
	}
	if(i==0 || j==0)
	{
		if(i==0)
		{
			w1.i=i;
			w1.j=j-1;
			array[n]=w1;
			tracking(i,j-1,array,n+1);
		}
		else if(j==0)
		{
			w1.i=i-1;
			w1.j=j;
			array[n]=w1;
			tracking(i-1,j,array,n+1);
		}
//		printf("%d %d %d\n",n,w1.i,w1.j);
		return;
	}

	if(edit_distance[i][j] == edit_distance[i-1][j-1] && str1[i-1]==str2[j-1])
	{
		w1.i=i-1;
		w1.j=j-1;
		array[n]=w1;
		tracking(i-1,j-1,array,n+1);
	}

	if(edit_distance[i][j] == (edit_distance[i][j-1]+1))
	{
		w1.i=i;
		w1.j=j-1;
		array[n]=w1;
		tracking(i,j-1,array,n+1);
	}

	if(edit_distance[i][j] == (edit_distance[i-1][j]+1))
	{
		w1.i=i-1;
		w1.j=j;
		array[n]=w1;
		tracking(i-1,j,array,n+1);
	}

	if(edit_distance[i][j] == (edit_distance[i-1][j-1]+1) && str1[i-1]!=str2[j-1])
	{
		w1.i=i-1;
		w1.j=j-1;
		array[n]=w1;
		tracking(i-1,j-1,array,n+1);
	}
//	printf("m");
}

int main(int argc, char *argv[])
{
	int i,j,k;

	while(main1());
	system("cls");
	printf("\nUse '+' to magnify And '-' To Zoom in");
	printf("\nUse 'w' 'a' 's' 'd' To scroll through table\nPress any key\n");
    getch();
    printf("\nEnter string 1\n");
    scanf("%s",&str1);
    printf("\nEnter string 2\n");
	scanf("%s",&str2);
	table_height=strlen(str1)+1;
	table_width=strlen(str2)+1;
	wrap array[table_height*table_width];
	edit_distance=(int **)malloc(sizeof(int *) * (table_height));
	if(edit_distance==NULL)
     {
         printf("not possivle\n");
         exit(0);

     }

	for(i=0;i<table_height;i++)
	{
		edit_distance[i]=(int *)malloc(sizeof(int)*(table_width));
		if(edit_distance[i]==NULL)
        {
         printf("not possivle\n");
         exit(0);

        }
	}

    for(i=0;i<table_height;i++)
    {
        for(j=0;j<table_width;j++)
        {
            for(k=0;k<3;k++)
             {
                    arrow[i][j][k]=0;
                    arrow_color[i][j][k]=0;
             }
        }
    }

	for(i=0;i<table_width;i++)
	{
		edit_distance[0][i]=i;
		arrow[table_height-1][i][0]=1;
		color[0][i]=0;
	}
	arrow[table_height-1][0][0]=0;
	for(i=0;i<table_height;i++)
	{
		edit_distance[i][0]=i;
		arrow[i][0][2]=1;
		color[i][0]=0;
	}
	arrow[table_height-1][0][2]=0;

	for(i=1;i<table_height;i++)
	{
		for(j=1;j<table_width;j++)
		{
		    color[i][j]=0;
			edit_distance[i][j] = min_edit_distance(i,j);
		}
	}
    color[0][0]=color[table_height-1][table_width-1]=1;
	tracking(table_height-1,table_width-1,array,0);

	i=table_height-1;
	j=table_width-1;
	if(edit_distance[i][j] == edit_distance[i-1][j-1] && str1[i-1]==str2[j-1])
	{
	    arrow_color[i][j][1]=1;
	}

	if(edit_distance[i][j] == (edit_distance[i][j-1]+1))
	{
		arrow_color[i][j][0]=1;
	}

	if(edit_distance[i][j] == (edit_distance[i-1][j]+1))
	{
        arrow_color[i][j][2]=1;
	}

	if(edit_distance[i][j] == (edit_distance[i-1][j-1]+1) && str1[i-1]!=str2[j-1])
	{
        arrow_color[i][j][1]=1;
	}
	start_tablex=-(table_width*column_width)/2;
    start_tabley=-(table_height*row_width)/2;
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("GLUT Shapes");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);
    init();

    glutMainLoop();

    return EXIT_SUCCESS;
}
