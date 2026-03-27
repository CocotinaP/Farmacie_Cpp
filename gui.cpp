#include "gui.h"

Gui::Gui(Reteta& recipe, ServiceMedicamente& service) : recipe{ recipe }, service { service } {
	initGui();
	load();
	connectSignals();
	conectButoaneRaport();
}

void Gui::initGui() {
	setLayout(mainLy);
	mainLy->addWidget(tabelMedicamente);
	mainLy->addWidget(listaMedicamente);
	QVBoxLayout* leftLy = new QVBoxLayout;
	QFormLayout* formLy = new QFormLayout;
	formLy->addRow("Denumire", txtDenumire);
	formLy->addRow("Pret", txtPret);
	formLy->addRow("Producator", txtProducator);
	formLy->addRow("Substanta activa", txtSubstantaActiva);
	formLy->addRow("Numarul pt. reteta random", txtNrRetetaRandom);
	leftLy->addLayout(formLy);
	btnAdauga = new QPushButton("Adauga");
	btnSterge = new QPushButton("Sterge");
	btnModifica = new QPushButton("Modifica");
	btnRaport = new QPushButton("Raport");
	btnCauta = new QPushButton("Cauta");
	btnSorteazaDupaDenumire = new QPushButton("Sorteaza dupa denumire");
	btnSorteazaDupaProducator = new QPushButton("Sorteaza dupa producator");
	btnSorteazaDupaSubstantaActivaSiPret = new QPushButton("Sorteaza dupa substanta activa si pret");
	btnFiltreazaDupaPret = new QPushButton("Filtreaza dupa pret");
	btnFiltreazaDupaSubstantaActiva = new QPushButton("Filtreaza dupa substanta activa");
	btnReteta = new QPushButton("Reteta");
	btnAdaugaReteta = new QPushButton("Adauga medicament in reteta");
	btnAdauaRetetaRandom = new QPushButton("Adauga random in reteta");
	btnGolesteReteta = new QPushButton("Goleste reteta");
	btnRetetaDesene = new QPushButton("Reteta grafic");
	btnUndo = new QPushButton("Undo");
	QHBoxLayout* btnsLy1 = new QHBoxLayout;
	btnsLy1->addWidget(btnAdauga);
	btnsLy1->addWidget(btnSterge);
	btnsLy1->addWidget(btnModifica);
	btnsLy1->addWidget(btnCauta);
	btnsLy1->addWidget(btnRaport);
	QHBoxLayout* btnsLy2 = new QHBoxLayout();
	btnsLy2->addWidget(btnSorteazaDupaDenumire);
	btnsLy2->addWidget(btnSorteazaDupaProducator);
	btnsLy2->addWidget(btnSorteazaDupaSubstantaActivaSiPret);
	QHBoxLayout* btnsLy3 = new QHBoxLayout();
	btnsLy3->addWidget(btnFiltreazaDupaPret);
	btnsLy3->addWidget(btnFiltreazaDupaSubstantaActiva);
	retetaLy->addWidget(btnReteta);
	retetaLy->addWidget(btnAdaugaReteta);
	retetaLy->addWidget(btnAdauaRetetaRandom);
	retetaLy->addWidget(btnGolesteReteta);
	retetaLy->addWidget(btnRetetaDesene);
	btnsLy3->addWidget(btnUndo);
	leftLy->addLayout(btnsLy1);
	leftLy->addLayout(btnsLy2);
	leftLy->addLayout(btnsLy3);
	leftLy->addLayout(retetaLy);
	mainLy->addLayout(leftLy);
	mainLy->addWidget(rezultate);
	auto rp = service.raport();
	for (auto const& s : rp) {
		QPushButton* buton = new QPushButton(QString::fromStdString(s.first));
		vectbtn.push_back(buton);
	}
	for (auto b : vectbtn) {
		lybtntip->addWidget(b);
	}
	mainLy->addLayout(lybtntip);
}

