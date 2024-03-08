#include "service.h"
#include <assert.h>
#include <random>
#include <chrono>
#include <fstream>

void Service::deleteCos(){
	repoCos.delCos();
	notify();
}

const vector <Film> Service::allCos() {
	return repoCos.getCos();
}

void Service::addCos(string titlu) {
	int poz = repo.find(titlu);
	repoCos.storeCos(repo.getPoz(poz));
	notify();
}

void Service::addRandom(int numar) {
	repoCos.delCos();
	vector <Film> v = repo.getAll();
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(v.begin(), v.end(), std::default_random_engine(seed));
	for (int i = 0; i < numar; i++) {
		Film& f = v[i];
		repoCos.storeCos(f);
	}
	notify();
}

void Service::add(string titlu, string gen, int an, string actor) {
	Film f{ titlu,gen,an,actor };
	f.validateFilm();
	repo.store(f);
	adaugStatistica(f.getGen());
	actiuneUndo.push_back(new UndoAdauga{ repo,f });
}

Film Service::findService(string titlu) const{
	int i = repo.find(titlu);
	Film f = repo.getPoz(i);
	return f;
}

void Service::deleteService(string titlu) {
	int i = repo.find(titlu);
	Film f = repo.getPoz(i);
	stergStatistica(f.getGen());
	repo.del(i);
	actiuneUndo.push_back(new UndoSterge{ repo,f });
}

void Service::modifyService(string titlu, string gen, int an, string actor) {
	int i = repo.find(titlu);
	Film& f = repo.getPoz(i);
	actiuneUndo.push_back(new UndoModify{ repo,f });
	Film f2 = { titlu,gen,an,actor };
	f = f2;
}

vector <Film> Service::Filter(int how, string str) {
	vector <Film> v;
	if (how == 1) {
		vector <Film> Filme = repo.getAll();
		for (const Film& f : Filme) {
			if (f.getTitlu() == str) {
				v.push_back(f);
			}
		}
	}
	else if (how == 2) {
		vector <Film> Filme = repo.getAll();
		for (const Film& f : Filme) {
			if (f.getGen() == str) {
				v.push_back(f);
			}
		}
	}
	return v;
}

void Service::PrintFile(string nume, int opt) {
	
		vector <Film> v = repoCos.getCos();

		string file_path = "D:\\info\\OOP\\Lab10-11\\";
		file_path += nume;

		if (opt == 1) {
			file_path += ".cvs";
		}
		else {
			file_path += ".html";
		}

		std::ofstream fout(file_path);

		if (opt == 1) {
			for (auto& f : v) {
				fout << f.getTitlu() << "," << f.getGen() << "," << f.getAn() << "," << f.getActor() << "\n";
			}
		}
		else {
			for (auto& f : v) {
				fout << f.getTitlu() << "|" << f.getGen() << "|" << f.getAn() << "|" << f.getActor() << "<br>";
			}
		}

	
}

vector <Film> Service::Sort(int how) {
	vector <Film> v = repo.getAll();
	if (v.size() == 0) {
		return v;
	}
	for (int i = 0; i < v.size() - 1; i++) {
		for (int j = i+1; j < v.size(); j++) {
			Film& f1 = v.at(i);
			Film& f2 = v.at(j);
			if (how == 1) {
				if (strcmp(f1.getTitlu().c_str(), f2.getTitlu().c_str()) > 0) {
					Film f3 = f1;
					f1 = f2;
					f2 = f3;
				}
			}
			else if (how == 2) {
				if (strcmp(f1.getActor().c_str(), f2.getActor().c_str()) > 0) {
					Film f3 = f1;
					f1 = f2;
					f2 = f3;
				}
			}
			else {
				if (f1.getAn() > f2.getAn()) {
					Film f3 = f1;
					f1 = f2;
					f2 = f3;
				}
				else if (f1.getAn() == f2.getAn()) {
					if (strcmp(f1.getGen().c_str(), f2.getGen().c_str()) > 0) {
						Film f3 = f1;
						f1 = f2;
						f2 = f3;
					}
				}
			}
		}
	}
	return v;
}

const vector <Film> Service::getAll() {
	return repo.getAll();
}

void Service::adaugStatistica(const string& gen)
{
	if (stats.count(gen))
		stats[gen]++;
	else
		stats[gen] = 1;
}

void Service::stergStatistica(const string& gen) {
	stats[gen]--;
}

map<string, int> Service::getStats()
{
	return stats;
}

void Service::undo() {
	if (actiuneUndo.empty()) {
		throw RepoException("\nNu se mai poate face undo!\n");
	}
	ActiuneUndo* actiune = actiuneUndo.back();
	actiune->doUndo();
	actiuneUndo.pop_back();
	delete actiune;
}


