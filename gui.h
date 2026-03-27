#ifndef _GUI_H_
#define _GUI_H_
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qmessagebox.h>
#include <QtWidgets/qtablewidget.h>
#include <QtWidgets/qtableview.h>
#include <vector>
#include "service.h"
#include "reteta.h"
#include "exceptii.h"
#include "guiReteta.h"
#include "myTableModel.h"

using std::vector;

class Gui : public QWidget {
private:
	int id;
	vector <QPushButton*> vectbtn;
	ServiceMedicamente& service;
	Reteta& recipe;
	QHBoxLayout* mainLy = new QHBoxLayout;
	QPushButton* btnAdauga;
	QPushButton* btnSterge;
	QPushButton* btnModifica ;
	QPushButton* btnSorteazaDupaDenumire;
	QPushButton* btnSorteazaDupaProducator;
	QPushButton* btnRaport;
	QPushButton* btnCauta;
	QVBoxLayout* lybtntip = new QVBoxLayout;
	QHBoxLayout* retetaLy = new QHBoxLayout;
	QPushButton* btnReteta;
	QPushButton* btnAdaugaReteta;
	QPushButton* btnAdauaRetetaRandom;
	QPushButton* btnGolesteReteta;
	QPushButton* btnSorteazaDupaSubstantaActivaSiPret;
	QPushButton* btnFiltreazaDupaPret;
	QPushButton* btnFiltreazaDupaSubstantaActiva;
	QPushButton* btnRetetaDesene;
	QPushButton* btnUndo;
	QLineEdit* txtDenumire = new QLineEdit();
	QLineEdit* txtPret = new QLineEdit();
	QLineEdit* txtProducator = new QLineEdit();
	QLineEdit* txtSubstantaActiva = new QLineEdit();
	QLineEdit* txtNrRetetaRandom = new QLineEdit();
	QListWidget* listaMedicamente = new QListWidget();
	QListWidget* rezultate = new QListWidget();
	//QTableWidget* tabelMedicamente = new QTableWidget(100, 4);
	QTableView* tabelMedicamente = new QTableView;
	MyTableModel* model;

	/*
	* Curata textfiled-urile.
	*/
	void curataTextFielduri();

	/*
	* Initilieaza ferastra.
	*/
	void initGui();

	/*
	* Incarca datele.
	*/
	void load();

	void connectSignals();

	/*
	* Adauga medicament.
	*/
	void adauga();

	/*
	* Adauga medicament la reteta.
	*/
	void adaugaReteta();

	/*
	* Adauga random in reteta.
	*/
	void adaugaRetetaRandom();

	/*
	* Goleste reteta.
	*/
	void golesteReteta();

	/*
	* Deschide fereastra cu retea grafica.
	*/
	void retetaGrafica();

	/*
	* Creeaza reteta.
	*/
	void reteta();

	/*
	* Sterge medicament.
	*/
	void sterge();

	/*
	* Cauta medicament.
	*/
	void cauta();

	/*
	* Modifica medicament.
	*/
	void modifica();

	/*
	* Afiseaza detaliile edicamentului.
	*/
	void detalii();

	/*
	* Afiseaza raportul.
	*/
	void raport();

	/*
	* Filtreaza medicamente dupa denumire.
	*/
	void filtreazaPret();

	/*
	* Filtraza medicamnete dupa substanta activa.
	*/
	void filtreazaSubstantaActiva();

	/*
	* Soreteaza dupa denumire.
	*/
	void sorteazaDenumire();

	/*
	* Sorteaza dupa producator.
	*/
	void sorteazaProducator();

	/*
	* Sorteaza dupa substanta activa si pret.
	*/
	void sorteazaDupaSubstantaActivaSiPret();

	/*
	* Face undo.
	*/
	void undo();

	void conectButoaneRaport();

public:
	Gui(Reteta& recipe, ServiceMedicamente& service);
};

#endif // !_GUI_H_
