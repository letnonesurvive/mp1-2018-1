#include <iostream>
#include <string>
#include <Windows.h>
#include <cstdlib>
#include <conio.h>
#include <random>
using namespace std;
#define n 25//ширина
#define m 20//высота
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
COORD position;
class Interface;
class Food;
class Snake;
class Game;
bool Gameover = false;
void DisableShowConsoleCursor()//отключение мигающей штуки
{
	CONSOLE_CURSOR_INFO     showCursor;
	GetConsoleCursorInfo(hConsole, &showCursor);
	showCursor.bVisible = false;
	SetConsoleCursorInfo(hConsole, &showCursor);
}

void cls(HANDLE hConsole)//Альтернатива system("cls") чтобы не моргал экран
{
	COORD coordScreen = { 0, 0 };
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;

	if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
		return;
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	if (!FillConsoleOutputCharacter(hConsole, (TCHAR) ' ',
		dwConSize, coordScreen, &cCharsWritten))
		return;
	if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
		return;
	if (!FillConsoleOutputAttribute(hConsole, csbi.wAttributes,
		dwConSize, coordScreen, &cCharsWritten))
		return;
	SetConsoleCursorPosition(hConsole, coordScreen);
}

void setposition(int x, int y)
{
	position.X = x;
	position.Y = y;
	SetConsoleCursorPosition(hConsole, position);
}

void GameSpeed(int speed)
{
	Sleep(speed);
}

enum ConsoleColor
{
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};

class Snake
{
	int maxtail;
	int tail = 5;
	enum Moving { Stop, Left, Right, Up, Down }dir;
	struct body
	{
		int x;
		int y;
	}snake[(n - 2)*(m - 2) + 1];
public:
	Snake()
	{
		for (int i = 0; i < tail; i++)
		{
			dir = Stop;
			snake[i].x = n / 2 + i;
			snake[i].y = m / 2;
		}
	}
	void SetMaxTail(int _maxtail)
	{
		if (_maxtail>tail)
			maxtail = _maxtail;
		else throw;
	}
	void DrawSnake()//рисуем змейку
	{
		cls(hConsole);
		setposition(snake[0].x, snake[0].y);
		SetConsoleTextAttribute(hConsole, (WORD)((Black) | Yellow));
		cout << "O";
		for (int i = 1; i < tail; i++)
		{
			setposition(snake[i].x, snake[i].y);
			SetConsoleTextAttribute(hConsole, (WORD)((Black) | Green));
			cout << "o";
		}
	}
	void crawl()//хвост ползет за головой
	{
		if (dir != Stop)
		{
			for (int i = tail; i > 0; i--)
			{
				snake[i].x = snake[i - 1].x;
				snake[i].y = snake[i - 1].y;
			}
		}
	}
	void control()//функция управления
	{
		switch (dir)
		{
		case Left:snake[0].x--; break;
		case Right:snake[0].x++; break;
		case Up:snake[0].y--; break;
		case Down:snake[0].y++; break;
		}
	}
	void kb()
	{
		if (_kbhit())
		{
			switch (_getch())
			{
			case 72:if (dir != Down&&dir != Stop)dir = Up; break;
			case 80:if (dir != Up&&dir != Stop)dir = Down; break;
			case 75:if (dir != Right&&dir != Stop)dir = Left; break;
			case 77:if (dir != Left && dir != Stop)dir = Right; break;
			case 13:if (dir == Stop)dir = Left; break;
			}
		}
	}
	void Check()
	{
		for (int i = 1; i < tail; i++)
		{
			if (snake[0].x == snake[i].x&&snake[0].y == snake[i].y)
			{
				Gameover = true;
				cls(hConsole);
				cout << "YOU LOSE";
			}
		}
		for (int i = 1; i < n; i++)
		{
			if (snake[0].x == i && (snake[0].y == 1 || snake[0].y == m))
			{
				Gameover = true;
				cls(hConsole);
				cout << "YOU LOSE";
			}
		}
		for (int i = 1; i < m; i++)
		{
			if (snake[0].y == i && (snake[0].x == 1 || snake[0].x == n))
			{
				Gameover = true;
				cls(hConsole);
				cout << "YOU LOSE";
			}
		}
		if (tail == maxtail)
		{
			Gameover = true;
			cls(hConsole);
			cout << "YOU WIN";
		}
	}
	friend class Food;
	friend class Interface;
}s;

class Interface
{
	int x;
	int y;
	int score;
public:
	void ShowMap()//рисуем карту
	{
		SetConsoleTextAttribute(hConsole, (WORD)((Black) | White));
		for (int j = 0; j < 2; j++)
		{
			for (int i = 0; i < n; i++)
			{
				setposition(i, j);
				cout << "#";
			}
			for (int i = 0; i < m; i++)
			{
				setposition(n + j, i);
				cout << "#";
			}
			for (int i = 0; i < m; i++)
			{
				setposition(j, i);
				cout << "#";
			}
			for (int i = 0; i < n + 2; i++)
			{
				setposition(i, m + j);
				cout << "#";
			}
		}
		setposition(0, m + 2);
		cout << "Score:" << score << " ";
		if (s.dir == s.Stop)
			cout << "Press Enter" << endl;
	}
	friend class Food;
}A;

class Food
{
private:
	int eatx;
	int eaty;
	bool did = true;
	void create()
	{
		random_device random_device;
		mt19937 generator(random_device());
		uniform_int_distribution<int> randx(2, n - 2);
		uniform_int_distribution<int> randy(2, m - 2);
		eatx = randx(generator);
		eaty = randy(generator);
		for (int i = 0; i < s.tail; i++)
		{
			if (eatx == s.snake[i].x&&eaty == s.snake[i].y)
				create();
		}
	}
public:
	void ShowEAT()
	{
		if (did)
		{
			create();
			did = false;
		}
		else
		{
			setposition(eatx, eaty);
			cout << "*";
			if (s.snake[0].x == eatx&&s.snake[0].y == eaty)
			{
				A.score += 10;
				s.tail++;
				did = true;
			}
		}
	}
}eat;

void mainfunction()
{
	int lenth;
	int speed;
	cout << "Enter lenth" << endl;
	cin >> lenth;
	s.SetMaxTail(lenth);
	cout << "Enter speed(recommended speed 100)" << endl;
	cin >> speed;
	while (!Gameover)
	{
		s.DrawSnake();//рисуем змею
		A.ShowMap();//рисуем карту
		eat.ShowEAT();
		s.crawl();
		GameSpeed(speed);
		s.kb();
		s.control();
		s.Check();
	}
}

int main()
{
	DisableShowConsoleCursor();
	mainfunction();
	system("pause>>NULL");
}