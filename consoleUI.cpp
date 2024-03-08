#include "consoleUI.h"
#include <iostream>
#include <fstream>
using std::cin;
using std::cout;


void consoleUI::addUI()
{
	int an;
	string titlu, gen, actor, strAn;
	cout << "Titlul filmului este: "; cin >> titlu;
	while (titlu.length() < 2)
	{
		cout << "\nTrebuie sa fie minim 3 caractere!!\n";
		cout << "Introduceti din nou: "; cin >> titlu;
	}
	cout << "Genul filmului este: "; cin >> gen;
	while (gen.length() < 2)
	{
		cout << "\nTrebuie sa fie minim 3 caractere!!\n";
		cout << "Introduceti din nou: "; cin >> gen;
	}
	cout << "Anul de lansare al filmului este: "; cin >> strAn;
	try { an = std::stoi(strAn); }
	catch (...) { cout << "\nAti introdus gresit!\n"; return; }
	while (an < 1850 or an>2023)
	{
		cout << "\nNu e valid anul dat\n";
		cout << "Introduceti din nou: "; cin >> strAn;
		try { an = std::stoi(strAn); }
		catch (...) { cout << "\nAti introdus gresit!\n"; return; }
	}
	cout << "Actorul filmului este: "; cin >> actor;
	while (actor.length() < 2)
	{
		cout << "\nTrebuie sa fie minim 3 caractere!!\n";
		cout << "Introduceti din nou: "; cin >> actor;
	}
	try
	{
		service.add(titlu, gen, an, actor);
		cout << "Filmul a fost adaugat\n";
	}
	catch (DomainException& ex)
	{
		cout << ex.getMessage();
	}
	catch (RepoException& ex)
	{
		cout << ex.getMessage();
	}
}

void consoleUI::deleteUI()
{
	string titlu;
	cout << "Titlul filmului pe care vreau sa-l sterg: ";
	cin >> titlu;
	try
	{
		service.deleteService(titlu);
		cout << "\nFilmul a fost sters \n";

	}
	catch (RepoException& ex)
	{
		cout << ex.getMessage();
	}



}

void consoleUI::findUI()
{
	string titlu;
	cout << "Titlul masinii pe care vreau sa o gasesc: ";
	cin >> titlu;
	try
	{
		Film f = service.findService(titlu);
		cout << "\nFilmul cu titlul dat are urmatoarele date: \n";
		cout << " Titlul: " << titlu;
		cout << " Genul: " << f.getGen();
		cout << " Anul: " << f.getAn();
		cout << " Actorul: " << f.getActor() << '\n';
	}
	catch (RepoException& ex)
	{
		cout << ex.getMessage();
	}
}

void consoleUI::modifyUI()
{
	int an;
	string titlu, gen, actor, strAn;
	cout << "Titlul filmului pe care dorim sa-l modificam: "; cin >> titlu;
	while (titlu.length() < 2)
	{
		cout << "\nTrebuie sa fie minim 3 caractere!!\n";
		cout << "Introduceti din nou: "; cin >> titlu;
	}
	cout << "Genul filmului este: "; cin >> gen;
	while (gen.length() < 2)
	{
		cout << "\nTrebuie sa fie minim 3 caractere!!\n";
		cout << "Introduceti din nou: "; cin >> gen;
	}
	cout << "Anul de lansare al filmului este: "; cin >> strAn;
	try { an = std::stoi(strAn); }
	catch (...) { cout << "\nAti introdus gresit!\n"; return; }
	while (an < 1850 or an>2023)
	{
		cout << "\nNu e valid anul dat\n";
		cout << "Introduceti din nou: "; cin >> strAn;
		try { an = std::stoi(strAn); }
		catch (...) { cout << "\nAti introdus gresit!\n"; return; }
	}
	cout << "Actorul filmului este: "; cin >> actor;
	while (actor.length() < 2)
	{
		cout << "\nTrebuie sa fie minim 3 caractere!!\n";
		cout << "Introduceti din nou: "; cin >> actor;
	}

	try
	{
		service.modifyService(titlu,gen,an,actor);
		cout << "\nFilmul a fost modificat\n";
	}
	catch (RepoException& ex)
	{
		cout << ex.getMessage();
	}

}