void Gui::load() {
	auto lista = service.getLista();
	listaMedicamente->clear();
	/*
	tabelMedicamente->clear();
	tabelMedicamente->setItem(0, 0, new QTableWidgetItem("Denumire"));
	tabelMedicamente->setItem(0, 1, new QTableWidgetItem("Pret"));
	tabelMedicamente->setItem(0, 2, new QTableWidgetItem("Producator"));
	tabelMedicamente->setItem(0, 3, new QTableWidgetItem("Substanta activa"));*/
	model = new MyTableModel{ lista };
	tabelMedicamente->setModel(model);
	int cnt = 0;
	for (const auto& medicament : lista) {
		cnt += 1;
		listaMedicamente->addItem(QString::fromStdString(medicament.getDenumire()));
		/*
		tabelMedicamente->setItem(cnt, 0, new QTableWidgetItem(QString::fromStdString(medicament.getDenumire())));
		tabelMedicamente->setItem(cnt, 1, new QTableWidgetItem(QString::number(medicament.getPret())));
		tabelMedicamente->setItem(cnt, 2, new QTableWidgetItem(QString::fromStdString(medicament.getProducator())));
		tabelMedicamente->setItem(cnt, 3, new QTableWidgetItem(QString::fromStdString(medicament.getSubstantaActiva())));*/
	}
}

void Gui::connectSignals() {
	QObject::connect(btnAdauga, &QPushButton::clicked, this, &Gui::adauga);
	QObject::connect(btnFiltreazaDupaPret, &QPushButton::clicked, this, &Gui::filtreazaPret);
	QObject::connect(btnFiltreazaDupaSubstantaActiva, &QPushButton::clicked, this, &Gui::filtreazaSubstantaActiva);
	QObject::connect(btnSorteazaDupaDenumire, &QPushButton::clicked, this, &Gui::sorteazaDenumire);
	QObject::connect(btnSorteazaDupaProducator, &QPushButton::clicked, this, &Gui::sorteazaProducator);
	QObject::connect(btnSorteazaDupaSubstantaActivaSiPret, &QPushButton::clicked, this, &Gui::sorteazaDupaSubstantaActivaSiPret);
	QObject::connect(btnRaport, &QPushButton::clicked, this, &Gui::raport);
	QObject::connect(listaMedicamente, &QListWidget::itemClicked, this, &Gui::detalii);
	QObject::connect(btnSterge, &QPushButton::clicked, this, &Gui::sterge);
	QObject::connect(btnModifica, &QPushButton::clicked, this, &Gui::modifica);
	QObject::connect(btnUndo, &QPushButton::clicked, this, &Gui::undo);
	QObject::connect(btnReteta, &QPushButton::clicked, this, &Gui::reteta);
	QObject::connect(btnCauta, &QPushButton::clicked, this, &Gui::cauta);
	QObject::connect(btnAdaugaReteta, &QPushButton::clicked, this, &Gui::adaugaReteta);
	QObject::connect(btnAdauaRetetaRandom, &QPushButton::clicked, this, &Gui::adaugaRetetaRandom);
	QObject::connect(btnGolesteReteta, &QPushButton::clicked, this, &Gui::golesteReteta);
	QObject::connect(btnRetetaDesene, &QPushButton::clicked, this, &Gui::retetaGrafica);
}

void Gui::conectButoaneRaport() {
	for (auto b : vectbtn) {
		QObject::connect(b, &QPushButton::clicked, this, [this, b]() {
			rezultate->clear();
			auto txt = b->text();
			const auto& rp = service.raport();
			for (const auto& m : rp) {
				if (m.first == txt.toStdString()) {
					//rezultate->addItem(QString::number(m.second.getCount()));
					//QMessageBox::information(this, txt, QString::number(m.second.getCount()));
					QMessageBox* msg = new QMessageBox;
					msg->information(this, txt, QString::number(m.second.getCount()));
					//msg->exec();
				}
			}
			});
	}
}

void Gui::curataTextFielduri() {
	txtDenumire->clear();
	txtPret->clear();
	txtProducator->clear();
	txtSubstantaActiva->clear();
}

