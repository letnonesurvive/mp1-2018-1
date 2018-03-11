#include <iostream>
#include <string> 
#include <conio.h>
#include <cstdio>
#include <clocale>
#define _CRT_SECURE_NO_WARNINGS
#define size 100

//!!! Внутри класса ничего не вводить с клавиатуры!!!\\

using namespace std;
class UserMenu
{
private:
	string menu[size];
	int commands = 0;//число команд 
	int push = 0;//кнопка для switch
	int x = 0; //координаты отступа
	int y = 0;//координаты отступа
	int ammount = 1;//отвечает за перемещение ползунка
	int num = 0;
	bool trigger = false;
	void base()
	{
		for (int i = 0; i < size; i++)
		{
			menu[i] = "\0";
		}
	}
public:
	UserMenu()
	{
		base();
	}
	void SetValueCommands(int _commands)//установить число команд для меню
	{
		commands = _commands;
	}
	int GetCommands()//узнать число команд меню
	{
		return commands;
	}
	int getnum()
	{
		return num;
	}
	void SetCommands(int num, string str)//принимает номер и строчку
	{
		if (commands < num)
			commands = num;
		menu[num] = str;
	}
	void SetPositionManual(int _x, int _y)//для расположения меню экрана ручная настройка
	{
		x = _x;
		y = _y;
	}
	void SetPosition(string str)
	{
		if (str == "default")
		{
			x = 0;
			y = 0;
		}
		if (str == "left+down")
		{
			x = 0;
			y = 50;
		}
		if (str == "right+up")
		{
			x = 50;
			y = 0;
		}
		if (str == "right+down")
		{
			x = 50;
			y = 50;
		}
		if (str == "middle")
		{
			x = 25;
			y = 8;
		}
	}
	void NewMenu()
	{
		if (ammount > commands)
			ammount = 1;
		if (ammount < 1)
			ammount = commands;
		for (int i = 0; i <= y; i++)//сносит строку (двигает вниз)
			cout << endl;
		for (int i = 1; i <= commands; i++)
		{
			for (int i = 0; i <= x; i++)//выписывает пробел(двигает вправо)
				cout << " ";
			if (ammount == i)
				cout << '>' << i << " " << menu[i] << endl;
			else
				cout << i << " " << menu[i] << endl;

		}
		for (int i = 0; i <= x; i++)
		{
			cout << " ";
		}
		if (trigger == true)
		{
			cout << "Последний пункт меню: " << getnum();
		}
		cout << endl;
		for (int i = 0; i <= x; i++)
		{
			cout << " ";
		}
		cout << "Нажмите ESC Для выхода";
	}
	void Print()//amount равна номеру пунтка меню на котором расположена стрелочка
	{
		while (push != 27)//для выходу из меню нажать ESC
		{
			system("cls");
			NewMenu();
			push = _getch();
			switch (push)
			{
			case 80://вниз
				ammount++;
				break;
			case 72://вверх
				ammount--;
				break;
			case 13://enter
				trigger = true;
				num = ammount;
				break;
			}
		}
	}
};
void main()
{
	setlocale(LC_ALL, "Rus");
	UserMenu menu1;
	UserMenu menu2;
	string str;
	int n = 3;
	menu1.SetValueCommands(n);//установите число команд
	menu1.SetPosition("middle");//установите расположение меню
	for (int i = 1; i <= n; i++)//ввод осуществлен внутри консоли
	{
		getline(cin, str);
		menu1.SetCommands(i, str);
	}
	menu1.Print();
	/*-------------------------------------------------------------*/
	/*-------------------------------------------------------------*/
	menu2.SetPosition("default");
	menu2.SetCommands(1, "Пункт первый");//демонстрация внутри кода
	menu2.SetCommands(2, "Пункт второй");
	menu2.SetCommands(3, "Пункт третий");
	menu2.Print();
}