void consoleUI::print_aux(vector <Film> list)
{
	if (list.size() == 0)
		cout << "\nNu exista filme\n";
	else
	{
		printf("\n%15s | %15s | %15s | %15s | \n", "Titlu", "Gen", "An", "Actor");
		for (const Film& f : list)
			printf("%15s | %15s | %15d | %15s | \n", f.getTitlu().c_str(), f.getGen().c_str(), f.getAn(), f.getActor().c_str());
	}
}

void consoleUI::printUI()
{
	vector <Film> list = service.getAll();
	if (list.size() == 0)
		cout << "\nNu exista filme\n";
	else
	{
		printf("\n%15s | %15s | %15s | %15s | \n", "Titlu", "Gen", "An", "Actor");
		for (const Film& f : list)
			printf("%15s | %15s | %15d | %15s | \n", f.getTitlu().c_str(), f.getGen().c_str(), f.getAn(), f.getActor().c_str());
	}
}

//void consoleUI::printUI()
//{
//	vector <Film> list = service.getAll();
//	if (list.size() == 0)
//	{
//		cout << "\nNu exista masini\n";
//		return;
//	}
//	printf("\n%15s | %15s | %15s | %15s | \n", "Numar", "Producator", "Model", "Tip");
//	//cout << "\n%15sNumar | Producator | Model | Tip\n";
//	for (int i = 0; i < list.size(); i++)
//	{
//		printf("%15d | %15s | %15s | %15s | \n", list.at(i).getNumber(), list.at(i).getProd().c_str(), list.at(i).getModel().c_str(), list.at(i).getType().c_str());
//		//cout << c.getNumber() << "       " << c.getProd() << "       " << c.getModel() << "  " << c.getType() << "\n";
//	}
//
//}


void consoleUI::filtrareUI()
{
	int cmd;
	string aux, str;
	cout << "\nFiltrare dupa : \n 1. Titlu \n 2. Gen\n";

	cin >> str;
	try { cmd = std::stoi(str); }
	catch (...) { cout << "\nComanda invalida!\n"; return; }

	if (cmd == 1)
	{
		cout << "Titlul dupa care filtram lista este: "; cin >> aux;
		vector <Film> v = service.Filter(cmd, aux);
		if (v.size() == 0)
			cout << "\nNu exista filme cu acest titlu\n";
		else
		{
			print_aux(v);
		}
	}
	else
	{
		cout << "Genul dupa care filtram lista este: "; cin >> aux;
		vector <Film> v = service.Filter(cmd, aux);
		if (v.size() == 0)
			cout << "\nNu exista filme cu acest gen\n";
		else
		{
			print_aux(v);
		}
	}
}


void consoleUI::sortUI()
{

	int cmd;
	string str;
	cout << "\nSortare dupa : \n 1. Titlu \n 2. Actor \n 3. An + Gen\n";


	cin >> str;
	try { cmd = std::stoi(str); }
	catch (...) { cout << "\nComanda invalida!\n"; return; }

	if (cmd > 0 and cmd < 4)
	{
		vector <Film> v = service.Sort(cmd);
		print_aux(v);
	}
}

void consoleUI::uiMenu()
{
	cout << "\nAlege una dintre optiuni:\n";
	cout << "0.Exit\n";
	cout << "1.Adauga un film\n";
	cout << "2.Sterge un film\n";
	cout << "3.Gaseste un film\n";
	cout << "4.Modifica un film\n";
	cout << "5.Filtrare filme\n";
	cout << "6.Sortare filme\n";
	cout << "7.Afiseaza toate filmele\n";
	cout << "8.Afiseaza toate filmele din cos\n";
	cout << "9.Adauga film in cos\n";
	cout << "10.Elibereaza cos\n";
	cout << "11.Random\n";
	cout << "12.Afiseaza statistica\n";
	cout << "13.Undo\n";
	cout << "14.Export\n";
}

