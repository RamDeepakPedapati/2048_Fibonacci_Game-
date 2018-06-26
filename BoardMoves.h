#include<math.h>

//to check whether the move performed is valid or not........

int isValidMove(char move)
{
	if (move == 'W' || move == 'A' || move == 'S' || move == 'D' || move == 'Z')
		return 1;
	else
		return 0;
}


//checks whether two numbers are fibonnacii or not.............................
//returns 1 if they are adjacent fibonnacii...................................

int isAdjacentFibonacci(int first, int second)
{
	int diff = abs(first - second);
	if ((first == 1 && second == 0) || (first == 0 && second == 1))
		return 1;
	else if ((diff <= first && diff <= second)&&((first!=second)||(first==1 || second==1)))
		return 1;
	else
		return 0;
}


//checks whether there is an empty tile or not...................................

int isEmptyTileExist(Board *game)
{
	for (int iter = 0; iter < game->boardSize; iter++)
		for (int iter1 = 0; iter1 < game->boardSize; iter1++)
			if (game->table[iter][iter1] == 0)
				return 1;
	return 0;
}


//generate 1's at the random positon........................................

void generateRamdom(Board *game)
{
	int temp1 = rand() % (game->boardSize), temp2 = rand() % (game->boardSize);
	while (game->table[temp1][temp2] != 0)
	{
		temp1 = rand()%game->boardSize;
		temp2 = rand()%game->boardSize;
	}
	game->table[temp1][temp2] = 1;
}

//increasing the stepcount ......................................

void increaseGameCount(Board *game)
{
	game->stepCount=game->stepCount+1;
}


//checks all the game over conditions like whether the game is won or
//game is over with no further moves and no adjacent numberers

int isGameOver(Board *game)
{
	for (int iter1 = 0; iter1 < game->boardSize; iter1++)
	{
		for (int iter2 = 0; iter2 < game->boardSize; iter2++)
		{
			if ((game->table[iter1][iter2] == 2178309 && game->boardSize == 4) || (game->table[iter1][iter2] == 13 && game->boardSize == 2))
			{
				game->gameOver = 1;
				return 1;
			}
		}
	}
	for (int iter1 = 0; iter1 < game->boardSize; iter1++)
	{
		for (int iter2 = 0; iter2 < game->boardSize-1; iter2++)
		{
			if (isAdjacentFibonacci(game->table[iter1][iter2], game->table[iter1][iter2 + 1]))
				return 0;
		}
	}
	for (int iter1 = 0; iter1 < game->boardSize; iter1++)
	{
		for (int iter2 = 0; iter2 < game->boardSize - 1; iter2++)
		{
			if (isAdjacentFibonacci(game->table[iter2][iter1], game->table[iter2+1][iter1]))
				return 0;
		}
	}
	
	return 1;
}


//performs up move by adding the adjacent fibonacci...........................

int performUpMove(Board *game)
{
	int temp1, temp2, temp3,count=0;
	for (int iter1 = 0; iter1 < game->boardSize; iter1++)
	{
		for (int iter2 = 0; iter2 < game->boardSize - 1; iter2++)
		{
			temp1 = iter2;
			while (temp1<game->boardSize && game->table[temp1][iter1] == 0)
				temp1++;
			temp2 = temp1 + 1;
			while (temp2<game->boardSize && game->table[temp2][iter1] == 0)
				temp2++;
			if (temp2<game->boardSize && isAdjacentFibonacci(game->table[temp1][iter1], game->table[temp2][iter1]))
			{
				game->table[temp1][iter1] = game->table[temp1][iter1] + game->table[temp2][iter1];
				game->table[temp2][iter1] = 0;
				count++;
			}
			iter2 = temp1;
		}
	}

	for (int iter1 = 0; iter1 < game->boardSize; iter1++)
	{
		temp1 = 0;
		while (temp1 < game->boardSize)
		{
			while (temp1<game->boardSize && game->table[temp1][iter1] != 0)
				temp1++;
			temp2 = temp1 + 1;
			while (temp2<game->boardSize && game->table[temp2][iter1] == 0)
				temp2++;
			if (temp1 < game->boardSize && temp2 < game->boardSize)
			{
				temp3 = game->table[temp1][iter1];
				game->table[temp1][iter1] = game->table[temp2][iter1];
				game->table[temp2][iter1] = temp3;
				count++;
			}
			temp1++;
		}
	}
	if (count > 0)
		return 1;
	else
		return 0;
	
}


//performs down move by adding the adjacent fibonacci...........................

int performDownMove(Board *game)
{
	int temp1, temp2, temp3, count = 0;
	for (int iter1 = game->boardSize - 1; iter1 >= 0; iter1--)
	{
		for (int iter2 = game->boardSize - 1; iter2 >= 0; iter2--)
		{
			temp1 = iter2;
			while (temp1 >= 0 && game->table[temp1][iter1] == 0)
				temp1--;
			temp2 = temp1 - 1;
			while (temp2 >= 0 && game->table[temp2][iter1] == 0)
				temp2--;
			if (temp2 >= 0 && isAdjacentFibonacci(game->table[temp1][iter1], game->table[temp2][iter1]))
			{
				game->table[temp1][iter1] = game->table[temp1][iter1] + game->table[temp2][iter1];
				game->table[temp2][iter1] = 0;
				count++;
			}
			iter2 = temp1;
		}
	}

	for (int iter1 = game->boardSize - 1; iter1 >= 0; iter1--)
	{
		temp1 = game->boardSize - 1;
		while (temp1 >= 0)
		{
			while (temp1 >= 0 && game->table[temp1][iter1] != 0)
				temp1--;
			temp2 = temp1 - 1;
			while (temp2 >= 0 && game->table[temp2][iter1] == 0)
				temp2--;
			if (temp1 >= 0 && temp2 >= 0)
			{
				temp3 = game->table[temp1][iter1];
				game->table[temp1][iter1] = game->table[temp2][iter1];
				game->table[temp2][iter1] = temp3;
				count++;
			}
			temp1--;
		}
	}
	if (count > 0)
		return 1;
	else
		return 0;

}



