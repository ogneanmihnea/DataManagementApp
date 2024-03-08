#ifndef  LAB6_REPOSITORY_H_
#define LAB6_REPOSITORY_H_

#include "domain.h"
///#include "vector.h"
#include <vector>
#include <iostream>
#include "Observer.h"
using std::vector;
class RepoException {
	string msg;
public:
	RepoException(string m) : msg{ m } {}
	string getMessage() {
		return msg;
	}
};

class abstractRepo {
public:
	virtual void afiseaza() = 0;
};

class FilmCos
{
private:
	vector <Film> Cos;
public:
	FilmCos(const FilmCos& obj) = delete;
	FilmCos() {};

	void delCos();
	const vector <Film>& getCos();
	void storeCos(const Film& film);

};

class FilmCosFile : public FilmCos
{

private:
	std::string fName;
	FilmCos print;
public:
	FilmCosFile(std::string fName) : FilmCos(), fName{ fName } {
	}
	///void writeToFile(vector <Film> v);
};

class FilmRepo : public abstractRepo
{
private:
	vector <Film> Filme;


public:

	FilmRepo(const FilmRepo& obj) = delete;
	FilmRepo() {};

	void afiseaza() override {
		std::cout << 12;
	}
	/*
	* Functia care adauga un film nou
	* :param: film obiect de tip film
	* :type film: obiect de tip Film
	*  : post : Lista este modificata
	*/
	void store(const Film& film);



	/*
	* Functia care imi returneaza lista cu toate filmele
	* :return:
	* :type return : vector de obiecte Film
	*/
	const vector <Film>& getAll();


	/*
	* Functia de gasire o masina dupa titlu
	* :param titlu: titlul filmului pe care il cautam
	* :type titlu: string
	* :return: pozitia din vector
	* :type return: int
	* exceptie daca filmul nu exista
	*/
	int find(string titlu) const;

	void StoreFile();

	int findobj(Film film);
	void modify(const Film& film);

	/*
	* Functia care returneaza un obiect Film de pe o anumita pozitie
	* :param i: pozitia care avem nevoie
	* :type numar: int
	* :return: filmul de care avem nevoie
	* :type return: obiect Film
	* exceptie daca filmul nu exista
	*/
	Film& getPoz(int i);

	/*
	* Functia care sterge un film din lista
	* :para i: pozitia care o stergem
	* :type numar: int
	* :return:
	* :type return:
	* Filmul se sterge
	*/
	void del(int poz);
};




void testRepoDel();
void testFind();

#endif // ! LAB6_REPOSITORY_H_


