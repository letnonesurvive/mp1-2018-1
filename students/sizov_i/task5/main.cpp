#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <windows.h>
using namespace std;

int set_day;//установка даты в программе
int set_month;
int set_year;
void SetDate(int _day, int _month, int _year)
{
	set_day = _day;
	set_month = _month;
	set_year = _year;
}
struct deposit
{
	unsigned long long int SumRange;//диапазон начальной суммы депозита
	double pcent;//процент по вкладу, вычисляется по сумме и срок
	string time;
	bool status;//проверка открыт или закрыт депозит
    int day;//дата открытия депозита
	int month;
	int year;
	int endday;//дата закрытия депозита
	int endmonth;
	int endyear;
};
ostream& operator<<(ostream &os, const deposit dep)
{
	os << "Сумма вклада по депозиту:" << dep.SumRange << " " << "Ваш процент по вкладу:" << dep.pcent << " " << "Срок открытия:" << dep.time << endl << endl;
	os << "Дата открытия депозита:" << dep.day << " " << dep.month << " " << dep.year << endl;
	os << "Дата закрытия депозита:" << dep.endday << " " << dep.endmonth << " " << dep.endyear;
	return os;
}
struct Client
{
	unsigned int AccountNum;//номер аккаунта
	string pass;//пароль
	string initials;//фио
	unsigned long long int SallaryAcc;//сумма зарплатного счета
	deposit Deposit;//информация о депозите
};
ostream& operator<<(ostream &os, const Client &client)
{
	os << "Номер счета:" << client.AccountNum << "\n" << "ФИО:" << client.initials << "\n" << "Сумма на зарплатном счете:" << client.SallaryAcc << "руб."; /*<< "Состояние депозита:" << client.Deposit*/
	return os;
}
class ProcessingCentr
{
private:
	vector<Client>base;
public:
	Client AddClient(Client tmp)
	{
		if (tmp.pass.length() > 3 && (tmp.AccountNum < 10000 && tmp.AccountNum>0))
		{
			base.push_back(tmp);
			return tmp;
		}
		if (tmp.pass.length() <= 3)
		{
			cout << "Пароль должен состоять из более трех символов";
			throw;
		}
		if (tmp.AccountNum > 9999 || tmp.AccountNum <= 0)
		{
			cout << "Неверно указан номер счета";
			throw;
		}
	}
	friend ostream& operator<<(ostream &os, const ProcessingCentr &tmp);
	friend class Bank;
};
ostream& operator<<(ostream &os, const ProcessingCentr &tmp)
{
	for (size_t i = 0; i < tmp.base.size(); i++)
	{
		os << tmp.base[i] << endl;
	}
	return os;
}
class Bank
{
private:
	ProcessingCentr box;
	Client clt = {};
	bool login = false;//проверка на вход
	bool end = false;//проверка был закрты депозит или нет
	unsigned long long int savings;//накопления по депозиту
	string srok[5] = { "3 месяца","6 месяцев","1 год","2 года","3 года" };//массивы с основной информацией 
	double percent[20] = { 4.05, 4.65, 4.8, 5.0, 5.3, 4.15, 4.71, 4.83, 5.1, 5.4, 4.18, 4.75, 4.88, 5.2, 5.4, 4.25, 4.77, 4.95, 5.35, 6.11 };
	unsigned long long int sum[3] = { 100000,500000,1000000 };
	void rewrite(Client tmp)//перезапись и сохранение изменений клиента
	{
		for (size_t i = 0; i < box.base.size(); i++)
		{
			if (tmp.AccountNum == box.base[i].AccountNum&&tmp.pass == box.base[i].pass)
				box.base[i] = tmp;
		}
	}
	unsigned long long int Calculation()//вычисления накопленых процентов 
	{
		unsigned int tmpmonth = 0;//колличество прошедших месяцев с момента открытия депозита по установленную дату
		if (set_day >= clt.Deposit.day)
		{
			if (set_year <= clt.Deposit.endyear)
				tmpmonth = (set_month - clt.Deposit.month) + 12 * (set_year - clt.Deposit.year);//высчитываем сколько всего месяцев прошло с момента открытия депозита до момента входа в систему
			if (set_year == clt.Deposit.endyear && set_month >= clt.Deposit.endmonth)
				tmpmonth = (clt.Deposit.endmonth - clt.Deposit.month) + 12 * (clt.Deposit.endyear - clt.Deposit.year);
			if (set_year > clt.Deposit.endyear)
				tmpmonth = (clt.Deposit.endmonth - clt.Deposit.month) + 12 * (clt.Deposit.endyear - clt.Deposit.year);
		}
		if (set_day < clt.Deposit.day)
		{
			if (set_year <= clt.Deposit.endyear)
				tmpmonth = (set_month - clt.Deposit.month) + 12 * (set_year - clt.Deposit.year) - 1;
			if (set_year == clt.Deposit.endyear && set_month >= clt.Deposit.endmonth)
				tmpmonth = (clt.Deposit.endmonth - clt.Deposit.month) + 12 * (clt.Deposit.endyear - clt.Deposit.year);
			if (set_year > clt.Deposit.endyear)
				tmpmonth = (clt.Deposit.endmonth - clt.Deposit.month) + 12 * (clt.Deposit.endyear - clt.Deposit.year);
		}
		savings = unsigned long long int(clt.Deposit.SumRange*tmpmonth*clt.Deposit.pcent / 12 / 100);
		return savings;
	}
public:
	Bank(ProcessingCentr _box)
	{
		box = _box;
	};
	Client SignIn(unsigned int account, string str)//войти в систему
	{
		for (size_t i = 0; i < box.base.size(); i++)
		{
			if (box.base[i].AccountNum == account&&box.base[i].pass == str)
			{
				clt = box.base[i];
				login = true;
				return clt;
				//cout << clt<< endl<< endl;
			}
			if (box.base[i].AccountNum != account || box.base[i].pass != str)
			{
				cout << "Неправильно введен номер или пароль" << endl;
				throw;
			}
		}
	}
	void ShowAvaiDeposits()//показать доступные депозиты
	{
		if (login)
		{
			if (clt.Deposit.status)
			{
				cout << "У Вас уже открыт депозит" << endl;
				return;
			}
			cout << "Вам доступны следующие депозиты" << endl;
			cout << "(слева указан срок, справа процентная ставка)" << endl << endl;
			if (clt.SallaryAcc < sum[0])
			{
				cout << "На сумму менее " << sum[0] << endl;
				for (int i = 0; i < 5; i++)
				{
					cout << srok[i] << ":" << percent[i] << endl;
				}
			}
			if (clt.SallaryAcc >= sum[0] && clt.SallaryAcc < sum[1])
			{
				int i = 0;
				int j = 0;
				int k = 0;
				cout << "На сумму менее " << sum[k] << endl;
				for (i, j; i < 10; i++, j++)
				{
					if (j > 4)
					{
						j = 0;
						cout << "На сумму от " << sum[k] << " до " << sum[k + 1] << endl;
						k++;
						cout << endl;
					}
					cout << srok[j];
					cout << ":" << percent[i] << endl;
				}
			}
			if (clt.SallaryAcc >= sum[1] && clt.SallaryAcc < sum[2])
			{
				int i = 0;
				int j = 0;
				int k = 0;
				cout << "На сумму менее " << sum[k] << endl;
				for (i, j; i < 15; i++, j++)
				{
					if (j > 4)
					{
						j = 0;
						cout << "На сумму от " << sum[k] << " до " << sum[k + 1] << endl;
						k++;
						cout << endl;
					}
					cout << srok[j];
					cout << ":" << percent[i] << endl;
				}
			}
			if (clt.SallaryAcc >= sum[2])
			{
				int i = 0;
				int j = 0;
				int k = 0;
				cout << "На сумму менее " << sum[k] << endl;
				for (i, j; i < 20; i++, j++)
				{
					if (j > 4)
					{
						cout << endl;
						j = 0;
						if (k == 2)
							cout << "На сумму более " << sum[k] << endl;
						else cout << "На сумму от " << sum[k] << " до " << sum[k + 1] << endl;
						k++;
					}
					cout << srok[j];
					cout << ":" << percent[i] << endl;
				}
			}
		}
		else cout << "Войдите в систему" << endl;
	}
	void OpenDeposit(unsigned long long int money, string time)
	{
		if (login)
		{
			deposit dep = {};
			if (clt.Deposit.status)
				cout << "На вашем счете уже открыт депозит" << endl;
			if (clt.SallaryAcc >= money)
			{
				if (money < sum[0])
				{
					for (int i = 0; i < 5; i++)
						if (srok[i] == time)
							dep.pcent = percent[i];
				}
				if (money >= sum[0] && money < sum[1])
				{
					int i = 5;
					int j = 0;
					for (i, j; i < 10; i++, j++)
						if (srok[j] == time)
							dep.pcent = percent[i];
				}
				if (money >= sum[1] && money < sum[2])
				{

					int i = 10;
					int j = 0;
					for (i, j; i < 15; i++, j++)
						if (srok[j] == time)
							dep.pcent = percent[i];
				}
				if (money >= sum[2])
				{
					int i = 15;
					int j = 0;
					for (i, j; i < 20; i++, j++)
						if (srok[j] == time)
							dep.pcent = percent[i];
				}
				clt.SallaryAcc -= money;
				dep.SumRange = money;
				dep.status = true;
				dep.day = set_day;
				dep.month = set_month;
				dep.year = set_year;
				dep.endday = set_day;
				dep.endmonth = set_month;
				dep.endyear = set_year;
				if (time == "3 месяца")
				{
					dep.endmonth += 3;
					if (dep.endmonth > 12)
					{
						dep.endmonth %= 12;
						dep.endyear++;
					}
				}
				if (time == "6 месяцев")
				{
					dep.endmonth += 6;
					if (dep.endmonth > 12)
					{
						dep.endmonth %= 12;
						dep.endyear++;
					}
				}
				if (time == "1 год")
					dep.endyear++;
				if (time == "2 года")
					dep.endyear += 2;
				if (time == "3 года")
					dep.endyear += 3;
				dep.time = time;
				clt.Deposit = dep;
				rewrite(clt);
				end = false;
			}
			else cout << "Сумма депозита больше вашего зарплатного счета" << endl;
		}
		else cout << "Войдите в систему" << endl;
	}
	void StateDep()//показать открыт депозит или нет
	{
		if (login)
		{
			if (clt.Deposit.status)
				cout << "На вашем счете открыт депозит:" << endl;
			else
				cout << "У вас нет открытых депозитов" << endl;
		}
		else cout << "Войдите в систему" << endl;
	}
	void ShowStatusOfDeposit()//показать состояние депозита
	{
		if (login)
		{
			if (clt.Deposit.status)
			{
				Calculation();
				cout << clt.Deposit << endl;
				cout << "Ваши накопления составляют:" << savings << endl;
			}
			if (end)
			{
				cout << "Ваш последний депозит был закрыт" << endl;
			}
		}
		else cout << "Войдите в систему" << endl;
	}
	void GetPercent()//6) снять проценты (переведя их на зарплатный счет клиента)
	{
		if (login)
		{
			Calculation();
			clt.SallaryAcc += savings;
			savings = 0;
			rewrite(clt);
		}
		else cout << "Войдите в систему" << endl;
	}
	void CloseDeposit()
	{
		if (login)
		{
			if (set_year > clt.Deposit.endyear)
			{
				clt.SallaryAcc += clt.Deposit.SumRange + savings;
				clt.Deposit = {};
				savings = 0;
				rewrite(clt);
				cout << "Ваш депозит был закрыт" << endl;
				end = true;
				return;
			}
			if (set_year == clt.Deposit.endyear&&set_month >= clt.Deposit.endmonth)
			{
				if (set_month == clt.Deposit.endmonth&&set_day >= clt.Deposit.endday)
				{
					clt.SallaryAcc += clt.Deposit.SumRange + savings;
					clt.Deposit = {};
					savings = 0;
					rewrite(clt);
					cout << "Ваш депозит был закрыт" << endl;
					end = true;
					return;
				}
				if (set_month > clt.Deposit.endmonth)
				{
					clt.SallaryAcc += clt.Deposit.SumRange + savings;
					clt.Deposit = {};
					savings = 0;
					rewrite(clt);
					cout << "Ваш депозит был закрыт" << endl;
					end = true;
					return;
				}
				if (set_month == clt.Deposit.endmonth&&set_day < clt.Deposit.endday)
					cout << "Депозит может быть закрыт только по оканчанию срока" << endl;
			}
			if ((set_year < clt.Deposit.endyear) || (set_year == clt.Deposit.endyear&&set_year < clt.Deposit.endyear))
				cout << "Депозит может быть закрыт только по оканчанию срока" << endl;
		}
		else cout << "Войдите в систему" << endl;
	}
	friend ostream& operator<<(ostream &os, const ProcessingCentr &tmp);
	friend class ProcessingCentr;

};
void main()
{
	setlocale(LC_ALL, "rus");
	SYSTEMTIME st;
	GetLocalTime(&st);
	Client one = { 8523,"password","Иванов Александр Евгеньевич",1005000, };
	char password[256];
	int num, i, push = 0;
	int day, month, year;
	ProcessingCentr centr;
	centr.AddClient(one);
	Bank network(centr);
	/*---------------------------------------------------------------*/
	cout << "Введите логин" << endl;
	cin >> num;
	cout << "Введите пароль" << endl;
	for (i = 0; (password[i] = _getch()) != '\r';)
	{
		if (password[i] == '\b' && i != 0)
		{
			cout << "\b \b";
			i--;
		}
		else if (password[i] != '\b')
		{
			cout << '*';
			i++;
		}
	}
	password[i] = '\0';
	network.SignIn(num, string(password));
	SetDate(st.wDay, st.wMonth, st.wYear);
	system("cls");
	while (_getch())
	{
		cout << "Дата:" << ::set_day << " " << ::set_month << " " << ::set_year << endl << endl;
		cout << network.SignIn(num, string(password)) << endl << endl;
		cout << "Для просмотра доступных депозитов нажмите 1" << endl;
		cout << "Для установки депозита нажмите 2" << endl;
		cout << "Закрыть депозит (может быть закрыт только по окончанию срока) нажмите 3" << endl;
		cout << "Показать наличие открытого депозита нажмите 4" << endl;
		cout << "Узнать состояние депозита нажмите 5" << endl;
		cout << "Cнять проценты (переведя их на зарплатный счет клиента) нажмите 6" << endl;
		cout << "Установить дату (для демонстрации работы программы) нажмите 7" << endl;
		cin >> push;
		switch (push)
		{
		case 1:
		{
			system("cls");
			network.ShowAvaiDeposits();
			cout << endl;
			break;
		}
		case 2:
		{
			system("cls");
			int button = 0;
			unsigned long long int am;
			string str;
			cout << "Выберете срок депозита" << endl;
			cout << "1) 3 месяца" << endl;
			cout << "2) 6 месяцев" << endl;
			cout << "3) 1 года" << endl;
			cout << "4) 2 года" << endl;
			cout << "5) 3 года" << endl;
			cin >> button;
			switch (button)
			{
			case 1:
			{
				str = "3 месяца";
				break;
			}
			case 2:
			{
				str = "6 месяцев";
				break;
			}
			case 3:
			{
				str = "1 год";
				break;
			}
			case 4:
			{
				str = "2 года";
				break;
			}
			case 5:
			{
				str = "3 года";
				break;
			}
			default:
			{
				cout << "Неверное значение" << endl;
				break;
			}
			}
			cout << "Введите сумму" << endl;
			cin >> am;
			network.OpenDeposit(am, str);
			break;
		}
		case 3:
		{
			system("cls");
			network.CloseDeposit();
			break;
		}
		case 4:
		{
			system("cls");
			network.StateDep();
			break;
		}
		case 5:
		{
			system("cls");
			network.ShowStatusOfDeposit();
			break;
		}
		case 6:
		{
			system("cls");
			network.GetPercent();
			break;
		}
		case 7:
		{
			system("cls");
			cout << "Введите дату в формате день месяц год" << endl;
			cin >> day;
			cin >> month;
			cin >> year;
			SetDate(day, month, year);
			break;
		}
		default:
		{
			cout << "Неверное значение" << endl;
			break;
		}
		}
	}
	system("pause");
}