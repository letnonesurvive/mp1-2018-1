#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#define size 15
using namespace std;

//Данные :: название, режиссер, сценарист, композитор, дата выхода в прокат (день, месяц, год), сборы (в рублях)
//Класс должен предоставлять следующие операции : 1) добавить фильм, 2) изменить данные выбранного фильма, 
//3) найти фильм по названию и году, 4) выдать все фильмы заданного режиссера, 
//5) выдать все фильмы, вышедшие в прокат в выбранном году, 6) выдать заданное число фильмов с наибольшими сборами, 
//7) выдать заданное число фильмов с наибольшими сборами в выбранном году, 
//8) узнать текущее число фильмов, 9) удалить фильм, 10) сохранить фильмотеку в файл, 11) считать фильмотеку из файла.
//1)+
//2)?
//3)+
//4)+
//5)+
//6)+
//7)+
//8)+
//9)+
//10)+
//11)+
struct Date //данные релиза
{
	int day;
	int month;
	int year;
};
struct Facts //данные для фильмов 
{
	string name;
	string producer;
	string composer;
	unsigned long int fees;//сборы
};
struct Film //фильм хранит дату и прочие данные(в том числе и название)
{
	Date date;
	Facts stock;
	Film &operator=(const Film &tmp1)
	{
		this->date.day = tmp1.date.day;
		this->date.month = tmp1.date.month;
		this->date.year = tmp1.date.year;
		this->stock.name = tmp1.stock.name;
		this->stock.composer = tmp1.stock.composer;
		this->stock.producer = tmp1.stock.producer;
		this->stock.fees = tmp1.stock.fees;
		return *this;
	}
	bool operator ==(const Film &tmp1) const
	{
		return (this->date.day == tmp1.date.day && this->date.month == tmp1.date.month&&this->date.year == tmp1.date.year&& this->stock.name == tmp1.stock.name&& this->stock.composer == tmp1.stock.composer&& this->stock.producer == tmp1.stock.producer&& this->stock.fees == tmp1.stock.fees);
	}
	bool operator !=(const Film &tmp1) const
	{
		return !(this->date.day == 0 && this->date.month == 0 && this->date.year == 0 && this->stock.name == "" && this->stock.composer == "" && this->stock.producer == "" && this->stock.fees == 0);
	}
	bool operator !=(const int &tmp) const
	{
		return !(this->date.day == 0 && this->date.month == 0 && this->date.year == 0 && this->stock.name == "" && this->stock.composer == "" && this->stock.producer == "" && this->stock.fees == 0);
	}
};
class FilmLibrary
{
private:
	Date date[size] = {};
	Facts stock[size] = {};
	Film film1[size] = { *date,*stock };//основной архив фильмов
	Film tmp[size] = {};//архив фильмов не основной
public:
	FilmLibrary(Film film = {})
	{

	}
	void AddFilm(Film film, const int i)//добавить фильм
	{
		film1[i] = film;
	}
	Film GetFilmName(string name, int _year)// дать фильм по названию и году
	{
		for (int i = 0; i < size; i++)
		{
			if (film1[i].stock.name == name&&film1[i].date.year == _year)
				return film1[i];
		}
	}
	void SetChanges(int _day, int _month,int _year)
	{

	}
	void SetFilmProducer(string producer)//работает в паре с void PrintFilmTune()
	{
		int j = 0;
		for (int i = 0; i < size; i++)
		{
			if (film1[i].stock.producer == producer)
			{
				tmp[j] = film1[i];
				j += 1;
			}
		}
	}
	void SetFilmYear(int _year)//работает в паре с void PrintFilmTune()
	{
		int j = 0;
		for (int i = 0; i < size; i++)
		{
			if (film1[i].date.year == _year)
			{
				tmp[j] = film1[i];
				j += 1;
			}
		}
	}
	void SetFilmFees(int k)//выдать фильмы с наибольшими сборами работает в паре с void PrintFilmTune()
	{
		unsigned long int max = 0;
		int j = -1;
		int y = 0;
		for (int x = 0; x < k; x++)
		{
			max = 0;
			for (int i = 0; i < size; i++)
			{
				if (film1[i].stock.fees>max)
				{
					max = film1[i].stock.fees;
					j = i;
				}
			}
			tmp[y] = film1[j];
			y++;
			film1[j] = {};
		}
	}
	void SetFilmFees(int k, int _year)//выдать фильмы с наибольшими сборами и выбранном году работает в паре с void PrintFilmTune()
	{
		unsigned long int max = 0;
		int j = -1;
		int y = 0;
		for (int x = 0; x < k; x++)
		{
			max = 0;
			for (int i = 0; i < size; i++)
			{
				if (film1[i].stock.fees>max)
				{
					if (film1[i].date.year == _year)
					{
						max = film1[i].stock.fees;
						j = i;
					}
				}
			}
			tmp[y] = film1[j];
			y++;
			film1[j] = {};
		}
	}
	int GetValueFilms()//Возвращает число фильмов
	{
		int num = 0;
		for (int i = 0; i < size; i++)
		{
			if (film1[i] != 0)
				num++;
		}
		return num;
	}
	void PrintFilmTune()//выписывает фильмы заданного автора/ заданного года/с наибольшими сборами
	{
		for (int i = 0; i < size; i++)
			if (tmp[i] != 0)//проверка на не ли пустой фильм 
				cout << tmp[i] << endl;
	}
	void DeleteFilm(Film tmp = {})
	{
		for (int i = 0; i < size; i++)
		{
			if (film1[i] == tmp)
			{
				film1[i] = {};
			}
		}
	}
	void SaveInFile()
	{
		ofstream fout("note.txt");
		fout << *this << endl;
		fout.close();
	}
	void GetOutFile()
	{
		int count = 5 * GetValueFilms() + GetValueFilms()-1;//5  потому что каждый фильм занимает 5 строчек в консоли
		string *buff=new string[count];
		ifstream fin("note.txt");
		for (int i = 0; i <count; i++)
		{
			getline(fin, buff[i]);
			cout << buff[i] << endl;
		}
		fin.close();
		delete[] buff;
	}
	friend ostream &operator<<(ostream &os, const Film &film);
	friend ostream &operator<<(ostream &os, const FilmLibrary &tmp);
};