//performs left move by adding the adjacent fibonacci...........................

int performLeftMove(Board *game)
{
	int temp1, temp2, temp3, count = 0;
	for (int iter1 = 0; iter1 < game->boardSize; iter1++)
	{
		for (int iter2 = 0; iter2 < game->boardSize - 1; iter2++)
		{
			temp1 = iter2;
			while (temp1<game->boardSize && game->table[iter1][temp1] == 0)
				temp1++;
			temp2 = temp1+1;
			while (temp2<game->boardSize && game->table[iter1][temp2] == 0)
				temp2++; 
			if (temp2<game->boardSize && isAdjacentFibonacci(game->table[iter1][temp1], game->table[iter1][temp2]))
			{
				game->table[iter1][temp1] = game->table[iter1][temp1]+game->table[iter1][temp2];
				game->table[iter1][temp2] = 0;
				count++;
			}
			iter2 = temp1;
		}
	}
	
	for (int iter1 = 0; iter1 < game->boardSize; iter1++)
	{
		temp1 = 0;
		while (temp1 < game->boardSize)
		{
			while (temp1<game->boardSize && game->table[iter1][temp1] != 0)
				temp1++;
			temp2 = temp1 + 1;
			while (temp2<game->boardSize && game->table[iter1][temp2] == 0)
				temp2++;
			if (temp1 < game->boardSize && temp2 < game->boardSize)
			{
				temp3=game->table[iter1][temp1];
				game->table[iter1][temp1] = game->table[iter1][temp2];
				game->table[iter1][temp2] = temp3;
				count++;
			}
			temp1++;
		}
	}
	if (count > 0)
		return 1;
	else
		return 0;
	
}


//performs right move by adding the adjacent fibonaccis...........................

int performRightMove(Board *game)
{

	int temp1, temp2, temp3, count = 0;
	for (int iter1 = game->boardSize - 1; iter1 >= 0; iter1--)
	{
		for (int iter2 = game->boardSize - 1; iter2 >= 0; iter2--)
		{
			temp1 = iter2;
			while (temp1 >= 0 && game->table[iter1][temp1] == 0)
				temp1--;
			temp2 = temp1-1;
			while (temp2 >= 0 && game->table[iter1][temp2] == 0)
				temp2--;
			if (temp2>=0 && isAdjacentFibonacci(game->table[iter1][temp1], game->table[iter1][temp2]))
			{
				game->table[iter1][temp1] = game->table[iter1][temp1] + game->table[iter1][temp2];
				game->table[iter1][temp2] = 0;
				count++;
			}
			iter2 = temp1;
		}
	}

	for (int iter1 = game->boardSize - 1; iter1 >= 0; iter1--)
	{
		temp1 = game->boardSize-1;
		while (temp1 >= 0)
		{
			while (temp1 >= 0 && game->table[iter1][temp1] != 0)
				temp1--;
			temp2 = temp1 - 1;
			while (temp2 >= 0 && game->table[iter1][temp2] == 0)
				temp2--;
			if (temp1 >= 0 && temp2 >= 0)
			{
				temp3 = game->table[iter1][temp1];
				game->table[iter1][temp1] = game->table[iter1][temp2];
				game->table[iter1][temp2] = temp3;
				count++;
			}
			temp1--;
		}
	}
	if (count > 0)
		return 1;
	else
		return 0;
	
}


//resumes the game and stores the present board info into the files...............................

void resumeInfo(Board *game)
{
	FILE *fp,*fp1;
	char outputFilename[] = "out.list";
	char outputFile1[] = "out1.list";

	fp = fopen(outputFilename, "w");
	fp1 = fopen(outputFile1, "w");
	for (int iter1 = 0; iter1 < game->boardSize; iter1++)
	{
		for (int iter2 = 0; iter2 < game->boardSize;iter2++)
			fprintf(fp, "%d\n",game->table[iter1][iter2]);
	}
	fprintf(fp1, "%s %d %d %d %d", game->userName, game->gameOver, game->stepCount, game->resume,game->boardSize);
	fclose(fp);
	fclose(fp1);

}

//playing the move like up down ,resuming the game etc is done here................................

void playMove(Board *game)
{
	char move;
	int count = 0;
	printf("Enter a Move:\n  [W]-Up     \t[A]-Left    \t[S]-Down    \t[D]-Right    \t[Z]-Resume\n");
	scanf("\n%c", &move);
	if (isValidMove(move))
	{
		if (move == 'W')
			count=performUpMove(game);
		else if (move == 'A')
			count=performLeftMove(game);
		else if (move == 'S')
			count=performDownMove(game);
		else if (move == 'D')
			count=performRightMove(game);
		else if (move == 'Z')
		{
			resumeInfo(game);
			game->resume = 1;
			return;
		}
		if (count > 0)
		{
			increaseGameCount(game);
			resumeInfo(game);
		}
		if (isEmptyTileExist(game) && count>0)
			generateRamdom(game);
	}
}