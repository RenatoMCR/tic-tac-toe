#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define P1 'X'
#define P2 'O'
#define grid_size 5

void DrawBoard();
int CheckWin();

int turn = 1;

char symbols[2] = {P1, P2};
char grid[grid_size][grid_size];

int main(){
	memset(grid, ' ', sizeof(grid));

	while (1) {
		system("clear");

		DrawBoard();

		int column, line;

		printf("\nPlayer %d turn! (%c)\nPosition: ", turn, symbols[turn]);
		scanf("%d %d", &line, &column);

		if (grid[line - 1][column - 1] != ' ')
			continue;

		grid[line - 1][column - 1] = symbols[turn];

		if (CheckWin() == 1){
			printf("%sPlayer %d(%c) is the winner!%s\nPlay again? (y/...)\n", ANSI_COLOR_GREEN, turn, symbols[turn], ANSI_COLOR_RESET);

			char awnser;
			scanf(" %c", &awnser);

			if (awnser == 'y'){
				memset(grid, ' ', sizeof(grid));
				turn = 1;
				
				continue;
			}

			break;
		}

		turn++;
		turn = turn % 2;
	}

	printf("\n");

	return 0;
}

void DrawBoard(){
	for (int i = 0; i < grid_size; i++) {
		for (int j = 0; j < grid_size; j++){
			switch (grid[i][j]){
				case P1: printf(ANSI_COLOR_GREEN); break;
				case P2: printf(ANSI_COLOR_CYAN); break;
			}

			printf(" %c ", grid[i][j]);

			if (j != grid_size - 1)
				printf("%s|", ANSI_COLOR_MAGENTA);
		}

		if (i != grid_size - 1) {
			printf("\n");

			for (int x = 0; x <= grid_size; x++)
				printf("---");

			printf("\n");
		}

		printf(ANSI_COLOR_RESET);
	}
}

int CheckWin(){
	int horizontal = 0, vertical = 0;
	int diagonal_left = 0, diagonal_right = 0;

	for (int i = 0; i < grid_size; i++){
		for (int j = 0; j < grid_size; j++){
			if (grid[i][j] == symbols[turn])
				horizontal++;
			if (grid[j][i] == symbols[turn])
				vertical++;
		}

		if (horizontal == grid_size || vertical == grid_size)
			return 1;
		else
			horizontal = 0, vertical = 0;
	}

	for (int i = 0, j = grid_size - 1; i < grid_size; i++, j--){
		if (grid[i][i] == symbols[turn])
			diagonal_left++;
		if (grid[j][j] == symbols[turn])
			diagonal_right--;

		if (diagonal_left == grid_size || diagonal_right == grid_size)
			return 1;
	}
}
