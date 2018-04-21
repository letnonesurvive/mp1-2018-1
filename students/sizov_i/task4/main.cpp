#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
using namespace std;

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
	os << "Сумма вклада по депозиту:" << dep.SumRange << " " << "Ваш процент по вкладу:" << dep.pcent << " " << "Срок открытия:" << dep.time;
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
	int set_day;//установка даты в программе
	int set_month;
	int set_year;
	bool login = false;//проверка на вход
	unsigned long long int savings;//накопления по депозиту
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
		int tmpmonth = 0;//колличество прошедших месяцев с момента открытия депозита по установленную дату
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
	void SetDate(int _day, int _month, int _year)// устанавливаем дату для работы с программой 
	{
		set_day = _day;
		set_month = _month;
		set_year = _year;
		Calculation();//когда устанавливаем дату, то и происходит вычисления процентов
	}
	void SignIn(unsigned int account, string str)//войти в систему
	{
		for (size_t i = 0; i < box.base.size(); i++)
		{
			if (box.base[i].AccountNum == account&&box.base[i].pass == str)
			{
				clt = box.base[i];
				login = true;
				cout << clt << endl;
			}
			if (box.base[i].AccountNum != account || box.base[i].pass != str)
			{
				cout << "Неправильно введен номер или пароль" << endl;
			}
		}
	}
	void ShowAvaiDeposits()//показать доступные депозиты
	{
		if (login)
		{
			string srok[5] = { "3 месяца","6 месяцев","1 год","2 года","3 года" };
			double per[20] = { 5.4,4.8,9.3,8.1,7.5 };
			unsigned long long int sum[3] = { 100000,500000,1000000 };
			if (clt.SallaryAcc < sum[0])
			{
				for (int i = 0; i < 5; i++)
				{
					cout << srok[i] << ":" << per[i] << endl;
				}
			}
			if (clt.SallaryAcc >= sum[0] && clt.SallaryAcc <= sum[1])
			{
				int i = 0;
				int j = 0;
				for ( i ,j ; i < 10,j < 10; i++, j++)
				{
					if (j == 5)
						j = 0;
					 cout << srok[j];
					 cout<< ":" << per[i] << endl;
				}
			}
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
				cout << "У вас не открыт ни один депозит:" << endl;
		}
		else cout << "Войдите в систему" << endl;
	}
	void ShowStatusOfDeposit()//показать состояние депозита
	{
		if (login)
		{
			if (clt.Deposit.status)
			{
				cout << clt.Deposit << endl;
				cout << "Ваши накопления составляют:" << savings << endl;
			}
			if (!clt.Deposit.status)
			{
				cout << "На вашем счете нет открытых депозитов" << endl;
			}
		}
		else cout << "Войдите в систему" << endl;
	}
	void OpenDeposit(unsigned long long int sum, string srok)//открыть депозит
	{
		if (login)
		{
			if (clt.SallaryAcc >= sum)
			{
				if (!clt.Deposit.status)
				{
					deposit dep = {};
					double percent;
					int tmpendd;
					int tmpendm;
					int tmpendy;
					if (sum <= 100000)
					{
						if (srok == "3 месяца")
							percent = 4.05;
						if (srok == "6 месяцев")
							percent = 4.65;
						if (srok == "1 год")
							percent = 4.8;
						if (srok == "2 года")
							percent = 5.0;
						if (srok == "3 года")
							percent = 5.3;
					}
					if (sum > 100000 && sum <= 500000)
					{
						if (srok == "3 месяца")
							percent = 4.15;
						if (srok == "6 месяцев")
							percent = 4.71;
						if (srok == "1 год")
							percent = 4.83;
						if (srok == "2 года")
							percent = 5.1;
						if (srok == "3 года")
							percent = 5.4;
					}
					if (sum> 500000 && sum <= 1000000)
					{
						if (srok == "3 месяца")
							percent = 4.18;
						if (srok == "6 месяцев")
							percent = 4.75;
						if (srok == "1 год")
							percent = 4.88;
						if (srok == "2 года")
							percent = 5.2;
						if (srok == "3 года")
							percent = 5.4;
					}
					if (sum > 1000000)
					{
						if (srok == "3 месяца")
							percent = 4.25;
						if (srok == "6 месяцев")
							percent = 4.77;
						if (srok == "1 год")
							percent = 4.95;
						if (srok == "2 года")
							percent = 5.35;
						if (srok == "3 года")
							percent = 6.11;;
					}
					if (srok == "3 месяца")
					{
						tmpendd = set_day;
						tmpendm = set_month + 3;
						tmpendy = set_year;
						if (tmpendm > 12)
						{
							tmpendm = tmpendm % 12;
							tmpendy++;
						}
					}
					if (srok == "6 месяцев")
					{
						tmpendd = set_day;
						tmpendm = set_month + 6;
						tmpendy = set_year;
						if (tmpendm > 12)
						{
							tmpendm = tmpendm % 12;
							tmpendy++;
						}
					}
					if (srok == "1 год")
					{
						tmpendd = set_day;
						tmpendm = set_month;
						tmpendy = set_year + 1;
					}
					if (srok == "2 года")
					{
						tmpendd = set_day;
						tmpendm = set_month;
						tmpendy = set_year + 2;
					}
					if (srok == "3 года")
					{
						tmpendd = set_day;
						tmpendm = set_month;
						tmpendy = set_year + 3;
					}
					dep.day = set_day;
					dep.month = set_month;
					dep.year = set_year;
					dep.endday = tmpendd;
					dep.endmonth = tmpendm;
					dep.endyear = tmpendy;
					dep.SumRange = sum;
					dep.pcent = percent;
					dep.time = srok;
					dep.status=true;
					clt.Deposit = dep;
					clt.SallaryAcc -= sum;
					rewrite(clt);
				}
				else cout << "У вас уже открыт депозит" << endl;
			}
			else cout << "Сумма депозита больше вашего зарплатного счета" << endl;
		}
		else cout << "Войдите в систему" << endl;
	}
	void GetPercent()//6) снять проценты (переведя их на зарплатный счет клиента)
	{
		if (login)
		{
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
			}
			if (set_year == clt.Deposit.endyear&&set_month >= clt.Deposit.endmonth)
			{
				if (set_month == clt.Deposit.endmonth&&set_day >= clt.Deposit.endday)
				{
					clt.SallaryAcc += clt.Deposit.SumRange + savings;
					clt.Deposit = {};
					savings = 0;
					rewrite(clt);
				}
				if (set_month > clt.Deposit.endmonth)
				{
					clt.SallaryAcc += clt.Deposit.SumRange + savings;
					clt.Deposit = {};
					savings = 0;
					rewrite(clt);
				}
				if (set_month == clt.Deposit.endmonth&&set_day < clt.Deposit.endday)
				{
					cout << "Депозит может быть закрыт только по оканчанию срока" << endl;
				}
			}
			if ((set_year < clt.Deposit.endyear) || (set_year == clt.Deposit.endyear&&set_year < clt.Deposit.endyear))
			{
				cout << "Депозит может быть закрыт только по оканчанию срока" << endl;
			}
		}
		else cout << "Войдите в систему" << endl;
	}
	friend ostream& operator<<(ostream &os, const ProcessingCentr &tmp);
	friend class ProcessingCentr;
};
void main()
{
	setlocale(LC_ALL, "rus");
	Client one = {8523,"password","Иванов Александр Евгеньевич",475120};
	ProcessingCentr centr;
	centr.AddClient(one);
	Bank network(centr);
	network.SetDate(13, 06, 1999);
	network.SignIn(8523, "password");
	//cout << endl;
	network.ShowAvaiDeposits();
	//network.OpenDeposit(15000, "3 года");
	//network.ShowStatusOfDeposit();
	//network.SignIn(8523, "password");
	//network.SetDate(14, 7, 2002);
	//network.CloseDeposit();
	//network.SignIn(8523, "password");
	//network.ShowStatusOfDeposit();
	system("pause");
}