/*
Họ tên: Nguyễn Dương Trí
MSSV: 1753020
*/

#define _CRT_SECURE_NO_WARNINGS // Để dùng được scanf trong VS2017

// KHAI BÁO CÁC THƯ VIỆN
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define N_ROWS 3
#define N_COLS 3

//KHAI BÁO CÁC PROTOTYPE
void print_board(int a[][N_COLS]);
int check_winner(int a[][N_COLS]);
int check_draw(int a[][N_COLS]);
void computer(int a[][N_COLS]);
void player(int a[][N_COLS]);
int compute_min_val(int a[][N_COLS]);
int compute_max_val(int a[][N_COLS]);

int main()
{
	int a[N_ROWS][N_COLS];
	int result;

	for (int i = 0; i < N_ROWS; i++)
		for (int j = 0; j < N_COLS; j++)
		{
			a[i][j] = 0;
		}
	while (true)
	{
		computer(a);
		result = check_winner(a);
		if (result != 0)
		{
            	print_board(a);
			if (result == -2)
			{
				printf("\nDraw\n\n0\n");
				return 0;
			}
			else
			{
				printf("\nAI win\n\n1\n");
				return 0;
			}
		}

		player(a);
		result = check_winner(a);
		if (result != 0)
		{
			print_board(a);
			if (result == -2)
			{
				printf("\nDraw\n\n0\n");
				return 0;
			}
			else
			{
				printf("\nYou win\n\n-1\n");
				return 0;
			}
		}
	}
	return 0;
}

void print_board(int a[][N_COLS])
{
	// In chỉ số cột của bàn cờ
	printf("\n   ");
	for (int j = 0; j < N_COLS; j++)
		printf("  %i ", j);
	printf("\n");

	// In đường kẻ ngang của bàn cờ
	printf("   ");
	for (int k = 0; k < N_COLS; k++)
		printf("+---");
	printf("+\n");

	for (int i = 0; i < N_ROWS; i++) // Duyệt dòng
	{
		printf(" %i ", i); // In chỉ số dòng của bàn cờ
		for (int j = 0; j < N_COLS; j++) // Duyệt cột
		{
			if (a[i][j] > 0)
				printf("| x ");
			else if (a[i][j] < 0)
				printf("| o ");
			else
				printf("|   ");
		}
		printf("|\n");

		// In đường kẻ ngang của bàn cờ
		printf("   ");
		for (int k = 0; k < N_COLS; k++)
			printf("+---");
		printf("+\n");
	}
	printf("\n");
}
void player(int a[][N_COLS])
{
	print_board(a);
	int x, y;
	do
	{
		printf("O Player Turn! Please enter the value of rows and cols: ");
		scanf("%d %d", &x, &y);
	}
	while ((x > 2) || (y > 2) || (x < 0) || (y < 0) || (a[x][y] != 0));

	a[x][y] = -1;

}
void computer(int a[][N_COLS])
{
	int moveX = -1, moveY = -1;
	int score = -99;
	int i, j;
	for (i = 0; i < N_COLS; i++)
		for (j = 0; j < N_ROWS; j++)
		{
			if (a[i][j] == 0)
			{
				a[i][j] = 1;
				int tempScore = compute_min_val(a);
				a[i][j] = 0;
				if (tempScore > score)
				{
					score = tempScore;
					moveX = i;
					moveY = j;
				}
			}
		}
	a[moveX][moveY] = 1;
}

int compute_min_val(int a[][N_COLS])
{
	int result = check_winner(a);
	if ((result != 0) && (result != -2))
		return result;
	int state_val = 99;
	int i, j;
	for (i = 0; i < N_COLS; i++)
		for (j = 0; j < N_ROWS; j++)
		{
			if (a[i][j] == 0)
			{
				a[i][j] = -1;
				int min_val = compute_max_val(a);
				if (min_val < state_val)
				{
					state_val = min_val;
				}
				a[i][j] = 0;
			}
		}
	return state_val;
}
int compute_max_val(int a[][N_COLS])
{
	int result = check_winner(a);
	if ((result != 0) && (result != -2))
		return result;
	int state_val = -99;
	int i, j;
	for (i = 0; i < N_COLS; i++)
		for (j = 0; j < N_ROWS; j++)
		{
			if (a[i][j] == 0)
			{
				a[i][j] = 1;
				int max_val = compute_min_val(a);
				if (max_val > state_val)
				{
					state_val = max_val;
				}
				a[i][j] = 0;
			}
		}
	return state_val;
}
int check_winner(int a[][N_COLS])
{
	for (int i = 0; i < N_ROWS; i++)
		if ((a[i][0] == a[i][1]) && (a[i][1] == a[i][2]) && (a[i][1] != 0))
			return a[i][0];

	for (int j = 0; j < N_COLS; j++)
		if ((a[0][j] == a[1][j]) && (a[1][j] == a[2][j]) && (a[1][j] != 0))
			return a[0][j];

	if ((a[0][0] == a[1][1]) && (a[1][1] == a[2][2]) && (a[1][1] != 0))
		return a[0][0];

	else if ((a[2][0] == a[1][1]) && (a[1][1] == a[0][2]) && (a[1][1] != 0))
		return a[2][0];

	else if (check_draw(a) == 1) return -2;

	else return 0;
}

int check_draw(int a[][N_COLS])
{
	int count = 0;
	for (int i = 0; i < N_COLS; i++)
		for (int j = 0; j < N_ROWS; j++)
		{
			if (a[i][j] != 0) count += 1;
		}
	if (count == 9) return 1;
	return 0;
}