ostream &operator<<(ostream &os, const Film &film)
{
	os << "день:" << film.date.day << " " << "месяц:" << film.date.month << " " << "год:" << film.date.year << endl;
	os << "название:" << film.stock.name << "\n" << "режиссер:" << film.stock.producer << "\n" << "композитор:" << film.stock.composer << "\n" << "сборы:" << film.stock.fees << endl;
	return os;
}
ostream &operator<<(ostream &os, const FilmLibrary &tmp)
{
	for (int i = 1; i < size; i++)
	{
		if (tmp.film1[i] != 0)//проверка на не ли пустой фильм 
		{
			os << tmp.film1[i];
			os << endl;
		}
	}
	return os;
}
void main()
{
	setlocale(LC_ALL, "rus");
	FilmLibrary Library1;
	Film Furios;
	Film StarWars;
	Film Retribution;
	Film Titanik;
	Film Angelsofdeath;
	/*-----------------------------------------------------------*/

	Library1.AddFilm(Furios = { 10,8,2004 , "Форсаж","Роб Коэн","Музыкант",123456 }, 1);
	Library1.AddFilm(StarWars = { 11,9,2005,"Звездные войны","Джеймс Кэмерон","Моцарт",12345 }, 2);
	Library1.AddFilm(Retribution = { 18,9,2009,  "Возмездие","Джеймс Кэмерон","Бетховен",300 }, 3);
	Library1.AddFilm(Titanik = { 6, 04, 2009, "Титаник", "Кельвин Кльян", "Композитор", 100 }, 4);
	Library1.AddFilm(Angelsofdeath = { 10,8,2009 , "Ангелы смерти","Роб Коэн","Чайковский",200 }, 5);
	// cout << Library1;
	/*-----------------------------------------------------------*/
	//cout << Library1.GetFilmName("Форсаж", 2004) << endl;//true
	//Library1.SetFilmProducer("Джеймс Кэмерон");//true
	//Library1.SetFilmYear(2009);true
	//Library1.SetFilmFees(5);
	//Library1.PrintFilmTune();
	//cout << Library1.GetValueFilms();
	//Library1.DeleteFilm(StarWars);
	//Library1.SaveInFile();
	//Library1.GetOutFile();
	system("pause");
}
