/*Nguyễn HỮu Tuấn-1753017*/
#define _CRT_SECURE_NO_WARNINGS // Để dùng được scanf trong VS2017

// KHAI BÁO CÁC THƯ VIỆN
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define N_ROWS 3
#define N_COLS 3

//KHAI BÁO CÁC PROTOTYPE
void print_board(int a[][N_COLS]);
void player_pace(int a[][N_COLS]);
void computer_pace(int a[][N_COLS]);
int compute_min_val(int a[][N_COLS]);
int compute_max_val(int a[][N_COLS]);
int board_full(int a[][N_COLS]);
int result_check(int a[][N_COLS]);

//Hàm main. 
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

		computer_pace(a);
		result = result_check(a);
		if (result != 0)
		{
			print_board(a);
			if (result == -2)
			{
				printf("\n0\n");//Hòa xuất 0
				return 0;
			}
			else
			{
				printf("\n1\n");// Máy thắng xuất 1
				return 0;
			}
		}

		player_pace(a);
		result = result_check(a);
		if (result != 0)
		{
			print_board(a);
			if (result == -2)
			{
				printf("\n0\n");
				return 0;
			}
			else
			{
				printf("\n-1\n");// Người thắng xuất -1
				return 0;
			}
		}


	}
	system("pause");
	return 0;
}

//Hàm in bàn cờ
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

// Hàm nhập nước đi của người chơi.
void player_pace(int a[][N_COLS])
{
	print_board(a);
	int x, y;
	do
	{
		printf("Your turn: ");
		scanf("%d %d", &x, &y);
	} while ((x > 2) || (y > 2) || (x < 0) || (y < 0) || (a[x][y] != 0));
	a[x][y] = -1;
}

// Hàm nhập nước đi của máy.
void computer_pace(int a[][N_COLS])
{
	int  Row = 0, Col = 0;
	int score = 10;
	int i, j;
	for (i = 0; i < N_COLS; i++)
		for (j = 0; j < N_ROWS; j++)
		{
			if (a[i][j] == 0)
			{
				a[i][j] = 1;
				int tempScore = compute_min_val(a);
				a[i][j] = 0;
				if (tempScore < score)
				{
					score = tempScore;
					Row = i;
					Col = j;
				}
			}
		}
	a[Row][Col] = 1;
}

//  Hàm đệ quy dùng để lấy giá trị nhỏ nhất trong tất cả các trạng thái tiếp theo.
int compute_min_val(int a[][N_COLS])
{
	int point = result_check(a);
	if ((point != 0) && (point != 2))
		return point;
	int state_val = 10;
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

// Hàm đệ quy dùng để lấy giá trị lớn nhất trong tất cả các trạng thái tiếp theo.
int compute_max_val(int a[][N_COLS])
{
	int point = result_check(a);
	if ((point != 0) && (point != 2))
		return point;
	int state_val = -10;
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

// Hàm kiểm tra bàn cờ đã đầy.
int board_full(int a[][N_COLS])
{
	int piece = 0;
	for (int i = 0; i < N_COLS; i++)
		for (int j = 0; j < N_ROWS; j++)
		{
			if (a[i][j] != 0)
				piece += 1;
		}
	if (piece == 9)
		return 1;
	return 0;
}

// Hàm kiểm tra đã có người chơi nào giành chiến thắng chưa.
int result_check(int a[][N_COLS])
{
	if ((a[0][0] == a[0][1]) && (a[0][1] == a[0][2]) && (a[0][0] != 0))
		return a[0][0];
	else if ((a[1][0] == a[1][1]) && (a[1][1] == a[1][2]) && (a[1][0] != 0))
		return a[1][0];
	else if ((a[2][0] == a[2][1]) && (a[2][1] == a[2][2]) && (a[2][0] != 0))
		return a[2][0];
	else if ((a[0][0] == a[1][0]) && (a[1][0] == a[2][0]) && (a[0][0] != 0))
		return a[0][0];
	else if ((a[0][1] == a[1][1]) && (a[1][1] == a[2][1]) && (a[0][1] != 0))
		return a[0][0];
	else if ((a[0][2] == a[1][2]) && (a[1][2] == a[2][2]) && (a[0][2] != 0))
		return a[0][2];
	else if ((a[0][0] == a[1][1]) && (a[1][1] == a[2][2]) && (a[0][0] != 0))
		return a[0][0];
	else if ((a[0][2] == a[1][1]) && (a[1][1] == a[2][0]) && (a[0][2] != 0))
		return a[0][2];
	// Bàn cờ đã đầy mà chưa có người chơi nào thắng.
	else if (board_full(a) == 1)
		return 2;
	else return 0;
}