/*
void Gui::adauga() {
	try {
		auto denumire = txtDenumire->text().toStdString();
		auto pret = txtPret->text().toInt();
		auto producator = txtProducator->text().toStdString();
		auto substantaActiva = txtSubstantaActiva->text().toStdString();
		service.adaugaMedicament(denumire, pret, producator, substantaActiva);
		load();
		curataTextFielduri();
	}
	catch (const ValidatorExceptii& msg1) {
		QMessageBox::warning(nullptr, "Warning", QString::fromStdString(msg1.getMesage()));
	}
	catch (const RepoExceptii& msg2) {
		QMessageBox::warning(nullptr, "Warning", QString::fromStdString(msg2.getMesage()));
	}
}*/

void Gui::adauga() {
	try {
		auto denumire = txtDenumire->text().toStdString();
		auto pret = txtPret->text().toInt();
		auto producator = txtProducator->text().toStdString();
		auto substantaActiva = txtSubstantaActiva->text().toStdString();
		const auto& rprt = service.raport();
		service.adaugaMedicament(denumire, pret, producator, substantaActiva);
		int ok = 0;
		for (const auto& m : rprt) {
			if (m.first == substantaActiva) {
				ok = 1;
			}
		}
		if (ok == 0) {
			QPushButton* buton = new QPushButton(txtSubstantaActiva->text());
			vectbtn.push_back(buton);
			lybtntip->addWidget(buton);
			conectButoaneRaport();
		}
		load();
		curataTextFielduri();
	}
	catch (const ValidatorExceptii& msg1) {
		QMessageBox::warning(nullptr, "Warning", QString::fromStdString(msg1.getMesage()));
	}
	catch (const RepoExceptii& msg2) {
		QMessageBox::warning(nullptr, "Warning", QString::fromStdString(msg2.getMesage()));
	}
}

void Gui::adaugaReteta() {
	const auto& denumire = txtDenumire->text().toStdString();
	auto pret = txtPret->text().toInt();
	const auto& producator = txtProducator->text().toStdString();
	const auto& substantaActiva = txtSubstantaActiva->text().toStdString();
	Medicament medicament{ id, denumire, pret, producator, substantaActiva };
	//guiReteta.recipe.adaugaMedicamentInReteta(medicament);
	//guiReteta.reteta->addItem(QString::fromStdString(medicament.getDenumire()));
	recipe.adaugaMedicamentInReteta(medicament);
	curataTextFielduri();
}

void Gui::adaugaRetetaRandom() {
	auto numar = txtNrRetetaRandom->text().toInt();
	txtNrRetetaRandom->clear();
	try {
		recipe.adaugaRandom(service.getLista(), numar);
	}
	catch (const RetetaExceptii& msg) {
		QMessageBox::warning(nullptr, "Warning", QString::fromStdString(msg.getMesage()));
	}
}

void Gui::golesteReteta() {
	recipe.golesteReteta();
}

void Gui::retetaGrafica() {
	auto wRetetaGrafica = new GuiRetetaDesene(recipe);
	wRetetaGrafica->show();
}

void Gui::reteta() {
	auto wReteta = new GuiReteta{ recipe, service };
	wReteta->show();
}

void Gui::detalii() {
	auto denumireMedicament = listaMedicamente->currentItem()->text().toStdString();
	auto pozMedicament = service.cautaMedicamentDenumire(denumireMedicament);
	const auto& lista = service.getLista();
	const auto& medicament = lista[pozMedicament];
	txtDenumire->setText(QString::fromStdString(medicament.getDenumire()));
	txtPret->setText(QString::number(medicament.getPret()));
	txtProducator->setText(QString::fromStdString(medicament.getProducator()));
	txtSubstantaActiva->setText(QString::fromStdString(medicament.getSubstantaActiva()));
	id = medicament.getId();
}

void Gui::sterge() {
	service.stergeMedicament(id);
	load();
	curataTextFielduri();
}

