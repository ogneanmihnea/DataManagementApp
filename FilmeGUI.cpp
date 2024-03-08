#include "FilmeGUI.h"

void FilmStoreGUI::initGUI() {
	setLayout(lymain);
	QWidget* widLista = new QWidget;
	QVBoxLayout* vl = new QVBoxLayout;
	///widLista->setStyleSheet("background-color:turquoise");
	myModelList = new ModelList(service.getAll());
	lst->setModel(myModelList);
	vl->addWidget(lst);
	widLista->setLayout(vl);

	lymain->addWidget(widLista);

	QWidget* widBtnSort = new QWidget;
	QHBoxLayout* lyBtnSort = new QHBoxLayout;
	
	lyBtnSort->addWidget(btnSortByTitlu);
	lyBtnSort->addWidget(btnSortByActor);
	lyBtnSort->addWidget(btnSortByAn_Gen);
	
	widBtnSort->setLayout(lyBtnSort);
	
	vl->addWidget(widBtnSort);
	btnExit->resize(30, 30);
	vl->addWidget(btnExit);

	QWidget* widFiltrare = new QWidget;
	QVBoxLayout* lyfiltrare = new QVBoxLayout;
	lyfiltrare->addWidget(btnFiltrareTitlu);
	lyfiltrare->addWidget(btnFiltrareGen);
	btnCosFilme->setFixedSize(100,80);
	btnCosReadFilme->setFixedSize(100,80);
	lyfiltrare->addWidget(btnCosFilme);
	lyfiltrare->addWidget(btnCosReadFilme);
	///widFiltrare->setStyleSheet("background-color:aqua");
	widFiltrare->setLayout(lyfiltrare);
	lymain->addWidget(widFiltrare);

	QWidget* widDreapta = new QWidget;
	QFormLayout* lydreapta = new QFormLayout;
	widDreapta->setLayout(lydreapta);
	btnTextTitlu->setPlaceholderText("Dati un titlu");
	lydreapta->addRow(new QLabel("Titlu: "), btnTextTitlu);
	btnTextGen->setPlaceholderText("Dati un gen");
	lydreapta->addRow(new QLabel("Gen: "), btnTextGen);
	btnTextAn->setPlaceholderText("Dati un an(1850-2023)");
	lydreapta->addRow(new QLabel("An: "), btnTextAn);
	btnTextActor->setPlaceholderText("Dati un actor");
	lydreapta->addRow(new QLabel("Actor: "), btnTextActor);

	lydreapta->addWidget(btnAdd);
	lydreapta->addWidget(btnDelete);
	lydreapta->addWidget(btnModify);
	lydreapta->addWidget(btnUndo);
	lydreapta->addWidget(btnGen);

	lymain->addWidget(widDreapta);
	
}

void FilmStoreGUI::update(){
	QWidget::update();
}

void CosCrudGUI::update() {
	reloadCos(service.allCos());
}

