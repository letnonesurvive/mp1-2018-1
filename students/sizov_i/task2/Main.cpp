#include <iostream>
#include <cstdlib>
#include <ctime> 
#include <cmath>
using namespace std;

class Vector
{
private:
	int *arr = new int[20];//�������� ������������� �������
	int dim = 0;
	int n;
public:
	Vector(int _dim = 0)
	{
		SetDim(10);//��������� ����������� � ������ ������������� 
	}
	Vector(char str[])//����������� ��� ������ ������ ������
	{
		dim = 10; ;//������ ����������� ������ ���� �������
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
	void SetDim(int _dim)//������������� �����������
	{
		dim = _dim;
		int i;
		for (i = 0; i < _dim; i++)//���� �������� ������ ������, � ������������ �� ����� �����������
		{
			arr[i] = 0;
		}

	}
	int *SetComponentVectors()
	{
		int a;
		cin >> n;//���� ������ ������
		if (n - 1 >= dim)
		{
			throw;
		}
		cin >> a;//���� �������� ����������
		if (n - 1 < dim)
			arr[n - 1] = a;
		return arr;
	}
	int GetComponentVectors()//������ �������� ���������� �� ������
	{
		cin >> n;
		if (n > dim)
			throw;
		return arr[n - 1];
	}
	double LengthOfVector()//����������� ������ �������
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
	int Scalar(Vector v)//��������� ������������ 
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
	void ReturnARR()//���������� ������ � ������������
	{
		for (int i = 0; i < dim; i++)
			cout << "|" << arr[i] << "|";
	}
	void GetLengthOfVector()
	{
		cout << (int)LengthOfVector();
	}
	void PrintComponent()//������� �� ����� �������� ������
	{
		cout << GetComponentVectors() << endl;
	}
	int GetDim()//���������� �����������
	{
		return  dim;
	}
	void PrintDim()//������� ����������� �� �����
	{
		cout << GetDim();
	}
};
void DimenstionEntry(int *_dim)//��� ������ ���� ���� �����������, ����� ���� ������� ���� ������� SetDim ������� ������ ����������� �������(������ �������)
{
	cout << "Enter dimenstion" << endl;
	cin >> *_dim;
}
void main()
{
	setlocale(LC_ALL, "rus");
	int v = 0;
	Vector f1("39");//������� � ���������� ������������
	Vector k("289");
	Vector l(v);//������� ������
	f1.ReturnARR();
	cout << "����������� = "; f1.PrintDim(); cout << endl;
	cout << "������� �������� ���������� �� ������,������� �����" << endl;
	f1.PrintComponent();
	cout << "����� ������ ���������� �������, ������� ������� �����, � ����� ��������" << endl;
	cout << endl;
	f1.SetComponentVectors(); f1.ReturnARR(); cout << endl; cout << "�� ������ ����������" << endl;
	cout << endl;
	cout << "������ ������� = "; f1.GetLengthOfVector();
	cout << endl; cout << endl;
	k.ReturnARR();
	cout << endl; cout << endl;
	cout << "��������� ������������ = "; f1.ReturnScalar(k);
	l = f1 + k;
	cout << endl; cout << endl;
	cout << "����� �������� = "; l.ReturnARR();
	system("pause");
}