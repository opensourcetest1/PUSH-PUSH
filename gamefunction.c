﻿#include< stdio.h >
#include< conio.h >
#include< windows.h >
#include< stdlib.h >

#include "initialize.h"
#include "gamefunction.h"

extern char g_fileName[12];
char g_map[13][20];
int g_count = 0;

undostack *ud;

void init(undostack *s)
{
	s->top = 0;
}

int is_empty(undostack *s)
{
	return (s->top == -1);
}

int is_full(undostack *s)
{
	return (s->top == 999);
}void push(undostack *s, int item)
{
	if (is_full(s)) {
		fprintf(stderr, "Undo 불가");
		return;
	}
	else {
		s->stack[++(s->top)] = item;
		printf("%d", s->stack[s->top]);
		printf("%d", s->top);
	}
}

void push1(undostack *s, int item)
{
	if (is_full(s)) {
		fprintf(stderr, "Undo 불가");
		return;
	}
	else {
		s->ud[(s->top)] = item;
		printf("aaa : %d", item);
		printf(" %d %d ", s->top, s->stack1[s->top]);
	}
}

int pop(undostack *s)
{
	return s->stack[(s->top)];
}int pop1(undostack *s)
{
	return s->stack1[(s->top)--];
}void Draw()
{
	char m_level = 1;
	int i;
	int j;
	int tmp = 0;
	if (tmp == 0)
	{
		ud = (undostack *)malloc(100 * sizeof(undostack));
		init(ud);
		tmp++;
	}
	int m_x;
	int m_y;

	int m_boxCount = 0;

	system("cls");

	printf("▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩\n");
	printf("▩ ");
	ColorChange("R키 리셋", NULL, 15);
	printf(" ▩ ");
	ColorChange("COUNT : %03dMOVES", (char *)g_count, 15);
	printf("       ▩");
	for (i = 0; i<13; i++)
	{
		for (j = 0; j<20; j++)
		{
			switch (g_map[i][j])
			{
			case ' ':
				printf("  ");
				break;
			case '#':
				ColorChange("▩", NULL, 8);
				break;
			case '$':
				ColorChange("■", NULL, 9);
				break;
			case '.':
				m_boxCount = m_boxCount + 1;
				ColorChange("□", NULL, 6);
				break;
			case '+':
				m_x = i;
				m_y = j;
				m_boxCount = m_boxCount + 1;
				printf("ㅱ", NULL, 11);
				break;
			case '*':
				printf("▣", NULL, 11);
				break;
			case '@':
				m_x = i;
				m_y = j;
				ColorChange("㈜", NULL, 15);
				break;
			default:
				printf("▩");
			}
			//printf( "%c", g_map[i][j] );//디버그용
		}
		printf("\n");
		//printf( " i:%02d j:%02d\n", i,j );//디버그용, i와 j의 값을 확인하기 위해
	}
	if (m_boxCount != 0)
	{
		Move(m_x, m_y);
	}

	else if (g_fileName[5] >= 48 && g_fileName[5] < 57)
	{
		g_fileName[5]++;
		Level_Popup("Level Clear");
		GameStart(g_fileName);
	}

	else
	{
		Popup("Congratulations!");
	}
}

void GameStart(char _levelName[])
{
	LoadData(_levelName);
	Draw(g_map);
}