void FilmStoreGUI::connectSignal() {
	QObject::connect(btnGen, &QPushButton::clicked, [&]() {
		map <string, int> statsuri = service.getStats();
		vector <QPushButton*> btngenerate;
		int k = 0;
		for (const auto& s : statsuri) {
			string str = s.first;
			int a = s.second;
			QPushButton* newBTN = new QPushButton(QString::fromStdString(str));
			btngenerate.push_back(newBTN);
			lymain->addWidget(btngenerate[k]);
			QObject::connect(btngenerate[k], &QPushButton::clicked, [&, a]() {
				QMessageBox* mesaj = new QMessageBox;
				auto aa = QString::number(a);
				mesaj->setText(aa);
				mesaj->show();
				});
			k++;
		}
		
		});
	QObject::connect(btnExit, &QPushButton::clicked, this, &QApplication::quit);
	QObject::connect(btnSortByTitlu, &QPushButton::clicked, [&]() {
		reloadList(service.Sort(1));
		});
	QObject::connect(btnSortByActor, &QPushButton::clicked, [&]() {
		reloadList(service.Sort(2));
		});
	QObject::connect(btnSortByAn_Gen, &QPushButton::clicked, [&]() {
		reloadList(service.Sort(3));
		});
	QObject::connect(btnFiltrareTitlu, &QPushButton::clicked, [&]() {
		QWidget* fereastra = new QWidget;
		QVBoxLayout* lyfereastra = new QVBoxLayout;
		
		fereastra->setLayout(lyfereastra);
		QListWidget* lst2 = new QListWidget;
		lyfereastra->addWidget(lst2);
		auto filme = service.Filter(1, btnTextTitlu->text().toStdString());
		for (const auto& f : filme) {
			QString ss = QString::fromStdString(f.getGen()) + ". " + QString::number(f.getAn()) + ". " + QString::fromStdString(f.getActor());
			QListWidgetItem* item = new QListWidgetItem(ss);
			lst2->addItem(item);
		}
		fereastra->show();
		});
	QObject::connect(btnFiltrareGen, &QPushButton::clicked, [&]() {
		QWidget* fereastra = new QWidget;
		QVBoxLayout* lyfereastra = new QVBoxLayout;

		fereastra->setLayout(lyfereastra);
		QListWidget* lst2 = new QListWidget;
		lyfereastra->addWidget(lst2);
		auto filme = service.Filter(2, btnTextGen->text().toStdString());
		for (const auto& f : filme) {
			QString ss = QString::fromStdString(f.getTitlu()) + ". " + QString::number(f.getAn()) + ". " + QString::fromStdString(f.getActor());
			QListWidgetItem* item = new QListWidgetItem(ss);
			lst2->addItem(item);
		}
		fereastra->show();
		});

	QObject::connect(btnCosFilme, &QPushButton::clicked, this, [&]() {
		CosCrudGUI* NewCos = new CosCrudGUI(service);
		NewCos->show();
		});
	QObject::connect(btnCosReadFilme, &QPushButton::clicked, this, [&]() {
		CosReadOnly* NewCos = new CosReadOnly(service);
		NewCos->show();
		});
	QObject::connect(btnAdd, &QPushButton::clicked, this, &FilmStoreGUI::addNewFilm);
	QObject::connect(btnDelete, &QPushButton::clicked,this, &FilmStoreGUI::DeleteFilm);
	QObject::connect(btnModify, &QPushButton::clicked,this, &FilmStoreGUI::ModifyFilm);
	QObject::connect(btnUndo, &QPushButton::clicked,this, &FilmStoreGUI::Undo);
}





void FilmStoreGUI::addNewFilm() {
	try {
		service.add(btnTextTitlu->text().toStdString(), btnTextGen->text().toStdString(), btnTextAn->text().toInt(), btnTextActor->text().toStdString());
		reloadList(service.getAll());
	}
	catch (RepoException& ex) {
		QMessageBox::warning(this, "warning", QString::fromStdString(ex.getMessage()));
	}
	catch (DomainException& ex) {
		QMessageBox::warning(this, "warning", QString::fromStdString(ex.getMessage()));
	}
}

void FilmStoreGUI::DeleteFilm() {
	try {
		service.deleteService(btnTextTitlu->text().toStdString());
		reloadList(service.getAll());
	}
	catch (RepoException& ex) {
		QMessageBox::warning(this, "warning", QString::fromStdString(ex.getMessage()));
	}
	catch (DomainException& ex) {
		QMessageBox::warning(this, "warning", QString::fromStdString(ex.getMessage()));
	}
}

void FilmStoreGUI::ModifyFilm() {
	try {
		service.modifyService(btnTextTitlu->text().toStdString(), btnTextGen->text().toStdString(), btnTextAn->text().toInt(), btnTextActor->text().toStdString());
		reloadList(service.getAll());
	}
	catch (RepoException& ex) {
		QMessageBox::warning(this, "warning", QString::fromStdString(ex.getMessage()));
	}
	catch (DomainException& ex) {
		QMessageBox::warning(this, "warning", QString::fromStdString(ex.getMessage()));
	}
}

void FilmStoreGUI::Undo() {
	try {
		service.undo();
		reloadList(service.getAll());
	}
	catch (RepoException& ex) {
		QMessageBox::warning(this, "warning", QString::fromStdString(ex.getMessage()));
	}
	catch (DomainException& ex) {
		QMessageBox::warning(this, "warning", QString::fromStdString(ex.getMessage()));
	}
}

void CosCrudGUI::reloadCos(const std::vector <Film>& FilmeCos) {
	/*tabelCos->clear();
	tabelCos->setColumnCount(1);
	tabelCos->setRowCount(FilmeCos.size());
	int k = 0;
	for (const auto& f : FilmeCos) {
		QString ss = QString::fromStdString(f.getTitlu());
		QTableWidgetItem* item = new QTableWidgetItem(ss);
		tabelCos->setItem(k, 0, item);
		k++;
	}*/
	MyTableModel->setArr(FilmeCos);
}

