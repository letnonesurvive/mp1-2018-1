#include <iostream>
#include <cstdlib>
#include <ctime> 
#include <cmath>
using namespace std;

class Vector
{
private:
	int *arr = new int[20];//создание динамического массива
	int dim = 0;
	int n;
public:
	Vector(int _dim = 0)
	{
		SetDim(10);//поменяйте размерность в случае необходимости 
	}
	Vector(char str[])//конструктор как пример работы класса
	{
		dim = 10; ;//задаем размерность внутри кода вручную
		if (dim <= 20)
		{
			srand(atoi(str));
			for (int i = 0; i < dim; i++)
			{
				arr[i] = 1 + rand() % 30;
			}
		}
		else throw;
	}
	Vector operator=(const Vector &num)
	{
		if (this == &num)
			return *this;
		else
			if (dim != num.dim)
			{
				delete[]arr;
				arr = new int[num.dim + 1];
			}
		arr = num.arr;
		dim = num.dim;
		return *this;
	}
	void SetDim(int _dim)//устанавливаем размерность
	{
		dim = _dim;
		int i;
		for (i = 0; i < _dim; i++)//цикл забивает нулями массив, в зависиммости от ввода размерности
		{
			arr[i] = 0;
		}

	}
	int *SetComponentVectors()
	{
		int a;
		cin >> n;//ввод номера ячейки
		if (n - 1 >= dim)
		{
			throw;
		}
		cin >> a;//ввод значения компоненты
		if (n - 1 < dim)
			arr[n - 1] = a;
		return arr;
	}
	int GetComponentVectors()//узнать значение компоненты по номеру
	{
		cin >> n;
		if (n > dim)
			throw;
		return arr[n - 1];
	}
	double LengthOfVector()//высчитывает длинну вектора
	{
		double temp = 0;
		double b = 0;
		for (int i = 0; i < dim; i++)
			temp = arr[i] * arr[i] + temp;
		b = sqrt(temp);
		return b;
	}
	Vector operator+(const Vector other)
	{
		int v = 0;
		Vector tmp(v);
		if (dim != other.dim)
			throw;
		for (int i = 0; i < dim; i++)
			tmp.arr[i] = arr[i] + other.arr[i];
		return tmp;
	}
	int Scalar(Vector v)//скалярное проивзедение 
	{
		if (dim != v.dim);
		int tmp = 0;
		for (int i = 0; i < dim; i++)
			tmp = tmp + arr[i] * v.arr[i];
		return tmp;
	}
	void ReturnScalar(Vector v)
	{
		cout << Scalar(v);
	}
	void ReturnARR()//выписывает массив с компонентами
	{
		for (int i = 0; i < dim; i++)
			cout << "|" << arr[i] << "|";
	}
	void GetLengthOfVector()
	{
		cout << (int)LengthOfVector();
	}
	void PrintComponent()//выводит на экран значение ячейки
	{
		cout << GetComponentVectors() << endl;
	}
	int GetDim()//возвращает размерность
	{
		return  dim;
	}
	void PrintDim()//выводит размерность на экран
	{
		cout << GetDim();
	}
};
void DimenstionEntry(int *_dim)//это своего рода ввод размерности, после этой функции идет функция SetDim которая задает размерность вектора(размер массива)
{
	cout << "Enter dimenstion" << endl;
	cin >> *_dim;
}
void main()
{
	setlocale(LC_ALL, "rus");
	int v = 0;
	Vector f1("39");//вектора с рандомными компонентами
	Vector k("289");
	Vector l(v);//нулевой вектор
	f1.ReturnARR();
	cout << "Размерность = "; f1.PrintDim(); cout << endl;
	cout << "Узнайте значение компоненты по номеру,введите номер" << endl;
	f1.PrintComponent();
	cout << "Чтобы задать компоненту вектора, сначала введите номер, а затем значение" << endl;
	cout << endl;
	f1.SetComponentVectors(); f1.ReturnARR(); cout << endl; cout << "Вы задали компоненту" << endl;
	cout << endl;
	cout << "Длинна вектора = "; f1.GetLengthOfVector();
	cout << endl; cout << endl;
	k.ReturnARR();
	cout << endl; cout << endl;
	cout << "Скалярное произведение = "; f1.ReturnScalar(k);
	l = f1 + k;
	cout << endl; cout << endl;
	cout << "Сумма векторов = "; l.ReturnARR();
	system("pause");
}