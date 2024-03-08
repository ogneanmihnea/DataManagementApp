#include "repository.h"
#include <assert.h>
#include <fstream>
#include <sstream>
#include <string.h>

void FilmRepo::store(const Film& film) {

	for (const Film& f : Filme)
	{
		if (f.getTitlu() == film.getTitlu())
			throw RepoException("\nFilm already exists\n");
	}
	/*for (int i = 0; i<Filme.size(); i++)
	{
		if (Filme[i].getNumber() == car.getNumber())
			throw RepoException("\nFilm already exists\n");}*/
	Filme.push_back(film);
	afiseaza();
}

void FilmRepo::StoreFile() {
	std::ifstream fin("text.in");
	if (fin.is_open()) {
		std::string line;
		while (std::getline(fin, line)) {
			std::vector <std::string> substrings;
			std::istringstream iss(line);
			std::string substring;
			while (std::getline(iss, substring, ';')) {
				substrings.push_back(substring);
			}
			Film f{ substrings[0],substrings[1], std::stoi(substrings[2]), substrings[3] };
			store(f);
		}
		fin.close();
	}
}

int FilmRepo::find(string titlu) const
{
	int poz = -1, i = 0;
	for (const Film& f : Filme)
	{
		poz++;
		if (f.getTitlu() == titlu)
			return poz;
	}
	throw RepoException("\nFilmul nu exista\n");}

int FilmRepo::findobj(Film film) {
	int poz = -1, i = 0;
	for (const Film& f : Filme)
	{
		poz++;
		if (f.getTitlu() == film.getTitlu())
			return poz;
	}
	throw RepoException("\nFilmul nu exista\n");}

void FilmRepo::modify(const Film& film) {
	int i = findobj(film);
	Filme[i] = film;
}

void FilmRepo::del(int poz)
{
	Filme.erase(Filme.begin() + poz);
	///Filme.erase(poz);
}



Film& FilmRepo::getPoz(int i)
{
	return Filme.at(i);
}

const vector <Film>& FilmRepo::getAll()
{
	return Filme;
}

//void FilmCosFile::writeToFile(vector <Film> v)
//{
//	std::ofstream out(fName);
//
//	/*if (!out.is_open())
//	{
//		string ms("Error open file");
//		throw DomainException(ms);
//	}*/
//
//	for (auto& f : v) {
//		out << f.getTitlu();
//		out << " ";
//		out << f.getGen();
//		out << " ";
//		out << f.getAn();
//		out << " ";
//		out << f.getActor();
//		out << " ";
//		out << std::endl;
//	}
//	out.close();
//}

void FilmCos::delCos() {
	Cos.clear();
}

const vector <Film>& FilmCos::getCos() {
	return Cos;
}

void FilmCos::storeCos(const Film& film) {
	for (const Film& f : Cos) {
		if (f.getTitlu() == film.getTitlu()) {
			throw RepoException("\nFilmul este deja in cos!\n");
		}
	}
	Cos.push_back(film);
}


void testRepoDel()
{
	FilmRepo repo;
	Film f1{ "Batman" ,"actiune",2005,"David"};
	Film f2{ "Batman 2" ,"actiune",2008,"David" };
	
	repo.store(f1);
	const vector <Film>& filme = repo.getAll();
	assert(filme.size() == 1);

	repo.store(f2);

	const vector <Film>& filme2 = repo.getAll();
	assert(filme2.size() == 2);



	try {
		repo.store(f1); assert(false);
	}
	catch (RepoException& e)
	{
		assert(true);
		e.getMessage();
	}

	repo.del(0);


	repo.del(0);
	assert(filme.size() == 0);

	Film f3{ "Batman 3" ,"actiune",2008,"David" };
	f3.setTitlu("Spiderman");
	f3.setGen("comedie");
	f3.setAn(2000);
	f3.setActor("Alex");
	assert(f3.getActor() == "Alex" && f3.getAn() == 2000 && f3.getGen() == "comedie" && f3.getTitlu() == "Spiderman");

	repo.store(f3);
	f3.setGen("trei");
	repo.modify(f3);
	assert(filme[0].getGen() == "trei");
}

void testFind()
{
	FilmRepo repo;
	Film f1{ "Batman" ,"actiune",2005,"David" };
	Film f2{ "Batman 2" ,"actiune",2008,"David" };
	Film f3{ "Batman 3" ,"actiune",2009,"Alex" };
	Film f12{ "Batman 5" ,"actiune",2009,"Alex" };
	repo.store(f1);
	repo.store(f2);
	repo.store(f3);

	try {
		repo.find("Spiderman"); assert(false);
	}
	catch (RepoException& e)
	{
		assert(true);
		e.getMessage();
	}

	try {
		repo.findobj(f12); assert(false);
	}
	catch (RepoException& e)
	{
		assert(true);
		e.getMessage();
	}
	int i = repo.findobj(f1);
	assert(i == 0);
	i = repo.find("Batman");
	assert(i == 0);

	Film f5 = repo.getPoz(i);
	assert(f1.getActor() == f5.getActor() && f1.getAn() == f5.getAn());
}