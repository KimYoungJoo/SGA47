#pragma once

#include <iostream>
#include <conio.h>
#include <cstdlib>  // srand, rand
#include <ctime> // time, clock
#include <windows.h>

using namespace std;


void zero()
{
	HANDLE hCon = ::GetStdHandle(STD_OUTPUT_HANDLE);
	COORD z = {0, 0};
	::SetConsoleCursorPosition(hCon, z);
}

struct Point
{
	int x;
	int y;
	Point(const int& _x = -1, const int& _y = -1)
		: x(_x), y(_y)
	{}
};


class game
{
	enum dir_id
	{
		LEFT,
		UP,
		RIGHT,
		DOWN,
	};

public :
	game(const int& w = 70, const int& h = 20)
		: width(w), height(h)
		, blank('-'), mark('@'), border('#'), meat('$')
		, need_to_update(true), need_to_draw(true), meat_exist(false)
		, myPoint(width/2, height/2), myMeat()
		, meat_count(0), bordersize(1), mp_index(0)
		, board(NULL), meat_position(NULL)
		, speed(1), update_dt(0)
		, direction(LEFT)
	{
		srand((unsigned)time(NULL));

		board = new char[width*height];
		meat_position = new int[width*height];
	}
	~game()
	{
		if (board)
			delete board;
		if (meat_position)
			delete meat_position;
	}

	void Setup()
	{
		// 1. ������ �ʱ�ȭ...
		// 1-1. initialize board data.
		for (int i = 0; i < width*height; i++)
		{
			board[i] = blank;
		}
		// 1-2. initialize meat position index.
		for (int i = 0; i < width*height; i++)
		{
			meat_position[i] = i;
		}
		// 1-3. shuffle meat position index.
		for (int i = width*height-1; i > 0; i--)
		{
			int index = rand()%i;

			int tmp = meat_position[i];
			meat_position[i] = meat_position[index];
			meat_position[index] = tmp;
		}
	}
	bool Input()
	{
		if (_kbhit())
		{
			int key = _getch();
			if (key == 0x1B)
			{
				return false;
			}
			else if (key == 'a' || key == 'A')
			{
				if (myPoint.x - 1 < bordersize)
					return true;

				myPoint.x--;
			}
			else if (key == 'd' || key == 'D')
			{
				direction = RIGHT;
				//if (myPoint.x + 1 >= width - bordersize)
				//	return true;

				//myPoint.x++;
			}
			else if (key == 'w' || key == 'W')
			{
				if (myPoint.y - 1 < bordersize)
					return true;

				myPoint.y--;
			}
			else if (key == 's' || key == 'S')
			{
				if (myPoint.y + 1 >= height - bordersize)
					return true;

				myPoint.y++;
			}

			need_to_update = true;
		}

		return true;
	}
	void Update(clock_t tick)
	{
		if (speed*update_dt/1000 >= 1)
		{
			int count = speed*update_dt/1000; // ĭ��

			update_dt = update_dt - (count/speed)*1000;

			// 4-1. �Ծ����� �ȸԾ����� Ȯ��
			if (myPoint.x == myMeat.x && myPoint.y == myMeat.y)
			{
				meat_exist = false;
				meat_count++;
			}

			if (direction == LEFT)
			{
				myPoint.x -= 1;
			}
			else if (direction == UP)
			{
				myPoint.y -= 1;
			}
			else if (direction == RIGHT)
			{
				myPoint.x += 1;
			}
			else if (direction == DOWN)
			{
				myPoint.y += 1;
			}

			// todo update.
			for (int y = 0; y < height; y++)
			{
				for (int x = 0; x < width; x++)
				{
					if (x < bordersize || y < bordersize ||
						x >= width-bordersize || y >= height-bordersize)
						board[x + y*width] = border;
					else if (myPoint.x == x && myPoint.y == y)
						board[x + y*width] = mark;
					else if (myMeat.x == x && myMeat.y == y)
						board[x + y*width] = meat;
					else
						board[x + y*width] = blank;
				}
			}

			// 4-3. ���̰� �������� ������ ���̸� ��������.
			if (!meat_exist)
			{
				// �����...
				while (true)
				{
					if (board[meat_position[mp_index]] != blank)
					{
						mp_index++;
						if (mp_index >= width*height)
							mp_index=0;
					}
					else
					{
						myMeat.x = meat_position[mp_index]%width;
						myMeat.y = meat_position[mp_index]/width;
						board[meat_position[mp_index]] = meat;
						break;
					}
				}

				meat_exist = true;
			}

			need_to_draw = true;
			need_to_update = false;
		}

		update_dt += tick;
	}
	void Draw()
	{
		if (need_to_draw)
		{
			zero();

			cout << "Catch Meat~ by anonymous..." << endl;
			// todo draw..
			for (int y = 0; y < height; y++)
			{
				for (int x = 0; x < width; x++)
				{
					cout << board[x + y*width];
				}
				cout << endl;
			}
			cout << "current eaten count : " << meat_count << endl;

			need_to_draw = false;
		}
	}

private :
	// 0. ����� ���� �� ����� ����
	const int width;
	const int height;
	const char blank;
	const char mark;
	const char border;
	const char meat;
	bool need_to_update;
	bool need_to_draw;
	bool meat_exist;
	Point myPoint;
	Point myMeat;
	int meat_count;
	int bordersize;

	char *board;
	int *meat_position;
	int mp_index;

	//////////////////////////
	// �ڵ� ������...
	clock_t speed;			// 1ĭ/s
	clock_t update_dt;

	int direction; // left(0), top(1), right(2), bottom(3)
};
