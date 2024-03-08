#ifndef LAB6_UICONSOLE_H_
#define LAB6_UICONSOLE_H_

#include "service.h"

class consoleUI
{
private:
	Service& service;
	void uiMenu();

public:
	consoleUI(Service& service) : service{ service } {}
	void run();
	void addUI();
	void printUI();
	void deleteUI();
	void findUI();
	void modifyUI();
	void filtrareUI();
	void sortUI();
	void print_aux(vector <Film> list);
	void deleteCos();
	void addCos();
	void printCos();
	void addRandom();
	void afisareStat();
	void undoUI();
	void FilePrint();
};



#endif // !LAB6_UICONSOLE_H_
