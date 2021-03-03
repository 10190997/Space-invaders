#include <iostream>
#include <conio.h>
#include <windows.h>
#include <dos.h>
#include <time.h>
#include <stdio.h>

using namespace std;

int sleeper = 100;
bool endgame = false;
const char ship_char = 'W';
const char shoot_char = '^';
char alien_char[5] = { '@', '@', '@', '@', '@' };
int direct;
int coord_x = 10;
int coord_y = 18;
int Scoord_x = coord_x;
int Scoord_y = coord_y;
bool pew = false;
int alien_x, alien_y;
int aliens = 5;

void hide_cursor()
{
	HANDLE ch = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(ch, &info);
}

void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void border()
{
	for (int x = 1; x < 20; x += 2)
	{
		gotoxy(x, 1);
		printf(".");
	}
	for (int x = 1; x < 20; x += 2)
	{
		gotoxy(x, 19);
		printf(".");
	}
	for (int y = 1; y < 20; y++)
	{
		gotoxy(1, y);
		printf(".");
	}
	for (int y = 1; y < 20; y++)
	{
		gotoxy(19, y);
		printf(".");
	}
}

void draw()
{
	gotoxy(coord_x, coord_y);
	printf("%c", ship_char);
}

void alien()
{
	alien_x = rand() % 15 + 2;
	if (alien_x % 2 == 1) alien_x++;
	alien_y = rand() % 15 + 2;
	gotoxy(alien_x, alien_y);
	cout << alien_char[aliens - 1];
}

void step()
{
	gotoxy(coord_x, coord_y);
	printf(" ");
	switch (direct)
	{
	case 1: coord_x -= 2;
		break;
	case 2: coord_x += 2;
		break;
	}
}

void shoot()
{
	if (pew == true && Scoord_y > 2)
	{
		int temp = Scoord_y;
		Scoord_y--;
		gotoxy(Scoord_x, Scoord_y);
		printf("%c", shoot_char);
		gotoxy(Scoord_x, temp);
		printf(" ");
		Sleep(50);
	}
	else if (Scoord_y <= 2)
	{
		gotoxy(Scoord_x, Scoord_y);
		printf(" ");
		pew = false;
	}
	else pew = false;
}

bool win_check()
{
	if (aliens == 0)
	{
		system("cls");
		gotoxy(9, 9);
		cout << "YOU WON!";
		Sleep(500);
		gotoxy(1, 25);
		Sleep(0);
		return true;
	}
	else return false;
}

bool kill()
{
	if (Scoord_x == alien_x && Scoord_y == alien_y)
	{
		aliens--;
		return true;
	}
	return false;
}

int var = 1;

int game() {
	hide_cursor();
	coord_x = 10;
	coord_y = 18;
	Scoord_x = coord_x;
	Scoord_y = coord_y;
	pew = false;
	alien_x, alien_y;
	aliens = 5;
	border();
	alien();
	endgame = false;
	int key;
	while (endgame == false)
	{
		shoot();
		draw();
		if (_kbhit())
		{
			key = _getch();
			switch (key)
			{
			case VK_ESCAPE: endgame = true; break;
			case 0: break;
			case 224: continue; break;
			case 75: direct = 1; step(); break;	//left
			case 77: direct = 2; step(); break;	//right
			case VK_SPACE: 	if (pew == false)
			{
				Scoord_x = coord_x;
				Scoord_y = coord_y - 1;
				pew = true;
			}
						 else continue; break;
			}
			if (coord_x > 19) coord_x -= 2;
			if (coord_x < 1) coord_x += 2;
		}
		Sleep(0);
		if (kill())
		{
			win_check();
			alien();
		}
		gotoxy(1, 21);
		cout << "Пришельцев осталось: " << aliens;
		if (win_check())
			endgame = true;
	}
	system("cls");
	return 0;
}

void rules()
{
	cout << "П Р А В И Л А И Г Р Ы\n"
		<< "Защитите свой корабль от пришельцев!\n"
		<< "Управление кораблём: стрелки вправо и влево. Выстрел: пробел.\n"
		<< "Чтобы выйти из игры в меню, нажмите esc.\n\n"
		<< "Нажмите любую клавишу, чтобы вернуться в меню.\n";
	bool rule = true;
	while (rule)
	{
		int key;
		if (_kbhit())
		{
			key = _getch();
			switch (key)
			{
			default: system("cls");  rule = false; break;
			}
		}
	}
	return;
}

int main()
{
	system("color 0a");
	srand(time(NULL));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");
	while (var != 0)
	{
		cout << "S P A C E I N V A D E R S\n" << "1. Начать игру\n" << "2. Правила\n" << "0. Выход\n"
			<< "Выш выбор: ";
		cin >> var;
		switch (var)
		{
		case 0: system("cls"); gotoxy(9, 9);  cout << "\ngudbaiii\n\n" << endl;  break;
		case 1: system("cls"); game(); break;
		case 2: system("cls"); rules(); break;
		default: cout << "\n\nВведите существующий пункт меню\n\n" << endl;
			Sleep(500);
			system("cls");
			Sleep(0);
		}
	}
	gotoxy(1, 25);
	return 0;
}