void Move(int _x, int _y)
{
	int i = 0;	//행
	int j = 0;	//열

	char m_key = _getch(); // 키를 입력받음 m_key 형태로
	switch (m_key)
	{
	case 72: //상
		g_count = g_count + 1;
		i = -1;
		j = 0;
		printf("%d", i);
		push(ud, i);
		push1(ud, j);
		break;
	case 80: //하
		g_count = g_count + 1;
		i = 1;
		j = 0;
		push(ud, i);
		push1(ud, j);
		break;
	case 75: //좌
		g_count = g_count + 1;
		i = 0;
		j = -1;
		push(ud, i);
		push1(ud, j);
		break;
	case 77: //우
		g_count = g_count + 1;
		i = 0;
		j = 1;
		push(ud, i);
		push1(ud, j);
		break;
	case 'u':
		if (g_count < 0)
			g_count = 0;
		else {
			i = (pop(ud));
			j = (pop1(ud));
			printf("%d", ud->top);
			printf("%d", i);
			printf("%d", j);
			g_count--;
		}
		break;
	case 'r':
		LoadData(g_fileName);
		break;
	case 27:
		g_count = 0;
		MainScreen();
	default:
		break;
	}
	switch (g_map[_x + i][_y + j])
	{
	case ' ':
		if (g_map[_x][_y] == '+')
		{
			g_map[_x + i][_y + j] = '@';
			g_map[_x][_y] = '.';
		}
		else
		{
			g_map[_x + i][_y + j] = g_map[_x][_y];
			g_map[_x][_y] = ' ';
		}
		break;
	case '$':
		if (g_map[_x][_y] == '+')
		{
			if (g_map[_x + 2 * i][_y + 2 * j] == '.')
			{
				g_map[_x + 2 * i][_y + 2 * j] = '*';
				g_map[_x + i][_y + j] = '@';
				g_map[_x][_y] = '.';
			}
			else if (g_map[_x + 2 * i][_y + 2 * j] == ' ')
			{
				g_map[_x + 2 * i][_y + 2 * j] = '$';
				g_map[_x + i][_y + j] = '@';
				g_map[_x][_y] = '.';
			}
		}
		switch (g_map[_x + 2 * i][_y + 2 * j])
		{
		case ' ':
			g_map[_x + 2 * i][_y + 2 * j] = '$';
			g_map[_x + i][_y + j] = '@';
			g_map[_x][_y] = ' ';
			break;
		case '.':
			g_map[_x + 2 * i][_y + 2 * j] = '*';
			g_map[_x + i][_y + j] = '@';
			g_map[_x][_y] = ' ';
			printf("\a");
			break;
		default:
			break;

		}
		break;
	case '.': //짐들어갈 빈칸
		if (g_map[_x][_y] == '+')
		{
			g_map[_x + i][_y + j] = '+';
			g_map[_x][_y] = '.';
		}
		else
		{
			g_map[_x + i][_y + j] = '+';
			g_map[_x][_y] = ' ';
		}
		break;
	case '*': //짐들어있는칸
		if (g_map[_x + 2 * i][_y + 2 * j] == ' ')
		{
			g_map[_x + 2 * i][_y + 2 * j] = '$';
			g_map[_x + i][_y + j] = '+';
			g_map[_x][_y] = ' ';
		}
		else if (g_map[_x + 2 * i][_y + 2 * j] == '.')
		{
			printf("\a");
			g_map[_x + 2 * i][_y + 2 * j] = '*';
			g_map[_x + i][_y + j] = g_map[_x][_y];
			g_map[_x][_y] = '.';
		}
		break;

	default:
		break;
	}
	Sleep(50);
	Draw();
}

void MoveCursor(int _x, int _y)
{
	COORD m_position = { _x - 1, _y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), m_position);
}

void Popup(char _message[])
{
	int i;
	//system( "cls" );
	MoveCursor(10, 7);
	printf("┏");
	for (i = 0; i < sizeof(_message) + 5; i++)
		printf("━");
	printf("┓\n");
	MoveCursor(10, 8);
	printf("┃ ");
	printf(_message);
	printf(" ┃\n");
	MoveCursor(10, 9);
	printf("┗");
	for (i = 0; i < sizeof(_message) + 5; i++)
		printf("━");
	printf("┛\n");

	MoveCursor(0, 16);
	_getch();
	MainScreen();
}

void Level_Popup(char _message[])
{
	int i;
	//system( "cls" );
	MoveCursor(10, 7);
	printf("┏");
	for (i = 0; i < sizeof(_message) + 2; i++)
		printf("━");
	printf("┓\n");
	MoveCursor(10, 8);
	printf("┃ ");
	printf(_message);
	printf(" ┃\n");
	MoveCursor(10, 9);
	printf("┗");
	for (i = 0; i < sizeof(_message) + 2; i++)
		printf("━");
	printf("┛\n");

	MoveCursor(0, 16);
	_getch();
	MainScreen();
}

void LoadData(char _fileName[])
{
	FILE *m_fp;
	int i = 0;
	g_count = 0;

	fopen_s(&m_fp, _fileName, "r");
	if (m_fp == NULL)
	{
		Popup("Can't Open File!");
	}
	while (!feof(m_fp))
	{
		fgets(g_map[i], 50, m_fp);
		i = i + 1;
	}
	fclose(m_fp);
}