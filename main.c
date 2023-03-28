#include<stdio.h>
#include<stdint.h>

uint8_t board [9] = { ' ',' ',' ',' ',' ',' ',' ',' ',' ' };
uint8_t array[2] = { 0,0 };

void drawBoard(uint8_t* board);
void updateBoard(uint8_t* board, uint8_t position, uint8_t value);
uint8_t getPlayerSymbol(uint8_t playerNumber, uint8_t* symbol);
void setPlayerConfig(uint8_t* configArray);
void loadAndUpdate(uint8_t playerNumber);
void getGameState(uint8_t* board, uint8_t* gameState);

void main()
{
	uint8_t turn = 1;
	uint8_t state=2;
	while (state==2)
	{
		if (turn == 0)
			turn = 1;
		else
			turn = 0;
		loadAndUpdate(turn);
		drawBoard(board);
		getGameState(board, &state);
	}
	if (state == 0)
	{
		printf("player number %d is the winner\n",turn+1);
	}
	else
	{
		printf("draw\n");
	}

}

void drawBoard(uint8_t* board)
{
	int i;
	for (i = 0; i < 9; i++)
	{
		printf(" %c ",board[i]);
		if (i < 9 && ((i + 1) % 3))
			printf("|");
		if (0 == (i + 1) % 3)
			printf("\n");
	}
	printf("\n");
}

void updateBoard(uint8_t* board, uint8_t position, uint8_t value)
{
	board[position] = value;
}

uint8_t getPlayerSymbol(uint8_t playerNumber, uint8_t* symbol)
{
	char x;
	if (playerNumber==0)
	{
		scanf(" %c", symbol);
		if (*symbol == 'x' || *symbol == 'X' || *symbol == 'o' || *symbol == 'O')
			return 0;
		else
			return 1;
	}
	else
	{
		scanf(" %c", &symbol[playerNumber]);
		if ((symbol[0] == (symbol[1] + ('x' - 'X'))) || (symbol[0] == (symbol[1] - ('x' - 'X'))) || symbol[0]==symbol[1])
		{
			return 1;
		}
		else
		{
			if (symbol[playerNumber] == 'x' || symbol[playerNumber] == 'X' || symbol[playerNumber] == 'o' || symbol[playerNumber] == 'O')
				return 0;
			else
				return 1;
		}
	}
}
void setPlayerConfig(uint8_t* configArray)
{
	int i;
	uint8_t error=1;
	for (i = 0; i < 2; i++)
	{
		while (error)
		{
			printf("enter the symbol of player %d\n", i + 1);
			error = getPlayerSymbol(i, configArray);
			if (error == 1)
			{
				printf("entered value is unapplicable\n");
			}
		}
		error = 1;
	}
}

void loadAndUpdate(uint8_t playerNumber)
{
	static int counter[9]={'/0','/0','/0','/0','/0','/0', '/0','/0', '/0'}, z = 0, x = 0;
	int pos=10,i=0,j;
	if (x == 0)
	{
		setPlayerConfig(array);
		x++;
	}
	while (pos < 0 || pos > 8)
	{
		printf("enter the position of player number %d\n", playerNumber + 1);
		scanf("%d",&pos);
		pos--;
		for (j = 0; j < 9; j++)
		{
			if (counter[j] == pos)
			{
				i = 1;
				break;
			}
		}
		
		if ( pos<0 || pos >8)
		{
			printf("undefined position\n");
			continue;
		}
		if (i != 0)
		{
			printf("This posision is used\n");
			pos = 10;
			i = 0;
		}
	}
	counter[z] = pos;
	z++;
	updateBoard(board, pos, array[playerNumber]);
}

void getGameState(uint8_t* board, uint8_t* gameState)
{
	int j = 0;
	int i;
	for (i = 0; i < 9; i++)
	{
		if (board[i] == ' ')
		{
			j = 1;
			break;
		}
	}
	if ((board[0] != ' ') && (board[0] == board[1]) && (board[1] == board[2]))
	{
		*gameState = 0;
	}
	else if ((board[3] != ' ') && (board[3] == board[4]) && (board[4] == board[5]))
	{
		*gameState = 0;
	}
	else if ((board[6] != ' ') && (board[6] == board[7]) && (board[7] == board[8]))
	{
		*gameState = 0;
	}
	else if ((board[0] != ' ') && (board[0] == board[3]) && (board[3] == board[6]))
	{
		*gameState = 0;
	}
	else if ((board[1] != ' ') && (board[1] == board[4]) && (board[4] == board[7]))
	{
		*gameState = 0;
	}
	else if ((board[2] != ' ') && (board[2] == board[5]) && (board[5] == board[8]))
	{
		*gameState = 0;
	}
	else if ((board[0] != ' ') && (board[0] == board[4]) && (board[4] == board[8]))
	{
		*gameState = 0;
	}
	else if ((board[2] != ' ') && (board[2] == board[4]) && (board[4] == board[6]))
	{
		*gameState = 0;
	}
	else if (j == 1)
	{
		*gameState = 2;
	}
	else
	{
		*gameState = 1;
	}
}
