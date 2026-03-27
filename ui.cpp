#include "ui.h"
#include "exceptii.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using std::cout;
using std::cin;
using std::string;
using std::getline;
using std::reverse;
using std::vector;

void Console::printMedicament(const Medicament& m) const {
	cout << "Id: " << m.getId() << ", Denumire: " << m.getDenumire() << ", Pret: " << m.getPret() << ", Producator: " << m.getProducator() << ", Substanta activa: " << m.getSubstantaActiva() << ";\n";
}

void Console::printListaInvers(const vector<Medicament>& l) const {
	if (l.size() == 0) {
		cout << "Lista este goala!\n";
	}
	else {
		const auto i = l.size();
		int j = (int)i;
		j -= 1;
		for (j; j >= 0; j--) {
			printMedicament(l[j]);
		}
		/*
		for (const auto& x : reverse(l)) {
			printMedicament(x);
		}*/
	}
}

void Console::printLista(const vector<Medicament>& lista) {
	if (lista.size() == 0) {
		cout << "Lista este goala!\n";
	}
	else {
		try {
			for (const auto& m : lista) {
				printMedicament(m);
			}
		}
		catch (const RepoExceptii& msg) {
			cout << msg.getMesage();
		}
	}
}

void Console::adaugaMedicament() {
	string denumire, producator, substantaActiva;
	int pret;
	cout << "Introduceti datele medicamentului pe care doriti sa il adugati:\n";
	cout << "Denumire: ";
	cin.ignore();
	getline(cin, denumire);
	cout << "Pret: ";
	cin >> pret;
	cin.ignore();
	cout << "Producator: ";
	getline(cin, producator);
	cout << "Substanta activa: ";
	getline(cin, substantaActiva);
	try {
		service.adaugaMedicament(denumire, pret, producator, substantaActiva);
		cout << "Adaugare realizata cu succes!\n";
	}
	catch (const RepoExceptii& msg) {
		cout << msg.getMesage();
	}
}

void Console::stergeMedicament() {
	int id;
	cout << "Introduceti id-ul medicamentului pe care doriti sa il stergeti: ";
	cin >> id;
	try {
		service.stergeMedicament(id);
		cout << "Stergere realizata cu succes!\n";
	}
	catch (const RepoExceptii& msg) {
		cout << msg.getMesage();
	}
}

void Console::modificaMedicament() {
	int id, pret;
	string denumire, producator, substantaActiva;
	cout << "Introduceti id-ul medicamentului pe care doriti sa il modificati: ";
	cin >> id;
	cout << "Introduceti noile date:\n";
	cout << "Denumire: ";
	cin.ignore();
	getline(cin, denumire);
	cout << "Pret: ";
	cin >> pret;
	cin.ignore();
	cout << "Producator: ";
	getline(cin, producator);
	cout << "Substanta activa: ";
	getline(cin, substantaActiva);
	try {
		service.modificaMedicament(id, denumire, pret, producator, substantaActiva);
		cout << "Modificare realizata cu succes!\n";
	}
	catch (const RepoExceptii& msg) {
		cout << msg.getMesage();
	}
}

void Console::filtrareMedicamente() {
	vector<Medicament> listaFiltrata;
	int crt;
	cout << "Introduceti criteriul de filtrare: 1 - pret; 2 - substanta activa: ";
	cin >> crt;
	if (crt == 1) {
		int pret;
		cout << "Introduceti pretul dupa care se face filtrarea: ";
		cin >> pret;
		listaFiltrata = service.filtreazaMedicamente(pret, "", 1);
	}
	else {
		if (crt == 2) {
			string substantaActiva;
			cout << "Introduceti substanta activa dupa care se face filtrarea: ";
			cin.ignore();
			getline(cin, substantaActiva);
			listaFiltrata = service.filtreazaMedicamente(0, substantaActiva, 2);
		}
		else {
			cout << "Criteriu invalid!\n";
		}
	}

	if (listaFiltrata.size() != 0) {
		cout << "Lista filtrata este:\n";
		printLista(listaFiltrata);
	}
	else {
		cout << "Nu s-au gasit rezultate!\n";
	}

}

void Console::cautaMedicament() {
	string denumire;
	cout << "Introduceti denuimrea medicamentului cautat: ";
	cin.ignore();
	getline(cin, denumire);
	const int pozitie = service.cautaMedicamentDenumire(denumire);
	if (pozitie == -1) {
		cout << "Nu s-au gasit rezultate!\n";
	}
	else {
		cout << "Medicamentul cautat este:\n";
		const auto& l = service.getLista();
		printMedicament(l[pozitie]);
	}
}

void Console::sorteaza() {
	int crt, ordine;
	vector<Medicament> ls;
	cout << "Introduceti criteriul de sortare: 1 - dupa denumire; 2 - dupa producator; 3 - dupa substana activa + pret: ";
	cin >> crt;
	cout << "1 - crescator sau 2 - descrescator?: ";
	cin >> ordine;
	switch (crt) {
	case 1:
		ls = service.sorteazaDupaDenumire();
		break;
	case 2:
		ls = service.sorteazaDupaProducator();
		break;
	case 3:
		ls = service.sorteazaDupaSubstantaActivaSiPret();
		break;
	default:
		cout << "Criteriu invalid!\n";
	}
	cout << "Lista sortata este:\n";
	if (ordine == 1) {
		printLista(ls);
	}
	else {
		printListaInvers(ls);
	}
}

