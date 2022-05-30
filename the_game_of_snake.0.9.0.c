#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <unistd.h>

/*
				Yusuf Zeki Çiftçi - 210601058
				Kerem Levent - 210601039
				the_game_of_snake.1.0.0
*/
    struct ID
{
    char name[50];
    long int score;
};


/* YAPILMAMIÞ GEREKSÝNÝMLER
 1- Girilen oyunculardan kazananýn skoru yazdýrýlsýn 
2- Rekor tutulsun
3- Yýlanýn kuyruðuna çarpmasý saðlansýn
*/

int area[80][23]={0};
int feedx,feedy;
int snakeLen;
int tailx[100];
int taily[100];

void gotoxy(short x, short y) {
 HANDLE hConsoleOutput;
 COORD Cursor_Pos = {x-1, y-1};

 hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
 SetConsoleCursorPosition(hConsoleOutput, Cursor_Pos);
}

void window(int x1 ,int y1, int x2, int y2,int type)
{
	int i;
	for(i=x1;i<=x2;i++)
	{
		area[i][y1]=type;
		area[i][y2]=type;
	}
	
	for(i=y1;i<=y2;i++)
	{
		area[x1][i]=type;
		area[x2][i]=type;
	}

}

void draw()
{
	int x,y;
	for(x=0;x<80;x++)
	{
		for(y=1;y<24;y++)
		{
			gotoxy(x+1,y+1);
			if(area[x][y]==2)
			{
				printf("%c",219);
			}
		}
	}
}

void randomAss()
{
    srand(time(NULL));
    feedx=2+rand()%78;
    feedy=3+rand()%21;
}

void main()
{
    system("color 30");
    
	int x,j;
    int playerTurn=0;
    int tryAgainCtrl;
    int numofplayers;
	struct ID player[numofplayers];
	
	FILE *pdosya;
    pdosya=fopen("dosya.txt","w");
    
	fprintf(pdosya,"***** YILAN OYUNU *****\n\n");
    printf("Please enter the number of players ..\n");
    scanf("%d",&numofplayers);

		system("CLS");
           
        for(x=0;x<numofplayers;x++)
        {
            snakeLen=3;
            printf("Please enter the name of %d. player..\n",(x+1));
            scanf("%s",&(player[x].name));
            player[x].score=0;
        system("CLS");
        
    system("CLS");

    printf("In game use the 'UP ARROW KEY' for UP, 'LEFT ARROW KEY' for LEFT\n, 'DOWN ARROW KEY' for DOWN and 'RIGHT ARROW KEY' for RIGHT\n");
    sleep(4);

    system("CLS");

    randomAss();
	window(0,1,79,23,2);
	draw();

	int sx=40,sy=12;
	unsigned char button;
	int dx=0,dy=0;
	
	printf("\n* * * * * * * * * * *    S  N  A  K  E       G  A  M  E    * * * * * * * * * * * ");

    do
    {
        if(kbhit())
        {
            button=getch();
            if(button==224)
            {

                button=getch();
                switch(button)
                {
                    case 72: dx=0,dy=-1;
                    break;
                    case 80: dx=0,dy=1;
                    break;
                    case 77: dx=1,dy=0;
                    break;
                    case 75: dx=-1,dy=0;
                    break;
                }
            }
        }
        sx=sx+dx;
        sy=sy+dy;
        
        if(sx==79 || sx==1)
        {
            printf("\n\nGAME OVER\nPLS WAIT..");
            playerTurn++;
            if(playerTurn==numofplayers)
            {
            	scanf("%d",&tryAgainCtrl);
        	}
			break;
        }

        if(sy==2 || sy==24)
        {
            printf("\n\nGAME OVER\nPLS WAIT..");
            playerTurn++;
        
		    if(playerTurn==numofplayers)
            {
            	scanf("%d",&tryAgainCtrl);
        	}
        	break;
		}
		tailx[0]=sx;
		taily[0]=sy;

        if(sx==feedx && sy==feedy)
        {
            randomAss();
            snakeLen++;
            player[playerTurn].score+=100;
            gotoxy(81,25);
            
            int z;
            for(z=0;z<numofplayers;z++)
        	{
			printf("\n%s SCORE : %d",player[z].name,player[z].score);
    		}
		}
				
        gotoxy(feedx,feedy);
        printf("%c",254);

        gotoxy(sx,sy);
        printf("%c",254);

        int i;
        for(i=0;i<snakeLen;i++)
        {
            gotoxy(tailx[i],taily[i]);
            printf("%c",254);
        }

        usleep(85000);
        gotoxy(sx,sy);
        printf(" ");
		
         for(i=0;i<snakeLen;i++)
        {
            gotoxy(tailx[i],taily[i]);
            printf(" ");
        }
          for(i=snakeLen;i>0;i--)
        {
            tailx[i]=tailx[i-1];
            taily[i]=taily[i-1];
        }
    }while(1);
    
    sleep(2);
    system("CLS");
   }
     for(j=0;j<numofplayers;j++)
    {
    	fprintf(pdosya,"%d. Oyuncu : [%s] - %d \n",j+1,(player[j].name),(player[j].score));
	}
	fclose(pdosya);
		gotoxy(1,82);
		
}
