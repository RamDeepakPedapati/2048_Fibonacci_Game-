#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
typedef struct Board1 {
	//Stores the Actual table of all values ,which are being displayed
	int **table;

	int boardSize;//either 2 or 4 representing 2*2 or 4*4 respectively

	char *userName;
	int stepCount;
	int gameOver;
	int resume;
}Board;


// structure to store the leaderboard................

typedef struct leaderBoard1{
	int SNo;
	char *date;
	char *userName;
	char *BoardType;
	int stepcount;

}leaderBoard;


//clears the screen......................

void clearScreen(){
	system("cls");
}


//printing the board on to console.....................................

void drawBoardOnScreen(Board *game)
{
	printf("\n\n\n-------------------------------------------------------------------------\n");
		for (int iter1 = 0; iter1 < game->boardSize; iter1++)
		{
			for (int iter2 = 0; iter2 < game->boardSize; iter2++)
				printf("%3d\t", game->table[iter1][iter2]);
			printf("\n");
		}
	printf("\nstepcount-%d", game->stepCount);
	printf("\n------------------------------------------------------------------------\n\n");
	
}

//returns the date in the format of dd-mm-yyyy

char *getDate()
{
	SYSTEMTIME t;
	int year;
	GetSystemTime(&t);
	char *date = (char*)malloc(sizeof(char) * 11);
	date[1] = (t.wDay % 10) + 48;
	date[0] = (t.wDay / 10) + 48;
	date[2] = '-';
	date[4] = (t.wMonth % 10) + 48;
	date[3] = (t.wMonth / 10) + 48;
	date[5] = '-';
	date[9] = (t.wYear % 10) + 48;
	year = t.wYear / 10;
	date[8] = (year % 10) + 48;
	year = year / 10;
	date[7] = (year % 10) + 48;
	year = year / 10;
	date[6] = (year % 10) + 48;
	date[10] = '\0';
	return date;

}


//returns the size of the board as string.................

char * getSize(Board *game)
{
	char *size = (char*)malloc(sizeof(char) * 4);
	size[0] = game->boardSize + 48;
	size[1] = 'x';
	size[2] = game->boardSize + 48;
	size[3] = '\0';
	return size;
}


//returns the no of lines count in the file specifie by its path............... 

int noOfLine(char *path)
{
	FILE *fp;
	int count=0;
	fp = fopen(path, "r");
	char c;
	c = fgetc(fp);
	while (c != EOF)
	{
		if (c == '\n')
			count++;
		c = fgetc(fp);
	}
	return fp;
}


//returns type of the board......................

char *getType(int size)
{
	if (size == 2)
		return "2x2";
	else if (size == 4)
		return "4x4";
	else
		return NULL;
}


//updation of the leaderboard is done here .......
//after the completion of the game................

void updateLeaderBoard(Board *game)
{
	leaderBoard *sl= (leaderBoard*)malloc(sizeof(leaderBoard)*20);
	FILE *fp,fp1;
	char *stringhead = (char*)malloc(sizeof(char));
	char *date = (char*)malloc(sizeof(char) * 11);
	char *userName = (char *)malloc(sizeof(char) * 20);
	char *type = (char *)malloc(sizeof(char) * 4);
	int sno,k=0;
	int stepcount;
	
	fp = fopen("leaderBoard.list", "r");

	while (fscanf(fp, "%d %s %s %s %d", &sno,date,userName,type, &stepcount) == 5)
	{
		sl[k].SNo = sno;
		sl[k].date = (char*)malloc(sizeof(char) * 20);
		strcpy(sl[k].date, date);
		sl[k].userName = (char*)malloc(sizeof(char) * 20);
		strcpy(sl[k].userName, userName);
		sl[k].BoardType = (char*)malloc(sizeof(char) * 20);
		strcpy(sl[k].BoardType,type);
		sl[k].stepcount = stepcount;
		k++;
	}
	fclose(fp);

	fp = fopen("leaderBoard.list", "w");
	int count = 1,placed=0;

	for (int iter = 0; iter < 20 && iter<k; )
	{
		if ((sl[iter].stepcount >= game->stepCount) && placed==0)
		{
			placed = 1;
			fprintf(fp,"%d %s %s %s %d\n", count,getDate(),game->userName,getType(game->boardSize),game->stepCount);
		}
		else 
		{
			fprintf(fp,"%d %s %s %s %d\n", count, sl[iter].date, sl[iter].userName, sl[iter].BoardType, sl[iter].stepcount);
			iter++;
		}
		count++;
	}
	fclose(fp);
	free(stringhead);
	free(date);
	free(userName);
	free(type);

}


