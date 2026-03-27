#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Lab10_11_Farmacie.h"

class Lab10_11_Farmacie : public QMainWindow
{
    Q_OBJECT

public:
    Lab10_11_Farmacie(QWidget *parent = nullptr);
    ~Lab10_11_Farmacie();

private:
    Ui::Lab10_11_FarmacieClass ui;
};
