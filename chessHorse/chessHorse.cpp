// chessHorse.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <stdio.h>

#define HEIGHT 8
#define WIDTH 8

#define PLUS3(x) (x + 2) < HEIGHT ? x + 2 : -100
#define MINUS3(x) (x - 2) >= 0 ? x - 2 : -100
#define PLUS1(x) (x + 1) < HEIGHT ? x + 1 : -100
#define MINUS1(x) (x - 1) >= 0 ? x - 1 : -100

struct WayToGo {
	//int StCoord[2];
	int UpLeft[2];
	int UpRigth[2];
	int RightUp[2];
	int RightDown[2];
	int DownRight[2];
	int DownLeft[2];
	int LeftDown[2];
	int LeftUp[2];
};

struct WayToGo allWays[HEIGHT][WIDTH];

int fillStr() {
	int i = 0;
	int j = 0;
	int yp3 = 0, ym3 = 0, yp1 = 0, ym1 = 0, xp3 = 0, xm3 = 0, xp1 = 0, xm1 = 0;
	for (i = 0; i < HEIGHT; i++)
	{
		yp3 = PLUS3(i);
		ym3 = MINUS3(i);
		yp1 = PLUS1(i);
		ym1 = MINUS1(i);
		for (j = 0; j < WIDTH; j++)
		{
			xp3 = PLUS3(j);
			xm3 = MINUS3(j);
			xp1 = PLUS1(j);
			xm1 = MINUS1(j);
			allWays[i][j].UpLeft[1] = yp3;
			allWays[i][j].UpLeft[2] = xm1;
			allWays[i][j].UpRigth[1] = yp3;
			allWays[i][j].UpRigth[2] = xp1;
			allWays[i][j].RightUp[1] = yp1;
			allWays[i][j].RightUp[2] = xp3;
			allWays[i][j].RightDown[1] = ym1;
			allWays[i][j].RightDown[2] = xp3;
			allWays[i][j].DownRight[1] = ym3;
			allWays[i][j].DownRight[2] = xp1;
			allWays[i][j].DownLeft[1] = ym3;
			allWays[i][j].DownLeft[2] = xm1;
			allWays[i][j].LeftDown[1] = ym1;
			allWays[i][j].LeftDown[2] = xm3;
			allWays[i][j].LeftUp[2] = yp1;
			allWays[i][j].LeftUp[2] = xm3;
		}
	}
	return 0;
}

int printBoard(int board[][WIDTH]) {
	int i = 0;
	int j = 0;
    printf("      %s\n      ", "------------------------------------------");
	for (i = 0; i < HEIGHT; i++)
	{
		for (j = 0; j < WIDTH; j++)
		{
			printf("|%3d ", board[i][j]);
		}
		printf("|\n      %s\n      ", "------------------------------------------");
	}
	return 0;
}

int freePlace(int n, int board[][WIDTH], int x, int y) {
	if (y != -100 && x != -100 && board[y][x] == 0)
	{
		return 1;
	}
	return 0;
}

int horseGo(int n, int board[][WIDTH], int x, int y) {
	int new_x = x;
	int new_y = y;
	board[y][x] = n;
	printBoard(board);
	while (n < 64) {
		if (freePlace(n, board, allWays[y][x].UpLeft[1], allWays[y][x].UpLeft[2]) == 0) {
			if (freePlace(n, board, allWays[y][x].UpRigth[1], allWays[y][x].UpRigth[2]) == 0) {
				if (freePlace(n, board, allWays[y][x].RightUp[1], allWays[y][x].RightUp[2]) == 0) {
					if (freePlace(n, board, allWays[y][x].RightDown[1], allWays[y][x].RightDown[2]) == 0) {
						if (freePlace(n, board, allWays[y][x].DownRight[1], allWays[y][x].DownRight[2]) == 0) {
							if (freePlace(n, board, allWays[y][x].DownLeft[1], allWays[y][x].DownLeft[2]) == 0) {
								if (freePlace(n, board, allWays[y][x].LeftDown[1], allWays[y][x].LeftDown[2]) == 0) {
									if (freePlace(n, board, allWays[y][x].LeftUp[1], allWays[y][x].LeftUp[2]) == 0) {
										board[y][x] = 0;
										return 0;
									}
									else {
										new_y = allWays[y][x].LeftUp[1];
										new_x = allWays[y][x].LeftUp[2];
									}
								}
								else {
									new_y = allWays[y][x].LeftDown[1];
									new_x = allWays[y][x].LeftDown[2];
								}
							}
							else {
								new_y = allWays[y][x].DownLeft[1];
								new_x = allWays[y][x].DownLeft[2];
							}
						}
						else {
							new_y = allWays[y][x].DownRight[1];
							new_x = allWays[y][x].DownRight[2];
						}
					}
					else {
						new_y = allWays[y][x].RightDown[1];
						new_x = allWays[y][x].RightDown[2];
					}
				}
				else {
					new_y = allWays[y][x].RightUp[1];
					new_x = allWays[y][x].RightUp[2];
				}
			}
			else {
				new_y = allWays[y][x].UpRigth[1];
				new_x = allWays[y][x].UpRigth[2];
			}
		}
		else {
			new_y = allWays[y][x].UpLeft[1];
			new_x = allWays[y][x].UpLeft[2];
		}
		if (horseGo(n + 1, board, new_x, new_y) == 0)
		{
			board[new_y][new_x] = 0;
			n--;
		}
	}
	return 1;
}

int main()
{
	int board[HEIGHT][WIDTH] = { 0 };
	fillStr();
	horseGo(1, board, 0, 0);
	printBoard(board);
	
}