// printing the learderboard information on to the console..........................

void displayLeaderBoard()
{
	FILE *fp;
	int sno;
	char *userName=(char*)malloc(sizeof(char)*20);
	char *size = (char*)malloc(sizeof(char) * 20);
	char *date = (char*)malloc(sizeof(char) * 11);
	int count;
	fp = fopen("leaderBoard.list", "r");
	printf("S.No\t\tDate\t\tName\t\tBoardSize\tStep Count\n");
	while (fscanf(fp, "%d %s %s %s %d",&sno,date,userName,size, &count) == 5)
	{
		printf("%-4d\t\t%10s\t%-10s\t%-3s\t\t%-2d\n", sno,date, userName, size, count);
	}
	
}


//creation of the board is done here like allocating mermory etc...

Board * createBoard(int boardSize,char *userName)
{
	if (boardSize == 2 || boardSize == 4)
	{

		//board creation and intialization..........................
		Board *newlyCreatedBoard = (Board *)malloc(sizeof(Board));
		newlyCreatedBoard->boardSize = boardSize;
		int **boardsample = (int **)calloc(boardSize, sizeof(int));
		for (int iter = 0; iter < boardSize; iter++)
		{
			boardsample[iter] = (int*)calloc(boardSize,sizeof(int));
		}
		newlyCreatedBoard->table = boardsample;
		newlyCreatedBoard->userName = userName;
		newlyCreatedBoard->stepCount = 0;
		newlyCreatedBoard->gameOver = 0;
		newlyCreatedBoard->resume = 0;
		return newlyCreatedBoard;
	}

}


//intialization of board is done here like generating two random 1's etc is done here............

void intializeBoard(Board *game)
{
	//generating two random initial positions
	int generatedCount = 0, temp1, temp2;
	while (generatedCount < 2)
	{
		temp1 = rand() % game->boardSize, temp2 = rand() %game->boardSize;
		if (game->table[temp1][temp2] == 0)
		{
			game->table[temp1][temp2] = 1;
			generatedCount++;
		}
	}

}


//loading the resumed and saved game is done here........................

Board * loadSavedGame()
{
	Board *resumedBoard = (Board *)malloc(sizeof(Board));
	FILE *fp, *fp1;
	char userName[20];/* One extra for nul char. */
	int boardSize;
	int gameOver;
	int resume;
	int stepCount;
	fp = fopen("out1.list","r");

	if (fp == NULL) {
		fprintf(stderr, "Can't open input file out1.list!\n");
		exit(1);
	}
	int a=fscanf(fp, "%s %d %d %d %d",userName,&gameOver,&stepCount,&resume,&boardSize);
	resumedBoard->boardSize = boardSize;
	int **boardsample = (int **)calloc(boardSize, sizeof(int));
	for (int iter = 0; iter < boardSize; iter++)
	{
		boardsample[iter] = (int*)calloc(boardSize, sizeof(int));
	}
	resumedBoard->table = boardsample;
	resumedBoard->userName = (char*)malloc(sizeof(char) * 20);
	strcpy(resumedBoard->userName, userName);
	resumedBoard->stepCount = stepCount;
	resumedBoard->gameOver = gameOver;
	resumedBoard->resume = resume;
	int k;

	fp1 = fopen("out.list", "r");
	for (int iter1 = 0; iter1 < resumedBoard->boardSize; iter1++)
	{
		for (int iter2 = 0; iter2 < resumedBoard->boardSize; iter2++)
			 k = fscanf(fp1,"%d\n",&resumedBoard->table[iter1][iter2]);
	}
	fclose(fp);
	fclose(fp1);
	return resumedBoard;
}