void testAddDel()
{
	FilmRepo repo;
	FilmCos repoCos;
	FilmCosFile print{"exit.txt"};
	Service serv{ repo, repoCos, print};

	serv.add("Batman", "actiune", 2005, "David");
	const vector <Film>& filme = serv.getAll();
	assert(filme.size() == 1);
	auto all_stats = serv.getStats();
	assert(all_stats["actiune"] == 1);
	serv.deleteService("Batman");

	const vector <Film>& filme1 = serv.getAll();
	assert(filme1.size() == 0);
	serv.add("Batman", "actiune", 2005, "David");
	serv.undo();
	assert(filme1.size() == 0);

	serv.add("Batman", "actiune", 2005, "David");
	serv.deleteService("Batman");
	serv.undo();
	const vector <Film>& filme3 = serv.getAll();
	assert(filme3.size() == 1);

	try {
		serv.add("Batman", "actiune", 100, "David"); assert(false);
	}
	catch (DomainException& ex)
	{
		assert(true);
		ex.getMessage();
	}

	try {
		serv.add("2", "actiune", 100, "David");
	}
	catch (...)
	{ assert(true);}

	try {
		serv.add("Batman", "e", 100, "David");
	}
	catch (...)
	{
		assert(true);
	}
	try {
		serv.add("Batman", "actiune", 100, "David");
	}
	catch (...)
	{
		assert(true);
	}
	try {
		serv.add("Batman", "actiune", 1959, "D");
	}
	catch (...)
	{
		assert(true);
	}
}

void testFindService()
{
	FilmRepo repo;
	FilmCos repoCos;
	FilmCosFile print{"exit.txt"};
	Service serv{ repo, repoCos, print };

	serv.add("Batman1", "actiune", 2005, "David");
	serv.add("Batman2", "actiune", 2006, "David");
	serv.add("Batman3", "actiune", 2007, "David");

	Film f1 = serv.findService("Batman1");
	assert(f1.getAn() == 2005 && f1.getActor() == "David");
}

void testModifyService()
{
	FilmRepo repo;
	FilmCos repoCos;
	FilmCosFile print{ "exit.txt" };
	Service serv{ repo, repoCos, print };

	serv.add("Batman1", "actiune", 2005, "David");
	serv.add("Batman2", "actiune", 2006, "David");
	serv.add("Batman3", "actiune", 2007, "David");

	serv.modifyService("Batman1", "comedie", 2000, "Alex");

	Film f1 = serv.findService("Batman1");
	assert(f1.getGen() == "comedie" && f1.getAn() == 2000 && f1.getActor() == "Alex");

	serv.undo();
	Film f2 = serv.findService("Batman1");
	assert(f2.getGen() == "actiune" && f2.getAn() == 2005 && f2.getActor() == "David");
}



void testFilter()
{
	FilmRepo repo;
	FilmCos repoCos;
	FilmCosFile print{ "exit.txt" };
	Service serv{ repo, repoCos, print };

	serv.add("Batman1", "actiune", 2005, "David");
	serv.add("Batman2", "actiune", 2006, "David");
	serv.add("Batman3", "actiune", 2007, "David");

	vector <Film> v = serv.Filter(1, "Batman1");
	assert(v.size() == 1);

	vector <Film> v1 = serv.Filter(2, "actiune");
	assert(v1.size() == 3);
}

void testSort() {
	FilmRepo repo;
	FilmCos repoCos;
	FilmCosFile print{ "exit.txt" };
	Service serv{ repo, repoCos, print };

	vector <Film> v1 = serv.Sort(1);

	assert(v1.size() == 0);
	serv.add("Batman6", "actiune2", 2005, "Aavid");
	serv.add("Batman2", "actiune1", 2005, "David");
	serv.add("Batman3", "actiune3", 2005, "David");
	serv.add("Batman1", "actiune4", 2001, "Cavid");
	serv.add("Batman9", "actiune5", 2005, "David");
	serv.add("Batman8" ,"actiune1",2001,"David" );
	
	vector <Film> v = serv.Sort(1);


	assert(v[0].getTitlu() == "Batman1");

	v = serv.Sort(2);
	assert(v[0].getTitlu() == "Batman6");

	v = serv.Sort(3);
	assert(v[0].getTitlu() == "Batman8");
}

void testCos()
{
	FilmRepo repo;
	FilmCos repoCos;
	FilmCosFile print{ "exit.txt" };
	Service serv{ repo,repoCos, print };

	serv.add("Batman6", "actiune2", 2005, "Aavid");
	serv.add("Batman2", "actiune1", 2005, "David");

	serv.addRandom(2);
	vector <Film> v1 = serv.allCos();
	assert(v1.size() == 2);

	serv.add("Batman3", "actiune3", 2005, "David");
	serv.add("Batman1", "actiune4", 2001, "Cavid");
	serv.add("Batman9", "actiune5", 2005, "David");
	serv.add("Batman8", "actiune1", 2001, "David");

	serv.deleteCos();
	v1 = serv.allCos();

	assert(v1.size() == 0);

	serv.addCos("Batman1");

	v1 = serv.allCos();
	assert(v1.size() == 1);
	serv.addCos("Batman2");
	v1 = serv.allCos();
	assert(v1.size() == 2);

	try
	{
		serv.addCos("Batman1"); assert(false);
	}
	catch (RepoException& ex)
	{
		assert(true);
		ex.getMessage();
	}

	serv.deleteCos();
	v1 = serv.allCos();
	assert(v1.size() == 0);


}