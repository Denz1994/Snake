#include <stdio.h>
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

int player_position[2] = {0, 0};

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
			if (x == player_position[0] && y == player_position[1])
			{
				printf("x ");
			}
			else
			{
				printf("  ");
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
	// TODO: FIX MACRO USAGE?
	return (0 <= x && 0 < COLS && 0 <= y && y < ROWS) ? TRUE : FALSE;
}

void player_move(int direction)
{
	int xDelta = 0;
	int yDelta = 0;

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

	// TODO: MAKE SURE WE ARE IN BOUNDS
	player_position[1] += yDelta;
	player_position[0] += xDelta;
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
int main()
{
	int direction = 0;
	int c = mygetch();
	printf("Input: %c", c);
	// print_board();

	// while (direction = mygetch() != 'Q')
	// {
	// 	// direction = mygetch();
	// 	if (direction == MOVE_UP ||
	// 		direction == MOVE_DOWN ||
	// 		direction == MOVE_LEFT ||
	// 		direction == MOVE_RIGHT)
	// 	{
	// 		player_move(direction);
	// 	}
	// 	printf("\n\n\n\n\n\n\n\n\n\n");
	// 	printf("\n\n\n\n\n\n\n\n\n\n");
	// 	printf("\n\n\n\n\n\n\n\n\n\n");

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
*/
