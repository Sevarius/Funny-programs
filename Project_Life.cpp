#include "iostream"
#include "time.h"
#include <stdlib.h>
#include <dos.h>
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
using namespace std;

int print_field(char *field, const int field_size);
int count_friends(char *field, const int i, const int j, const int field_size, const char cell);

int main(void) {

	
	srand(time(0));
	const char cell = 219;	//254, 219, 249, 111, 48
	const char nothing = 32;	//32
	const int field_size = 60;
	char field[field_size][field_size], sfield[field_size][field_size];
	int a, friends;
	char knob = 'w';

	for (int i = 0; i < field_size; i++)
		for (int j = 0; j < field_size; j++)
			field[i][j] = nothing;

	for (int i = 0; i < field_size; i++) {
		for (int j = 0; j < field_size; j++) {
			a = rand() % 4;
			if (a == 0)
				field[i][j] = cell;
			else
				field[i][j] = nothing;
		}
	}

	print_field(&field[0][0], field_size);

	while (true) {

		for (int i = 0; i < field_size; i++)
			for (int j = 0; j < field_size; j++)
				sfield[i][j] = nothing;

		for (int i = 0; i < field_size; i++) {
			for (int j = 0; j < field_size; j++) {

				friends = count_friends(&field[0][0], i, j, field_size, cell);

				if (field[i][j] == cell && (friends == 2 || friends == 3))
					sfield[i][j] = cell;
				if (field[i][j] == nothing && friends == 3)
					sfield[i][j] = cell;

			}
		}

		for (int i = 0; i < field_size; i++)
			for (int j = 0; j < field_size; j++) {
				field[i][j] = sfield[i][j];
			}

		print_field(&field[0][0], field_size);
		Sleep(300);
	}
	

	cout << "\n";
	system("pause");
	return 0;
}

int count_friends(char *field, const int i, const int j, const int field_size, const char cell) {
	int friends = 0;
	int m[8][2] = { 0 };
	m[0][0] = i - 1;
	m[0][1] = j - 1;
	m[1][0] = i - 1;
	m[1][1] = j;
	m[2][0] = i - 1;
	m[2][1] = j + 1;
	m[3][0] = i;
	m[3][1] = j + 1;
	m[4][0] = i + 1;
	m[4][1] = j + 1;
	m[5][0] = i + 1;
	m[5][1] = j;
	m[6][0] = i + 1;
	m[6][1] = j - 1;
	m[7][0] = i;
	m[7][1] = j - 1;
	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 2; y++) {
			if (m[x][y] < 0)
				m[x][y] = field_size - 1;
			if (m[x][y] > field_size - 1)
				m[x][y] = 0;
		}
		if (*(field + m[x][0] * field_size + m[x][1]) == cell)
			friends++;
	}

	return friends;
}

int print_field(char *field, const int field_size) {
	
	system("cls");
	
	for (int i = 0; i < field_size; i++) {
		for (int j = 0; j < field_size; j++) {
			cout << *(field + i * field_size + j);
		}
		cout << "\n";
	}
	
	return 0;
}