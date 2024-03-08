#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_LAB1011.h"

class LAB1011 : public QMainWindow
{
    Q_OBJECT

public:
    LAB1011(QWidget *parent = nullptr);
    ~LAB1011();

private:
    Ui::LAB1011Class ui;
};
