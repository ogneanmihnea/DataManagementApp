#pragma once
#include "LAB1011.h"
#include "service.h"
#include <QtWidgets/qapplication.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qlayout.h>
#include <qlistwidget.h>
#include <QtWidgets/qpushbutton.h>
#include <qformlayout.h>
#include <QtWidgets/qlineedit.h>
#include <qmessagebox.h>
#include <QtWidgets/qtablewidget.h>
#include "Observer.h"
#include <qpainter.h>
#include <qtableview.h>
#include <qlistview.h>
#include "modele.h"

class FilmStoreGUI: public QWidget, public Observer {
private:
	Service& service;
	QHBoxLayout* lymain = new QHBoxLayout;
	///QListWidget* lst = new QListWidget;
	QListView* lst = new QListView;
	ModelList* myModelList;
	///QListWidget* lstCos = new QListWidget;
	
	QPushButton* btnSortByTitlu = new QPushButton("Sort by titlu");
	QPushButton* btnSortByActor = new QPushButton("Sort by actor");
	QPushButton* btnSortByAn_Gen = new QPushButton("Sort by an/gen");
	QPushButton* btnExit = new QPushButton("Exit");
	QPushButton* btnFiltrareTitlu = new QPushButton("Filtrare by titlu");
	QPushButton* btnFiltrareGen = new QPushButton("Filtrare by gen");
	QPushButton* btnCosFilme = new QPushButton("CosCRUDGUI");
	QPushButton* btnCosReadFilme = new QPushButton("CosReadOnlyGUI");
	QPushButton* btnAdd = new QPushButton("Adauga film");
	QPushButton* btnModify = new QPushButton("Modifica film");
	QPushButton* btnDelete = new QPushButton("Sterge film");
	QPushButton* btnUndo = new QPushButton("Undo");
	QPushButton* btnGen = new QPushButton("Generare butoane");
	QLineEdit* btnTextTitlu = new QLineEdit;
	QLineEdit* btnTextGen = new QLineEdit;
	QLineEdit* btnTextAn = new QLineEdit;
	QLineEdit* btnTextActor = new QLineEdit;
	
	void initGUI();
	void reloadList(const std::vector <Film>& Filme);
	void connectSignal();
	void addNewFilm();
	void DeleteFilm();
	void ModifyFilm();
	void Undo();
	///void reloadCos(const std::vector <Film>& Filme);
	void update() override;
public:
	FilmStoreGUI(Service& service) : service{ service } {
		initGUI();
		connectSignal();
		reloadList(service.getAll());
	};
};

class CosCrudGUI : public QWidget, public Observer {
private:
	Service& service;
	///QTableWidget* tabelCos = new QTableWidget;
	ModelTable* MyTableModel;
	QTableView* tabelCos = new QTableView;
	QPushButton* btnAddCos = new QPushButton("Add Cos");
	QPushButton* btnGenCos = new QPushButton("Generare cos");
	QPushButton* btnDeleteCos = new QPushButton("Delete cos");
	QPushButton* btnExportHTML = new QPushButton("Exporta HTML");
	QPushButton* btnExportCSV = new QPushButton("Exporta CSV");
	QLineEdit* btnCosTitlu = new QLineEdit;
	QLineEdit* btnExport = new QLineEdit;

	void addCos();
	void GenCos();
	void deleteCos();
	void ExportHtml();
	void ExportCsv();
	void reloadCos(const std::vector <Film>& Filme);
	void update() override;
	void initCos();
public:
	CosCrudGUI(Service& serv) : service{ serv } {
		initCos();
	}
	~CosCrudGUI() {
		service.removeObserver(this);
	}
};

class CosReadOnly : public QWidget, public Observer {
private:
	Service& service;
	void update() override;
	void initCos();
public:
	CosReadOnly(Service& service) : service{ service } {
		initCos();
	}

	void paintEvent(QPaintEvent* ev) override {
		QPainter p{ this };

		p.setPen(Qt::green);
		p.setFont(QFont("Arial", 15));

		int i = 1, j = 20;
		int cnt = 1;
		for (auto& elem : service.allCos()) {
			p.drawText(QPoint(i, j), QString::fromStdString(elem.getTitlu()));
			p.setPen(Qt::blue);
			p.setBrush(Qt::blue);
			QRect rect{ i,j+10,100,10 };
			p.fillRect(rect, p.brush());
			p.drawRect(rect);
			///p.drawLine(i, j + 10, i + 90, j + 10);
			
			j += 50;
			if (cnt % 5 == 0) {
				i += 270;
				j = 20;
			}
			p.setPen(Qt::green);
			cnt++;
		}
	}

	~CosReadOnly() {
		service.removeObserver(this);
	}
};

