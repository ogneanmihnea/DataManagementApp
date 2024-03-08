#ifndef LAB6_SERVICE_H_
#define LAB6_SERVICE_H_

#include "repository.h"
#include <map>
#include "Undo.h"
#include "Observer.h"

using std::map;

class Service : public Observable
{
private:
	FilmRepo& repo;
	FilmCos& repoCos;
	FilmCosFile& print;
	vector <ActiuneUndo*> actiuneUndo = {};
	map <string, int> stats;
public:
	Service(FilmRepo& repo, FilmCos& repoCos, FilmCosFile& print) : repo{ repo }, repoCos{ repoCos },print { print } {}
	Service(const Service& obj) = delete;
	Service() = default;

	void deleteCos();
	const vector <Film>  allCos();
	void addCos(string titlu);
	void addRandom(int numar);
	void undo();

	/*
	* Functia care adauga un film nou
	* :param titlu: titlul filmului
	* :type titlu: string
	* :param gen: genul filmului
	* :type gen: string
	* :param an: anul filmului
	* :type an: int
	* :param actor: actorul filmului
	* :type actor: string
	*  : post :Filmul este adaugat
	*/
	void add(string titlu, string gen, int an, string actor);

	/*
	* Functia de gasire a unui film dupa titlu
	* :param titlu: titlul flimului pe care il cautam
	* :type titlu: string
	* :return: filmul cautat
	* :type return: obiect Film
	*/
	Film findService(string titlu) const;

	/*
	* Functia care sterge un film din lista
	* :param titlu: titlul filmului
	* :type titlu: string
	* Masina se sterge
	*/
	void deleteService(string titlu);

	/*
	* Functia care modifica un film existent
	* :param titlu: titlul filmului pe care il modificam
	* :type titlu: string
	* :param gen: genul filmului
	* :type gen: string
	* :param an: anul filmului
	* :type an: int
	* :param actor: actorul filmului
	* :type actor: string
	*  : post :Filmul este modificat
	*/
	void modifyService(string titlu, string gen, int an, string actor);

	/*
	* Filtrare listei de filme dupa 2 posibilitati
	* :param how: cum sa filtram
	* :type how: int
	* :param str: sirul dupa care sa filtram
	* :type str: string
	* :return : se returneaza o lista noua filtrata
	* :return type: vector cu obiecte Film
	*
	*/
	vector <Film> Filter(int how, string str);

	/*
	* Sortarea listei de filme dupa param how
	* :param how: cum sa filtram
	* :type how: int
	* :return : se returneaza o lista noua sortata
	* :return type: vector cu obiecte Film
	*/

	vector <Film> Sort(int how);

	/*
	* Functia care imi returneaza lista cu toate filmele inregistrate
	* :return:
	* :type return : vector de obiecte Film
	*/
	const vector <Film> getAll();


	map<string, int> getStats();
	//afis statistici
	void adaugStatistica(const string& gen);
	void stergStatistica(const string& gen);

	void PrintFile(string nume, int opt);
};

void testAddDel();
void testFindService();
void testModifyService();
void testFilter();
void testSort();
void testCos();

#endif // !LAB6_SERVICE_H_

