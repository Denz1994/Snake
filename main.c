#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>

#define ROWS 10
#define COLS 30
#define TOP_BORDER_LENGTH 59
#define TRUE 1
#define FALSE 0

// Controls
#define MOVE_UP 'w'
#define MOVE_DOWN 's'
#define MOVE_RIGHT 'd'
#define MOVE_LEFT 'a'
#define QUIT 'q'

// Assumes index [0] is head and [length] is tail
int snake_body[50][2] = {{0, 0}};
int food_position[2] = {0, 0};
int length = 0;

void print_board()
{
	printf("\n");
	// Top Border
	for (int i = 0; i < TOP_BORDER_LENGTH; i++)
	{
		printf("-");
	}

	printf("\n");
	// Left and Right Borders
	for (int y = 0; y < ROWS; y++)
	{
		printf("| ");
		for (int x = 0; x < COLS - 2; x++)
		{
			// Here we represent position. Either the position is filled or it is not.
			if (x == snake_body[0][0] && y == snake_body[0][1])
			{
				printf("x ");
			}
			else if (x == food_position[0] && y == food_position[1])
			{
				printf("+ ");
			}
			else
			{
				int skip_space = FALSE;
				for (int i = 0; i <= length; i++)
				{
					if (snake_body[i][0] == x && snake_body[i][1] == y)
					{
						printf("o ");
						skip_space = TRUE;
						break;
					}
				}
				if (skip_space == FALSE)
				{
					// Empty spaces
					printf("  ");
				}
			}
		}
		printf("|");
		printf("\n");
	}

	// Bottom Border
	for (int i = 0; i < TOP_BORDER_LENGTH; i++)
	{
		printf("-");
	}
	printf("\n\n");
}

int is_within_bounds(int x, int y)
{
	// COLS - 2 because we use two characters for each column spacing. Whitespace + whitespace
	return (0 <= x && x < COLS - 2 && 0 <= y && y < ROWS) ? TRUE : FALSE;
}

// TODO: Shouldn't be able to spawn in side snake
void generate_random_item_position()
{
	food_position[0] = rand() % (COLS - 2);
	food_position[1] = rand() % (ROWS);
}

// Simulate eating food: Update length and regen food position
int eat_food()
{
	if (
		snake_body[0][0] == food_position[0] &&
		snake_body[0][1] == food_position[1])
	{

		length += 1;
		snake_body[length][0] = food_position[0];
		snake_body[length][1] = food_position[1];
		generate_random_item_position();
		return 1;
	}
	return 0;
}

void player_move(int direction)
{
	int xDelta, yDelta, newX, newY;
	xDelta = yDelta = newX = newY = 0;

	if (direction == MOVE_UP)
	{
		yDelta -= 1;
	}
	else if (direction == MOVE_DOWN)
	{
		yDelta += 1;
	}
	else if (direction == MOVE_LEFT)
	{
		xDelta -= 1;
	}
	else if (direction == MOVE_RIGHT)
	{
		xDelta += 1;
	}

	newY = snake_body[0][1] + yDelta;
	newX = snake_body[0][0] + xDelta;

	if (is_within_bounds(newX, newY))
	{
		int x_temp = snake_body[0][0];
		int y_temp = snake_body[0][1];
		/*************************************
		Debug info
		printf("x_temp: %i\ny_temp: %i\n", x_temp, y_temp);
		printf("tail: %i, %i\n", snake_body[1][0], snake_body[1][1]);
		printf("length: %i", length);
		*************************************/
		for(int i = length; i >= 1; i --){
			snake_body[i][0] = snake_body[i-1][0];
			snake_body[i][1] = snake_body[i-1][1];
		}
		snake_body[0][0] = newX;
		snake_body[0][1] = newY;
		eat_food();
		
	}
}

// Source: https://github.com/ChrisMinich/robots/blob/master/helpers.c#L6-L25
// This guy is a legend for sourcing the code snippet.
// TODO: Figure out what this does.
int mygetch(void)
{
	int ch;
	struct termios oldt, newt;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

	return ch;
}

/*
	Simulates refreshing the screen.
	See https://stackoverflow.com/questions/55672661/what-does-printf-033h-033j-do-in-c
*/
void terminal_refresh()
{
	printf("\033[H\033[J");
}
int main()
{
	int direction = 0;
	srand(time(NULL));
	generate_random_item_position();

	while (direction != QUIT)
	{
		print_board();
		printf("Score:\t%i", length);
		direction = mygetch();
		terminal_refresh();
		if (direction == MOVE_UP ||
			direction == MOVE_DOWN ||
			direction == MOVE_LEFT ||
			direction == MOVE_RIGHT)
		{
			player_move(direction);
		}
	}
	return 0;
}

/*
X X X X X X X X X X X X X X X
X							X
X							X
X							X
X							X
X							X
X							X
X							X
X							X
X							X
X X X X X X X X X X X X X X X


ooooox


*/
