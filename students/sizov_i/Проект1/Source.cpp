#include <iostream>
#include <string> 
#include <conio.h>
#include <cstdio>
#include <clocale>
#define _CRT_SECURE_NO_WARNINGS
#define size 100

//!!! ¬нутри класса ничего не вводить с клавиатуры!!!\\

using namespace std;
class UserMenu
{
private:
	string menu[size];
	bool trigger=false;
	int commands = 0;//число команд 
	int push = 0;//кнопка дл€ switch
	int x = 0; //координаты отступа
	int y = 0;//координаты отступа
	int ammount = 1;//отвечает за перемещение ползунка
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
	void SetValueCommands(int _commands)//установить число команд дл€ меню
	{
		commands = _commands;
	}
	int GetValueCommads()//добавил метод возвращени€ команд 
	{
		return commands;
	}
	void SetCommand(int num, string str)//принимает номер и строчку
	{
		if (commands < num)
			commands = num;
		menu[num] = str;
	}
	void SetPositionManual(int _x, int _y)//дл€ расположени€ меню экрана ручна€ настройка
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
	void PrintMenu()
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
	}
	void CallMenu()//amount равна номеру пунтка меню на котором расположена стрелочка
	{
		while (push!=13)
		{
			system("cls");
			PrintMenu();
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
				break;
			}
		}
	}
	int GetCallMenu()//немного переделал возвращаемое значение
	{
		for (int i = 0; i <= x; i++)
			cout << " ";
		if (trigger = true)
			return ammount;
	}
};
void main()
{
	setlocale(LC_ALL, "Rus");
	UserMenu menu1;
	menu1.SetPosition("middle");//установите расположение меню
	menu1.SetCommand(1, "ѕривет");
	menu1.SetCommand(2, "ѕривет");
	menu1.SetCommand(3, "ѕривет");
	menu1.SetCommand(4, "ѕривет");
	menu1.SetCommand(5, "ѕривет");
	menu1.CallMenu(); //вызвать меню 
	cout<<menu1.GetCallMenu();//получить значение выбранного пункта меню
	system("pause");
}