void Console::reteta(Reteta& recipe) {
	cout << "1 - Afiseaza reteta.\n";
	cout << "2 - Adauga medicament in reteta.\n";
	cout << "3 - Goleste reteta.\n";
	cout << "4 - Adauga medicamente random.\n";
	cout << "5 - Exporta reteta.\n";
	cout << "Comanda: ";
	string denumire;
	int cmd;
	cin >> cmd;
	if (cmd == 2) {
		cout << "Denumire medicament: ";
		cin.ignore();
		getline(cin, denumire);
		const auto& list = service.getLista();
		int poz;
		poz = service.cautaMedicamentDenumire(denumire);
		if (poz != -1) {
			recipe.adaugaMedicamentInReteta(list[poz]);
			cout << "Medicament adugat cu succes!\n";
		}
		else {
			cout << "Medicament inexistent!\n";
		}
	}
	else {
		if (cmd == 1) {
			cout << "Reteta este:\n";
			printLista(recipe.getReteta());
		}
		else {
			if (cmd == 3) {
				recipe.golesteReteta();
				cout << "Reteta stearsa cu succes!\n";
			}
			else {
				if (cmd == 4) {
					cout << "Introduceti numarul de medicamente: ";
					int nr;
					cin >> nr;
					try {
						recipe.adaugaRandom(service.getLista(), nr);
						cout << "Adaugare realizata cu succes!\n";
					}
					catch (const RetetaExceptii& m) {
						cout << m.getMesage();
					}
				}
				else {
					if (cmd == 5) {
						cout << "Introduceti numele fisierului: ";
						string nume;
						cin.ignore();
						getline(cin, nume);
						recipe.exportHTML(nume);
					}
					else {
						cout << "Comanda invalida!\n";
					}
				}
			}
		}
	}
	cout << "Dimensiunea retetei: ";
	cout << recipe.getReteta().size() << "\n";

}

void Console::raport() {
	map <string, DTOMedicament> rp;
	rp = service.raport();
	cout << "Raport:\n";
	for (const auto& r : rp) {
		cout << r.second.getType() << ": " << r.second.getCount() << "\n";
	}
}

void Console::undo() {
	try {
		service.undo();
		cout << "Undo reazlizat cu succes!\n";
	}
	catch (const RepoExceptii& msg) {
		cout << msg.getMesage();
	}
}

void Console::adaugaLaInceput() {
	try {
		service.adaugaMedicament("Zinat", 23, "Europharm", "Cefuroxima");
		service.adaugaMedicament("Paracetamol", 12, "Biofarm", "Paracetamol");
		service.adaugaMedicament("Augumentin", 45, "Europharm", "Amoxicilina");
		service.adaugaMedicament("Cefrox", 54, "Fiterman Phrama", "Cefuroxima");
		service.adaugaMedicament("Parasinus", 21, "Terapia", "Paracetamol");
		service.adaugaMedicament("Tantum verde", 67, "Angelini", "Clorhidrat de benizdamina");
		service.adaugaMedicament("Panadol", 32, "Terapia", "Paracetamol");
		service.adaugaMedicament("Aciclovir", 32, "Biofarm", "Aciclovir");
		service.adaugaMedicament("Algocalmin", 25, "Fiterman Pharma", "Metamizol sodic monohidrat");
		service.adaugaMedicament("Cefort", 89, "Terapia", "Ceftriaxona");
	}
	catch (const RepoExceptii msg) {
		cout << msg.getMesage();
	}
}

void Console::start() {
	Reteta recipe;
	bool finish = false;
	int cmd;
	adaugaLaInceput();
	while (!finish) {
		cout << "Meniul aplicatiei:\n";
		cout << "0 - Inchide aplicatia.\n";
		cout << "1 - Afiseaza lista curenta.\n";
		cout << "2 - Adauga un medicament.\n";
		cout << "3 - Sterge un medicament.\n";
		cout << "4 - Modifica un medicament.\n";
		cout << "5 - Cauta un medicament.\n";
		cout << "6 - Filtreaza medicamentele.\n";
		cout << "7 - Sorteaza medicamentele.\n";
		cout << "8 - Reteta.\n";
		cout << "9 - Raport.\n";
		cout << "10 - Undo.\n";
		cout << "Tastati comanda: ";
		cin >> cmd;
		switch (cmd) {
		case 0:
			finish = true;
			break;
		case 1:
			cout << "Lista curenta de medicamente este: \n";
			try{
			printLista(service.getLista());
			}
			catch (const RepoExceptii& msg) {
				cout << msg.getMesage();
			}
			break;
		case 2:
			adaugaMedicament();
			break;
		case 3:
			stergeMedicament();
			break;
		case 4:
			modificaMedicament();
			break;
		case 5:
			try {
				cautaMedicament();
			}
			catch (const RepoExceptii& msg) {
				cout << msg.getMesage();
			}
			break;
		case 6:
			try {
				filtrareMedicamente();
			}
			catch (const RepoExceptii& msg) {
				cout << msg.getMesage();
			}
			break;
		case 7:
			try {
				sorteaza();
			}
			catch (const RepoExceptii& msg) {
				cout << msg.getMesage();
			}
			break;
		case 8:
			try {
				reteta(recipe);
			}
			catch (const RepoExceptii& msg) {
				cout << msg.getMesage();
			}
			break;
		case 9:
			try {
				raport();
			}
			catch (const RepoExceptii& msg) {
				cout << msg.getMesage();
			}
			break;
		case 10:
			try {
				undo();
			}
			catch (const RepoExceptii& msg) {
				cout << msg.getMesage();
			}
			break;
		default:
			cout << "Comanda invalida!\n";
		}
		
	}

}