void FilmStoreGUI::reloadList(const std::vector <Film>& Filme) {
	/*lst->clear();
	for (const auto& f : Filme) {
		QString ss = QString::fromStdString(f.getTitlu());
		QListWidgetItem* item = new QListWidgetItem(ss);
		lst->addItem(item);
	}*/
	myModelList->setArr(Filme);
}

void CosCrudGUI::initCos() {
	service.addObserver(this);
	MyTableModel = new ModelTable(service.allCos());
	tabelCos->setModel(MyTableModel);
	reloadCos(service.allCos());
	QVBoxLayout* lyfereastra = new QVBoxLayout;
	setLayout(lyfereastra);


	///lyfereastra->addWidget(lstCos);
	lyfereastra->addWidget(tabelCos);
	lyfereastra->addWidget(btnCosTitlu);
	btnCosTitlu->setPlaceholderText("Titlul filmului");
	btnCosTitlu->setAlignment(Qt::AlignCenter);
	lyfereastra->addWidget(btnAddCos);
	lyfereastra->addWidget(btnDeleteCos);
	lyfereastra->addWidget(btnGenCos);
	lyfereastra->addWidget(btnExport);
	btnExport->setPlaceholderText("Export File Name");
	btnExport->setAlignment(Qt::AlignCenter);
	lyfereastra->addWidget(btnExportHTML);
	lyfereastra->addWidget(btnExportCSV);

	QObject::connect(btnAddCos, &QPushButton::clicked, this, &CosCrudGUI::addCos);
	QObject::connect(btnDeleteCos, &QPushButton::clicked, this, &CosCrudGUI::deleteCos);
	QObject::connect(btnGenCos, &QPushButton::clicked, this, &CosCrudGUI::GenCos);
	QObject::connect(btnExportHTML, &QPushButton::clicked, this, &CosCrudGUI::ExportHtml);
	QObject::connect(btnExportCSV, &QPushButton::clicked, this, &CosCrudGUI::ExportCsv);

}

void CosCrudGUI::addCos() {
	try {
		service.addCos(btnCosTitlu->text().toStdString());
		reloadCos(service.allCos());
	}
	catch (RepoException& ex) {
		QMessageBox::warning(this, "warning", QString::fromStdString(ex.getMessage()));
	}
	catch (DomainException& ex) {
		QMessageBox::warning(this, "warning", QString::fromStdString(ex.getMessage()));
	}
}

void CosCrudGUI::GenCos() {
	try {
		service.addRandom(5);
		reloadCos(service.allCos());
	}
	catch (RepoException& ex) {
		QMessageBox::warning(this, "warning", QString::fromStdString(ex.getMessage()));
	}
	catch (DomainException& ex) {
		QMessageBox::warning(this, "warning", QString::fromStdString(ex.getMessage()));
	}
}

void CosCrudGUI::ExportHtml() {
	try {
		service.PrintFile(btnExport->text().toStdString(), 2);
	}
	catch (RepoException& ex) {
		QMessageBox::warning(this, "warning", QString::fromStdString(ex.getMessage()));
	}
	catch (DomainException& ex) {
		QMessageBox::warning(this, "warning", QString::fromStdString(ex.getMessage()));
	}
}

void CosCrudGUI::ExportCsv() {
	try {
		service.PrintFile(btnExport->text().toStdString(), 1);
	}
	catch (RepoException& ex) {
		QMessageBox::warning(this, "warning", QString::fromStdString(ex.getMessage()));
	}
	catch (DomainException& ex) {
		QMessageBox::warning(this, "warning", QString::fromStdString(ex.getMessage()));
	}
}

void CosCrudGUI::deleteCos() {
	try {
		service.deleteCos();
		reloadCos(service.allCos());
	}
	catch (RepoException& ex) {
		QMessageBox::warning(this, "warning", QString::fromStdString(ex.getMessage()));
	}
	catch (DomainException& ex) {
		QMessageBox::warning(this, "warning", QString::fromStdString(ex.getMessage()));
	}
}

void CosReadOnly::initCos() {
	service.addObserver(this);
}

void CosReadOnly::update() {
	QWidget::update();
}