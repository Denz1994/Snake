#include <stdio.h>

#define ROWS 10
#define COLS 30
#define TOP_BORDER_LENGTH 59
#define TRUE 1
#define FALSE 0

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
	return (0 <= x && 0 < COLS && 0 <= y && y < ROWS) ? TRUE : FALSE;
}

int main()
{
	print_board();
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
