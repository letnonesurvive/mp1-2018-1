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
		SetDim(10);//помен€йте размерность в случае необходимости 
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
		for (i = 0; i < _dim; i++)//цикл забивает нул€ми массив, в зависиммости от ввода размерности
		{
			arr[i] = 0;
		}

	}
	int *SetComponentVectors()
	{
		int a;
		cin >> n;//ввод номера €чейки
		if (n - 1 >= dim)
		{
			throw;
		}
		cin >> a;//ввод значени€ компоненты
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
	int Scalar(Vector v)//скал€рное проивзедение 
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
	void PrintComponent()//выводит на экран значение €чейки
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
void DimenstionEntry(int *_dim)//это своего рода ввод размерности, после этой функции идет функци€ SetDim котора€ задает размерность вектора(размер массива)
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
	cout << "–азмерность = "; f1.PrintDim(); cout << endl;
	cout << "”знайте значение компоненты по номеру,введите номер" << endl;
	f1.PrintComponent();
	cout << "„тобы задать компоненту вектора, сначала введите номер, а затем значение" << endl;
	cout << endl;
	f1.SetComponentVectors(); f1.ReturnARR(); cout << endl; cout << "¬ы задали компоненту" << endl;
	cout << endl;
	cout << "ƒлинна вектора = "; f1.GetLengthOfVector();
	cout << endl; cout << endl;
	k.ReturnARR();
	cout << endl; cout << endl;
	cout << "—кал€рное произведение = "; f1.ReturnScalar(k);
	l = f1 + k;
	cout << endl; cout << endl;
	cout << "—умма векторов = "; l.ReturnARR();
	system("pause");
}