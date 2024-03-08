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
#include <qtableview.h>
#include <qlistview.h>

class ModelTable : public QAbstractTableModel {
private:
	vector <Film> arr;
public:
	ModelTable(const vector <Film>& arr) : arr{ arr } {};
	QVariant headerData(int section, Qt::Orientation orientation, int role) const {
		if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
			switch (section) {
			case 0:
				return QString("Titlu");
			}
		}
		return QVariant{};
	}
	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return arr.size();
	}
	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 1;
	}
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole && index.isValid() && index.row() < arr.size()) {
			return QString(QString::fromStdString(arr[index.row()].getTitlu())).arg(index.row()).arg(index.column());
		}
		return QVariant{};
	}

	void setArr(const vector <Film> vec) {
		this->arr = vec;
		auto topLeft = createIndex(0, 0);
		auto bottomR = createIndex(rowCount(), columnCount());
		emit layoutChanged();
		emit dataChanged(topLeft, bottomR);
	}
};

class ModelList : public QAbstractListModel {
private:
	vector <Film> arr;
public:
	ModelList(const vector <Film>& arr) : arr{ arr } {};
	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return arr.size();
	}
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole && index.isValid() && index.row() < arr.size()) {
			return QString(QString::fromStdString(arr[index.row()].getTitlu()));
		}
		return QVariant{};
	}

	void setArr(const vector <Film> vec) {
		this->arr = vec;
		auto topLeft = createIndex(0,0);
		auto bottomR = createIndex(rowCount(), 0);
		emit dataChanged(topLeft, bottomR);
	}
};