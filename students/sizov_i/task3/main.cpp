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
	int commands = 0;//����� ������ 
	int push = 0;//������ ��� switch
	int x = 0; //���������� �������
	int y = 0;//���������� �������
	int ammount = 1;//�������� �� ����������� ��������
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
	void SetValueCommands(int _commands)//���������� ����� ������ ��� ����
	{
		commands = _commands;
	}
	int GetCommands()//������ ����� ������ ����
	{
		return commands;
	}
	int getnum()
	{
		return num;
	}
	void SetCommands(int num, string str)//��������� ����� � �������
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
	void NewMenu()
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
		for (int i = 0; i <= x; i++)
		{
			cout << " ";
		}
		if (trigger == true)
		{
			cout << "��������� ����� ����: " << getnum();
		}
		cout << endl;
		for (int i = 0; i <= x; i++)
		{
			cout << " ";
		}
		cout << "������� ESC ��� ������";
	}
	void Print()//amount ����� ������ ������ ���� �� ������� ����������� ���������
	{
		while (push != 27)//��� ������ �� ���� ������ ESC
		{
			system("cls");
			NewMenu();
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
	menu1.SetValueCommands(n);//���������� ����� ������
	menu1.SetPosition("middle");//���������� ������������ ����
	for (int i = 1; i <= n; i++)//���� ����������� ������ �������
	{
		getline(cin, str);
		menu1.SetCommands(i, str);
	}
	menu1.Print();
	/*-------------------------------------------------------------*/
	/*-------------------------------------------------------------*/
	menu2.SetPosition("default");
	menu2.SetCommands(1, "����� ������");//������������ ������ ����
	menu2.SetCommands(2, "����� ������");
	menu2.SetCommands(3, "����� ������");
	menu2.Print();
}