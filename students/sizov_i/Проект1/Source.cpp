#include <iostream>
#include <string> 
#include <conio.h>
#include <cstdio>
#include <clocale>
#define _CRT_SECURE_NO_WARNINGS
#define size 100

//!!! ������ ������ ������ �� ������� � ����������!!!\\

using namespace std;
class UserMenu
{
private:
	string menu[size];
	bool trigger=false;
	int commands = 0;//����� ������ 
	int push = 0;//������ ��� switch
	int x = 0; //���������� �������
	int y = 0;//���������� �������
	int ammount = 1;//�������� �� ����������� ��������
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
	void SetValueCommands(int _commands)//���������� ����� ������ ��� ����
	{
		commands = _commands;
	}
	int GetValueCommads()//������� ����� ����������� ������ 
	{
		return commands;
	}
	void SetCommand(int num, string str)//��������� ����� � �������
	{
		if (commands < num)
			commands = num;
		menu[num] = str;
	}
	void SetPositionManual(int _x, int _y)//��� ������������ ���� ������ ������ ���������
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
		for (int i = 0; i <= y; i++)//������ ������ (������� ����)
			cout << endl;
		for (int i = 1; i <= commands; i++)
		{
			for (int i = 0; i <= x; i++)//���������� ������(������� ������)
				cout << " ";
			if (ammount == i)
				cout << '>' << i << " " << menu[i] << endl;
			else
				cout << i << " " << menu[i] << endl;
		}
	}
	void CallMenu()//amount ����� ������ ������ ���� �� ������� ����������� ���������
	{
		while (push!=13)
		{
			system("cls");
			PrintMenu();
			push = _getch();
			switch (push)
			{
			case 80://����
				ammount++; 
				break;
			case 72://�����
				ammount--;
				break;
			case 13://enter
				trigger = true;
				break;
			}
		}
	}
	int GetCallMenu()//������� ��������� ������������ ��������
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
	menu1.SetPosition("middle");//���������� ������������ ����
	menu1.SetCommand(1, "������");
	menu1.SetCommand(2, "������");
	menu1.SetCommand(3, "������");
	menu1.SetCommand(4, "������");
	menu1.SetCommand(5, "������");
	menu1.CallMenu(); //������� ���� 
	cout<<menu1.GetCallMenu();//�������� �������� ���������� ������ ����
	system("pause");
}