void Gui::cauta() {
	auto pozMedicament = service.cautaMedicamentDenumire(txtDenumire->text().toStdString());
	if (pozMedicament != -1) {
		const auto& lista = service.getLista();
		const auto& medicament = lista[pozMedicament];
		txtDenumire->setText(QString::fromStdString(medicament.getDenumire()));
		txtPret->setText(QString::number(medicament.getId()));
		txtProducator->setText(QString::fromStdString(medicament.getProducator()));
		txtSubstantaActiva->setText(QString::fromStdString(medicament.getSubstantaActiva()));
		id = medicament.getId();
	}
	else {
		QMessageBox::warning(nullptr, "Warning", "Nu s-au gasit rezultate!");
	}
}

void Gui::modifica() {
	const auto& denumire = txtDenumire->text().toStdString();
	const auto& pret = txtPret->text().toInt();
	const auto& producator = txtProducator->text().toStdString();
	const auto& substantaActiva = txtSubstantaActiva->text().toStdString();
	service.modificaMedicament(id, denumire, pret, producator, substantaActiva);
	load();
	curataTextFielduri();
}

void Gui::raport() {
	const auto& rprt = service.raport();
	if (rprt.size()) {
		rezultate->clear();
		rezultate->addItem("Raport (substanta activa):");
		for (const auto& medicament : rprt) {
			rezultate->addItem(QString::fromStdString(medicament.first) + ": " + QString::number(medicament.second.getCount()));
		}
	}
	else {
		QMessageBox::warning(nullptr, "Warning", "Nu exista date!");
	}
}

void Gui::filtreazaPret() {
	auto pret = txtPret->text().toInt();
	const auto& listaFiltrata = service.filtreazaMedicamente(pret, "jbj", 1);
	rezultate->clear();
	rezultate->addItem("Lista filtrata dupa pret:");
	if (listaFiltrata.size()) {
		for (const auto& medicament : listaFiltrata) {
			rezultate->addItem(QString::fromStdString(medicament.getDenumire()));
		}
	}
	else {
		rezultate->addItem("Nu s-au gasit rezultate!");
	}
	curataTextFielduri();
}

void Gui::filtreazaSubstantaActiva() {
	auto substantaActiva = txtSubstantaActiva->text().toStdString();
	const auto& listaFiltrata = service.filtreazaMedicamente(1, substantaActiva, 2);
	rezultate->clear();
	rezultate->addItem("Lista filtrata dupa substanta activa:");
	if (listaFiltrata.size()) {
		for (const auto& medicament : listaFiltrata) {
			rezultate->addItem(QString::fromStdString(medicament.getDenumire()));
		}
	}
	else {
		rezultate->addItem("Nu s-au gasit rezultate!");
	}
	curataTextFielduri();
}

void Gui::sorteazaDenumire() {
	const auto& listaSortata = service.sorteazaDupaDenumire();
	rezultate->clear();
	rezultate->addItem("Lista sortata dupa denumire este:");
	if (listaSortata.size()) {
		for (const auto& medicament : listaSortata) {
			rezultate->addItem(QString::fromStdString(medicament.getDenumire()));
		}
	}
	else {
		rezultate->addItem("Lista estev goala!");
	}
}

void Gui::sorteazaProducator() {
	const auto& listaSortata = service.sorteazaDupaProducator();
	rezultate->clear();
	rezultate->addItem("Lista sortata dupa producator este:");
	if (listaSortata.size()) {
		for (const auto& medicament : listaSortata) {
			rezultate->addItem(QString::fromStdString(medicament.getDenumire()));
		}
	}
	else {
		rezultate->addItem("Lista este goala!");
	}
}

void Gui::sorteazaDupaSubstantaActivaSiPret() {
	const auto& listaFiltrata = service.sorteazaDupaSubstantaActivaSiPret();
	rezultate->clear();
	rezultate->addItem("Lista filtrata dupa substanta activa si pret este:");
	if (listaFiltrata.size()) {
		for (const auto& medicament : listaFiltrata) {
			rezultate->addItem(QString::fromStdString(medicament.getDenumire()));
		}
	}
	else {
		rezultate->addItem("Lista este goala!");
	}
}

void Gui::undo() {
	try {
		service.undo();
		load();
	}
	catch (const RepoExceptii& msg) {
		QMessageBox::warning(nullptr, "Warning", QString::fromStdString(msg.getMesage()));
	}
}