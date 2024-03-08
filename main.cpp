#include "domain.h"
#include "repository.h"
#include "service.h"
#include "LAB1011.h"
#include <QtWidgets/qapplication.h>
#include "FilmeGUI.h"

int main(int argc, char** argv) {
    /*testRepoDel();
    testAddDel();
    testFind();
    testFindService();
    testModifyService();
    testFilter();
    testSort();
    testCos();*/
    {
        QApplication app(argc,argv);
        FilmRepo repo;
        repo.StoreFile();
        FilmCos repoCos;
        FilmCosFile print{ "exit.txt" };
	    Service service{ repo, repoCos, print};
        FilmStoreGUI gui{ service };
        gui.show();
        app.exec();
    }
	
	///consoleUI console{ service };
	///console.run();
	return 0;
}