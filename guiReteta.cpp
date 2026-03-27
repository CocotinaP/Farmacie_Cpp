#include "guiReteta.h"

void GuiReteta::initGuiReteta() {
	recipe.adaugaObserver(this);
	setLayout(mainLy);
	mainLy->addWidget(reteta);
	QFormLayout* formLy = new QFormLayout();
	formLy->addRow("Nr. medicamente random", txtAdaugaRandom);
	formLy->addRow("Nume fisier", txtExport);
	QVBoxLayout* leftLy = new QVBoxLayout();
	leftLy->addLayout(formLy);
	mainLy->addLayout(leftLy);
	btnAdaugaRandom = new QPushButton("Adauga random");
	btnExportaHtml = new QPushButton("Exporta in fiser HTML");
	btnGoleste = new QPushButton("Goleste");
	QHBoxLayout* btnsLy1 = new QHBoxLayout();
	btnsLy1->addWidget(btnAdaugaRandom);
	btnsLy1->addWidget(btnExportaHtml);
	btnsLy1->addWidget(btnGoleste);
	leftLy->addLayout(btnsLy1);
}

GuiReteta::GuiReteta(Reteta& reteta, ServiceMedicamente& service) : recipe { reteta }, service{ service } {
	initGuiReteta();
	connectSignals();
	loadReteta();
}

void GuiReteta::connectSignals() {
	QObject::connect(btnAdaugaRandom, &QPushButton::clicked, this, &GuiReteta::adaugaRandom);
	QObject::connect(btnExportaHtml, &QPushButton::clicked, this, &GuiReteta::exporta);
	QObject::connect(btnGoleste, &QPushButton::clicked, this, &GuiReteta::goleste);
	QObject::connect(this, &QWidget::close, this, [this]() {
		recipe.stergeObserver(this);
		});
}

void GuiReteta::loadReteta() {
	const auto& recp = recipe.getReteta();
	reteta->clear();
	for (const auto& m : recp) {
		reteta->addItem(QString::fromStdString(m.getDenumire()));
	}
}

void GuiReteta::adaugaRandom() {
	auto numar = txtAdaugaRandom->text().toInt();
	txtAdaugaRandom->clear();
	//const auto& lista = service.getLista();
	try {
		recipe.adaugaRandom(service.getLista(), numar);
		//const auto& retetaRandom = recipe.getReteta();
		/*
		for (const auto& medicament : retetaRandom) {
			reteta->addItem(QString::fromStdString(medicament.getDenumire()));
		}*/
		loadReteta();
	}
	catch (const RetetaExceptii& msg) {
		QMessageBox::warning(nullptr, "Warning", QString::fromStdString(msg.getMesage()));
	}
}

void GuiReteta::exporta() {
	auto fileName = txtExport->text().toStdString();
	recipe.exportHTML(fileName);
}

void GuiReteta::goleste() {
	recipe.golesteReteta();
	const auto& ret = recipe.getReteta();
	if (ret.size() == 0) {
		reteta->clear();
	}
	else {
		QMessageBox::warning(nullptr, "Warning", "Nu s-a putut goli reteta!");
	}

}

void GuiReteta::update() {
	loadReteta();
}

GuiRetetaDesene::GuiRetetaDesene(Reteta& reteta) : reteta{ reteta } {
	reteta.adaugaObserver(this);
	connect();
}

void GuiRetetaDesene::connect() {
	QObject::connect(this, &QWidget::close, this, [&]() {
		reteta.stergeObserver(this);
		});
}

void GuiRetetaDesene::paintEvent(QPaintEvent*) {
	QPainter painter{ this };
	int x = 10;
	const auto& recp = reteta.getReteta();
	int size = (int)recp.size();
	for (int i = 0; i < size; i++) {
		painter.drawRect(x, 10, 20, size * 10);
		x += 30;
	}
}

void GuiRetetaDesene::update() {
	repaint();
}