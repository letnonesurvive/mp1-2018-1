#include <iostream>
#include <string>
#include <stdlib.h>
#include <cstdlib>

using namespace std;

class LongNumber
{
public:
	LongNumber() {}
	LongNumber(char *str)// онструктор данного вида принимает строку и записывает задом наперед дл€ удобства 
	{
		if (strlen(str) <= 20)
		{
			for (int i = 0, j = strlen(str) - 1; i < 20 && str[j] != '\0'; i++, j--)
			{
				arr[i] = str[j];
				//cout << arr[i];
			}
		}
	}
	LongNumber operator+(const LongNumber &num)// сложение реализовано методом "¬ столбик"
	{
		int r = 0;
		int temp1 = 0;
		LongNumber t1;
		for (int i = 0; i < 20; i++)
		{
			temp1 = atoi1(arr[i]) + (atoi1(num.arr[i])) + temp1;//результат сложени€ €чеек двух массивов
			r = temp1 % 10;//получаем остаток от числа при делениии на 10
			if (r < 0)//вдруг остаток будет отрицателет 
			{
				r = 10 + r;
				temp1 = temp1 - 10;
			}
			t1.arr[i] = itoa1(r);
			temp1 = temp1 / 10;
		}return t1;
	}
	LongNumber operator-(const LongNumber &num)//тот же самый способ что и со сложением
	{
		int r = 0;
		int temp1 = 0;
		LongNumber t1;
		for (int i = 0; i < 20; i++)
		{
			temp1 = atoi1(arr[i]) - (atoi1(num.arr[i])) + temp1;
			r = temp1 % 10;
			if (r < 0)
			{
				r = 10 + r;
				temp1 = temp1 - 10;
			}
			t1.arr[i] = itoa1(r);
			temp1 = temp1 / 10;
		}return t1;
	}
	LongNumber operator*(const LongNumber &num)
	{
		LongNumber t1;
		LongNumber t2;
		int	remnant1 = 0;//остаток дес€ток
		int	remnant2 = 0;//остаток единиц

		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20 - i; j++) {
				if (num.arr[i] == '0')//пропускаем нуль
					continue;
				remnant2 = atoi1(arr[j]) * atoi1(num.arr[i]);//получаем результат умножени€ 
				t1.arr[j + i] = itoa1((remnant2 += remnant1) % 10);//преобразывавает результат в массив
				remnant1 = remnant2 / 10;
			}
			t2 = t2 + t1;//исходный ответ
			t1 = "0";
		}
		return t2;
	}
	void print() //Ѕудет выводить результат если число не превышает 20 символов
	{
		if (!limit) {
			bool impact = false;
			for (int i = 0; i < 20; i++)
			{
				if (arr[19 - i] != '0')//без нулей 
					impact = true;
				if (impact)
					cout << arr[19 - i];

			}cout << endl;
		}
		else
			cout << "„исло слишком длинное" << endl;

	}
	bool operator==(const LongNumber &num)//равенство чисел
	{
		for (int i = 20; i >= 0; i--)// если массивы не равные будем возрващать false
		{
			if (atoi1(arr[i]) != atoi1(num.arr[i]))
				return false;
		}
	}
	LongNumber operator=(const LongNumber&num)//присваивание
	{
		for (int i = 0; i <= 20; i++)
			arr[i] = num.arr[i];
		return *this;
	}
	bool operator>(const LongNumber &num) //проверка на меньше, нужна дл€ делени€
	{
		for (int i = 20; i >= 0; i--)
		{

			if (atoi1(arr[i]) > atoi1(num.arr[i]))
				return true;
			if (atoi1(arr[i]) <atoi1(num.arr[i]))
				return false;
		}
		return false;//есди числа равны
	}
	bool operator<(const LongNumber &num) //проверка на больше, нужна дл€ делени€
	{
		for (int i = 20; i >= 0; i--)
		{
			if (atoi1(arr[i]) <atoi1(num.arr[i]))
				return true;
			if (atoi1(arr[i]) > atoi1(num.arr[i]))
				return false;
		}
		return false;
	}
private:
	char arr[20];
	bool  limit = false;
	int atoi1(char elem1)//функци€ мен€ет тип char на int(atoi не подходит так как не работает от массивов)
	{
		switch (elem1)
		{
		case '1': return 1;
		case '2': return 2;
		case '3': return 3;
		case '4': return 4;
		case '5': return 5;
		case '6': return 6;
		case '7': return 7;
		case '8': return 8;
		case '9': return 9;
		default:  return 0;
		}
	}
	char itoa1(int elem2) //функци€ мен€ет тип int на char
	{
		switch (elem2)
		{
		case 1: return '1';
		case 2: return '2';
		case 3: return '3';
		case 4: return '4';
		case 5: return '5';
		case 6: return '6';
		case 7: return '7';
		case 8: return '8';
		case 9: return '9';
		default:return '0';
		}
	}
};
void main()
{
	LongNumber a("11111111111111");
	LongNumber b("2222222222");
	LongNumber c = a*b;
	LongNumber d = a + b;
	LongNumber k = a - b;
	c.print();
	d.print();
	k.print();
}