void consoleUI::printCos()
{
	auto list = service.allCos();
	if (list.size() == 0)
	{
		cout << "\nNu exista filme in cos\n";
		return;
	}
	printf("\n Filme din cos sunt:\n");
	printf("\n%15s | %15s | %15s | %15s | \n", "Titlu", "Gen", "An", "Actor");
	//cout << "\n%15sNumar | Producator | Model | Tip\n";
	for (const Film& f : list) {
		printf("%15s | %15s | %15d | %15s | \n", f.getTitlu().c_str(), f.getGen().c_str(), f.getAn(), f.getActor().c_str());
	}
}

void consoleUI::addCos()
{
	string str;
	cout << "Filmul care trebuie adaugat in cos: ";
	cin >> str;

	try
	{
		service.addCos(str);
		cout << "\nFilmul a fost adaugat in cos!\n";
	}
	catch (RepoException& ex)
	{
		cout << ex.getMessage();
	}
}

void consoleUI::deleteCos()
{
	try
	{
		service.deleteCos();
		cout << "\nCosul a fost eliberat!\n";
	}
	catch (RepoException& ex)
	{
		cout << ex.getMessage();
	}
}

void consoleUI::addRandom()
{
	int nr;
	cout << "Numarul de filme de adaugat este: ";
	cin >> nr;
	try {
		service.addRandom(nr);
		cout << "\nCosul a fost populat";
	}
	catch (RepoException& ex)
	{
		cout << ex.getMessage();
	}
}

void consoleUI::afisareStat() {
	auto all_stats = service.getStats();
	for (auto it = all_stats.begin(); it != all_stats.end(); ++it) {
		if (it->second > 0)
		{
			cout <<"Genul " << it->first << " apare de " << it->second<<" ori.\n";
		}
	}
}

void consoleUI::undoUI() {
	try {
		service.undo();
		cout << "\nUndo s-a executat cu succes!\n";
	}
	catch (RepoException& ex) {
		cout << ex.getMessage();
	}
}

void consoleUI::FilePrint()
{
	cout << "Introduceti numele fisierului unde doriti sa exportati: \n";
	string nume_fisier;
	cin>>nume_fisier;

	cout << "Introduceti formatul sub care doriti sa exportati: \n";
	cout << "1. CSV\n";
	cout << "2. HTML\n";

	int op;
	cin >> op;

	service.PrintFile(nume_fisier, op);

	cout << "Filmele au fost afisate cu succes!\n";
}

void consoleUI::run()
{
	int cmd;
	string str;
	while (1)
	{
		uiMenu();
		cout << "Optiunea ta este: ";
		cin >> str;
		try { cmd = std::stoi(str); }
		catch (...) { cout << "\nComanda invalida!\n"; cmd = 10; }

		switch (cmd)
		{
		case 0:
			return;
		case 1:
			addUI();
			break;
		case 2:
			deleteUI();
			break;
		case 3:
			findUI();
			break;
		case 4:
			modifyUI();
			break;
		case 5:
			filtrareUI();
			break;
		case 6:
			sortUI();
			break;
		case 7:
			printUI();
			break;
		case 8:
			printCos();
			break;
		case 9:
			addCos();
			break;
		case 10:
			deleteCos();
			break;
		case 11:
			addRandom();
			break;
		case 12:
		{
			afisareStat();
			break;
		}
		case 13:
		{
			undoUI();
			break;
		}
		case 14:
		{
			FilePrint();
			break;
		}
		default:
			break;
		}
	}
}

