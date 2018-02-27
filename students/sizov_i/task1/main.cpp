#include <iostream>
#include <string>
#include <stdlib.h>
#include <cstdlib>
#include <locale>
using namespace std;

class LongNumber
{
public:
	LongNumber()
	{
		basis();
	}
	LongNumber(char *str)//Конструктор данного вида принимает строку и записывает задом наперед для удобства 
	{
		basis();
		if (strlen(str) <= 20)
		{
			for (int i = 0, j = strlen(str) - 1; i < 20 && str[j] != '\0'; i++, j--)
			{
				arr[i] = str[j];
				//cout << arr[i];
			}
		}
	}
	LongNumber operator+(const LongNumber &cons)// сложение реализовано методом "В столбик"
	{
		int r = 0;
		int temp1 = 0;
		LongNumber t1;
		for (int i = 0; i < 20; i++)
		{
			temp1 = atoi1(arr[i]) + (atoi1(cons.arr[i])) + temp1;//результат сложения ячеек двух массивов
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
	LongNumber operator-(const LongNumber &cons)//тот же самый способ что и со сложением
	{
		int r = 0;
		int temp1 = 0;
		LongNumber t1;
		for (int i = 0; i < 20; i++)
		{
			temp1 = atoi1(arr[i]) - (atoi1(cons.arr[i])) + temp1;
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
	LongNumber operator*(const LongNumber &cons)
	{
		LongNumber t1;
		LongNumber t2;
		int	remnant1 = 0;//остаток десяток
		int	remnant2 = 0;//остаток единиц

		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20 - i; j++) {
				if (cons.arr[i] == '0')//пропускаем нуль
					continue;
				remnant2 = atoi1(arr[j]) * atoi1(cons.arr[i]);//получаем результат умножения 
				t1.arr[j + i] = itoa1((remnant2 += remnant1) % 10);//преобразывавает результат в массив
				remnant1 = remnant2 / 10;
			}
			t2 = t2 + t1;//исходный ответ
			t1 = "0";
		}
		return t2;
	}
	LongNumber operator/(const LongNumber &cons)
	{
		bool start = false;
		int j = 20;
		LongNumber answer;
		LongNumber dividendPart;
		LongNumber divider(cons);// Делитель
		LongNumber dividend(*this);// Делимое
		if (divider == (LongNumber)"0")
		{
			throw "Деление на ноль";
			return 0;
		}
		do
		{
			while (dividendPart < divider && (j--) > 0)
			{
				dividendPart.rank();
				dividendPart.arr[0] = dividend.arr[j];
				if (dividend.arr[j] != '0')
					start = true;
				if (dividendPart < divider && start && j > 0)
					answer.rank();
			}
			while (dividendPart >= divider)
			{
				dividendPart = dividendPart - divider;
				answer = answer + "1";
			}
			if (j <= 0)
				break;
			answer.rank();
		} while (j > 0);
		return answer;
	}
	LongNumber operator%(const LongNumber &cons)
	{
		bool start = false;
		int j = 20;
		LongNumber answer;
		LongNumber dividendPart;
		LongNumber divider(cons);// Делитель
		LongNumber dividend(*this);// Делимое
		if (divider == (LongNumber)"0")
		{
			throw "Деление на ноль";
			return 0;
		}
		do
		{
			while (dividendPart < divider && j-- > 0)
			{
				dividendPart.rank();
				dividendPart.arr[0] = dividend.arr[j];
				if (dividend.arr[j] != '0')
					start = true;
				if (dividendPart < divider && start && j > 0)
					answer.rank();
			}
			while (dividendPart >= divider)
			{
				dividendPart = dividendPart - divider;
				answer = answer + "1";
			}
			if (j <= 0)
				break;
			answer.rank();
		} while (j > 0);
		answer = (*this) - answer* cons;//остаток
		return answer;
	}
	LongNumber& operator=(const LongNumber&cons)//присваивание
	{
		for (int i = 0; i <= 20; i++)
			arr[i] = cons.arr[i];
		return *this;
	}
	bool operator==(const LongNumber &cons)//равенство чисел
	{
		for (int i = 20; i >= 0; i--)// если массивы не равные будем возрващать false
		{
			if (atoi1(arr[i]) != atoi1(cons.arr[i]))
				return false;
		}
		return true;
	}
	bool operator>(const LongNumber &cons) //проверка на меньше, нужна для деления
	{
		for (int i = 20; i >= 0; i--)
		{

			if (atoi1(arr[i]) > atoi1(cons.arr[i]))
				return true;
			if (atoi1(arr[i]) <atoi1(cons.arr[i]))
				return false;
		}
		return false;//если числа равны
	}
	bool operator>=(const LongNumber &cons)
	{
		for (int i = 20; i >= 0; i--) {

			if (atoi1(arr[i]) > atoi1(cons.arr[i]))
				return true;
			if (atoi1(arr[i]) <atoi1(cons.arr[i]))
				return false;
		}
	}
	bool operator<(const LongNumber &cons) //проверка на больше, нужна для деления
	{
		for (int i = 20; i >= 0; i--)
		{
			if (atoi1(arr[i]) <atoi1(cons.arr[i]))
				return true;
			if (atoi1(arr[i]) > atoi1(cons.arr[i]))
				return false;
		}
		return false;
	}
	void print() //Будет выводить результат если число не превышает 20 символов
	{
		bool impact = false;
		if (!limit)
		{
			for (int i = 0; i < 20; i++)
			{
				if (arr[19 - i] != '0')//без нулей 
					impact = true;
				if (impact)
					cout << arr[19 - i];
			}cout << endl;
		}
		if (!impact)
		{
			cout << "0" << endl;
		}
	}
private:
	char arr[20];
	bool  limit = false;
	void basis()
	{
		for (char i = 0; i < 20; i++)
			arr[i] = '0';
	}
	int atoi1(char elem1)//функция меняет тип char на int(atoi не подходит так как не работает от массивов)
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
	char itoa1(int elem2) //функция меняет тип int на char
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
	void rank()
	{
		bool minus = limit;
		for (int i = 20; i > 0; i--)
			arr[i] = arr[i - 1];
		arr[0] = '0';
		limit = minus;
	}
};
void main()
{
	setlocale(LC_ALL, "Rus");
	LongNumber a("5");
	LongNumber b("25");
	LongNumber c = a*b;//true 
	LongNumber d = a + b;//true
	LongNumber k = a - b;//true
	LongNumber g = a / b;
	LongNumber l = a%b;
	/*LongNumber k1("25");
	LongNumber k2("5");
	LongNumber k3 = k1 / k2;
	k3.print();*/
	g.print();
	//c.print();
	//g.print();
	//l.print();
}