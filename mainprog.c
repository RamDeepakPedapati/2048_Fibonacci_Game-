#define _CRT_SECURE_NO_WARNINGS

										/*.......Gamee of fibonnaci 2048............*/



#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

#include "BoardUtils.h"	//contains all the board information like structures for board,intilization of board etc

#include "BoardMoves.h"	//conatins actions like movements etc


//to take the input from the uer to select board size...........................................

int takeInput()
{
	int boardSize;
	printf("Play Game:\n\t[2] - 2*2\t4 - 4*4\n");
	scanf("%d", &boardSize);
	while (boardSize != 2 && boardSize != 4)
	{
		system("cls");
		printf("please select one:\n1-2*2\n2-4*4\n");
		scanf("%3d", &boardSize);
	}
	return boardSize;
}


//to take the input from the user.....................

char *takeUser()
{
	/*char waste;
	scanf("%c",&waste);*/
	fflush(stdin);

	char *userName = (char*)malloc(sizeof(char) * 20);
	printf("Enter User Name:\n");
	gets(userName);
	return userName;
}




//playing the game is written here........................

void Game(Board *game)
{
	drawBoardOnScreen(game);
	while (!isGameOver(game) && (!game->resume))
	{
		playMove(game);
		clearScreen();
		drawBoardOnScreen(game);
	}
	if (game->resume)
		printf("Game Resumed\n");
	else if (game->gameOver)
	{
		printf("Game won with stepCount-%d\n", game->stepCount);
		updateLeaderBoard(game);
	}
	else
		printf("Game Over with step count %d\n", game->stepCount);
}

int main()
{
	int select;
	
	while (1)
	{
		printf("\t[1]-Play Game\t[2]-Replay Last Saved Game\t[3]-View LeaderBoard\t[4]-Exit\n");
		scanf("%d", &select);

		if (select == 1)
		{
			Board *game = createBoard(takeInput(), takeUser());
			clearScreen();
			intializeBoard(game);
			Game(game);
		}
		else if (select == 2)
		{
			Board *game = loadSavedGame();
			printf("\nWelcome %s", game->userName);
			Game(game);
		}
		else if (select == 3)
		{
			displayLeaderBoard();
		}
		else if (select == 4)
			break;
	}
	
	
	return 0;
}