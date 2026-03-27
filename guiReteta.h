#ifndef _GUIRETETA_H
#define _GUIRETETA_H
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qmessagebox.h>
#include <QtWidgets/qprogressbar.h>
#include <qpainter.h>
#include "reteta.h"
#include "gui.h"
#include "service.h"
#include "exceptii.h"
#include "observer.h"

class Gui;

class GuiReteta : public QWidget, public Observer {
	friend class Gui;
private:
	Reteta& recipe;
	ServiceMedicamente& service;
	QHBoxLayout* mainLy = new QHBoxLayout();
	QListWidget* reteta = new QListWidget();
	QPushButton* btnAdaugaRandom;
	QPushButton* btnGoleste;
	QPushButton* btnExportaHtml;
	QLineEdit* txtExport = new QLineEdit();
	QLineEdit* txtAdaugaRandom = new QLineEdit();
	void initGuiReteta();
	void loadReteta();
	void connectSignals();

	/*
	* Adauga medicamente random.
	*/
	void adaugaRandom();

	/*
	* Exporta in fisier html.
	*/
	void exporta();

	/*
	* Goleste reteta.
	*/
	void goleste();

public:
	GuiReteta(Reteta& recipe, ServiceMedicamente& service);

	void update() override;
};

class GuiRetetaDesene : public QWidget, public Observer {
private:
	Reteta& reteta;

	void connect();

public:
	GuiRetetaDesene(Reteta& reteta);

	void paintEvent(QPaintEvent*) override;

	void update() override;
};

#endif // !_GUIRETETA_H
