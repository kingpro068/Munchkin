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
int check_full_board(int a[][N_COLS]);
void computer_turn(int a[][N_COLS]);
void player_turn(int a[][N_COLS]);
int compute_min_val(int a[][N_COLS]);
int compute_max_val(int a[][N_COLS]);

int main()
{
	int a[N_ROWS][N_COLS];
	int result;

	for (int i = 0; i < N_ROWS; i++)
		for (int j = 0; j < N_COLS; j++)
		{
			a[i][j] = 0;                    //Làm trống bàn cờ
		}
    printf("You are 'O' player!\n");
	while (true)
	{
	    //Lượt chơi của máy
		computer_turn(a);
		result = check_winner(a);
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
				printf("\n1\n");
				return 0;
			}
		}
        //Lượt chơi của người chơi
		player_turn(a);
		result = check_winner(a);
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
				printf("\n-1\n");
				return 0;
			}
		}
	}
	system("pause");
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
void player_turn(int a[][N_COLS])
{
	print_board(a);
	int x, y;
	do
	{
		printf("Player Turn! Please enter the value of rows and cols: ");
		scanf("%d %d", &x, &y);
	}
	while ((x > 2) || (y > 2) || (x < 0) || (y < 0) || (a[x][y] != 0));

	a[x][y] = -1;

}
void computer_turn(int a[][N_COLS])
{
	int Ox = -1, Oy = -1;
	int score = -99;
	int i, j;
	for (i = 0; i < N_COLS; i++)
		for (j = 0; j < N_ROWS; j++)
		{
			if (a[i][j] == 0)
			{
				a[i][j] = 1;                                //Đi thử
				int maxScore = compute_min_val(a);         //Giả định bước đi của người chơi
				a[i][j] = 0;                                //Trả về giá trị ban đầu
				if (maxScore > score)
				{
					score = maxScore;                      //Điểm tốt nhất khi đi nước này
					Ox = i;                                 //Gán tọa độ của hàng
					Oy = j;                                 //Gán tọa độ của cột
				}
			}
		}
	a[Ox][Oy] = 1;
}

int compute_min_val(int a[][N_COLS])            //Hàm tính giá trị min của của trạng thái
{
	int result = check_winner(a);
	if ((result != 0) && (result != -2))          //Kiểm tra trạng thái bàn cờ
		return result;                            //Nếu đã đạt trạng thái kết thúc thì trả về số điểm của trạng thái
	int state_val = 99;
	int i, j;
	for (i = 0; i < N_COLS; i++)
		for (j = 0; j < N_ROWS; j++)
		{
			if (a[i][j] == 0)
			{
				a[i][j] = -1;                           //Đi thử
				int min_val = compute_max_val(a);       //Giả định nước đi đối thủ
				if (min_val < state_val)                //Nếu nước đi giả định có giá trị nhỏ hơn giá trị trạng thái ban đầu thì gán nhỏ nhất cho giá trị của trạng thái
				{
					state_val = min_val;
				}
				a[i][j] = 0;                            //Trả về giá trị ban đầu
			}
		}
	return state_val;                                   //Trả về điểm của ô trạng thái
}
int compute_max_val(int a[][N_COLS])                    //Hàm tính giá trị max của trạng thái
{
	int result = check_winner(a);
	if ((result != 0) && (result != -2))                     //Tương tự như hàm compute_min_val
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
int check_winner(int a[][N_COLS])       //Hàm kiểm tra điều khiện thắng
{
	for (int i = 0; i < N_ROWS; i++)
		if ((a[i][0] == a[i][1]) && (a[i][1] == a[i][2]) && (a[i][1] != 0))   //Kiểm tra điều kiện thắng theo hàng
			return a[i][0];

	for (int j = 0; j < N_COLS; j++)
		if ((a[0][j] == a[1][j]) && (a[1][j] == a[2][j]) && (a[1][j] != 0))     //Kiểm tra điều kiện thắng theo cột
			return a[0][j];

	if ((a[0][0] == a[1][1]) && (a[1][1] == a[2][2]) && (a[1][1] != 0))         //Kiểm tra điều kiện thắng theo đường chéo chính
		return a[0][0];

	else if ((a[2][0] == a[1][1]) && (a[1][1] == a[0][2]) && (a[1][1] != 0))       //Kiểm tra điều kiện thắng theo đường chéo phụ
		return a[2][0];

	else if (check_full_board(a) == 1) return -2;                    //Nếu bàn cờ đầy và không ai thắng thì hòa, trả về -2;

	else return 0;                                              //Nếu vẫn chưa kết thúc game thì trả về 0
}

int check_full_board(int a[][N_COLS])                 //Hàm kiểm tra bàn cờ đã được đánh hết chưa
{
	int count = 0;
	for (int i = 0; i < N_COLS; i++)
		for (int j = 0; j < N_ROWS; j++)
		{
			if (a[i][j] != 0) count += 1;       //Nếu tại ô đã được đánh thì tăng biến đếm count
		}
	if (count == 9) return 1;                   //Nếu cả 9 ô đã được đánh thì bàn cờ đầy , trả về 1
	return 0;
}
