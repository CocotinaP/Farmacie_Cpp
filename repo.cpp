#include "repo.h"
#include "exceptii.h"
#include <iostream>

using std::pair;

void RepoMedicamente::adauga(const Medicament& medicament) {
	medicamente.push_back(medicament);
}

void RepoMedicamente::sterge(const int& id) {
	const int poz = cautaId(id);
	if (poz != -1) {
		medicamente.erase(medicamente.begin() + poz);
		//medicamente.erase(poz);
	}
	else {
		throw(RepoExceptii("Nu s-a gasit medicamentul!\n"));
	}
}

void RepoMedicamente::modifica(const int& id, const string& denumire, const int& pret, const string& producator, const string& substantaActiva) {
	const int poz = cautaId(id);
	if (poz != -1) {
		this->medicamente[poz].setDenumire(denumire);
		this->medicamente[poz].setPret(pret);
		this->medicamente[poz].setProducator(producator);
		this->medicamente[poz].setSubstantaActiva(substantaActiva);
	}
	else {
		throw(RepoExceptii("Nu s-a gasit medicamentul!\n"));
	}
}

int RepoMedicamente::cautaId(const int& id) const {
	/*
	for (int pozitie = 0; pozitie < (int)this->medicamente.size(); pozitie++) {
		if (this->medicamente[pozitie].getId() == id) {
			return pozitie;
		}
	}*/
	int nr = -1;
	for (const auto& x : this->medicamente) {
		nr++;
		if (x.getId() == id) {
			return nr;
		}
	}
	return -1;
}

int RepoMedicamente::cautaDenumire(const string& denumire) const {
	int pozitie = -1;
	/*
	for (pozitie = 0; pozitie < (int)this->medicamente.size(); pozitie++) {
		if (this->medicamente[pozitie].getDenumire() == denumire) {
			return pozitie;
		}
	}*/
	for (const auto& x : this->medicamente) {
		pozitie++;
		if (x.getDenumire() == denumire) {
			return pozitie;
		}
	}
	return -1;
}

vector<Medicament> RepoMedicamente::getAll() {
	return medicamente;
}

void RepoFile::loadFromFile() {
	ifstream in(fileName);
	if (!in.is_open()) {
		throw RepoExceptii("Nu s-a putut deschide fisierul: " + fileName);

	}
	while (!in.eof()) {
		string id;
		std::getline(in, id, ',');
		int idnr = 0;
		for (int i = 0; id[i]; i++) {
			idnr = idnr * 10 + (id[i] - '0');
		}
		string nume;
		std::getline(in, nume, ',');
		string pret;
		std::getline(in, pret, ',');
		int pretnr = 0;
		for (int i = 0; pret[i]; i++) {
			pretnr = pretnr * 10 + (pret[i] - '0');
		}
		string producator, substantaActvia;
		std::getline(in, producator, ',');
		std::getline(in, substantaActvia);
		Medicament m{ idnr, nume, pretnr, producator, substantaActvia };
		RepoMedicamente::adauga(m);
	}
	in.close();
}

void RepoFile::writeToFile() {
	ofstream out(fileName);
	if (!out.is_open()) {
		throw RepoExceptii("Nu s-a putut deschide fisierul: " + fileName);
	}
	for (auto& m : getAll()) {
		out << m.getId() << ',' << m.getDenumire() << ',' << m.getPret() << ',' << m.getProducator() << ',' << m.getSubstantaActiva() << "\n";
	}
	out.close();
}

RepoNou::RepoNou(float prob) : probabilitate{ prob } {
	medicamente.clear();
}

void RepoNou::determinaSanse() {
	const auto prob = int(probabilitate * 10);
	const int nr = rand() % 10;
	if (nr <= prob) {
		return;
	}
	throw RepoExceptii("Nu e bun!\n");
}

void RepoNou::adauga(const Medicament& medicament) {
	determinaSanse();
	medicamente.insert(pair<int, Medicament>(medicament.getId(), medicament));
}

void RepoNou::sterge(const int& id) {
	determinaSanse();
	medicamente.erase(id);
}

void RepoNou::modifica(const int& id, const string& denumire, const int& pret, const string& producator, const string& substantaActiva) {
	determinaSanse();
	for (auto& i : medicamente) {
		if (i.first == id) {
			Medicament m2{ id, denumire, pret, producator, substantaActiva };
			medicamente.erase(id);
			medicamente.insert(pair<int, Medicament>(id, m2));
			break;
		}
	}
}


int RepoNou::cautaId(const int& id) const {
	int poz = -1;
	for (const auto& i : medicamente) {
		poz += 1;
		if (i.first == id) {
			return poz;
		}
	}
	return -1;
}


int RepoNou::cautaDenumire(const string& denumire) const {
	int poz = -1;
	for (const auto& i : medicamente) {
		poz += 1;
		if (i.second.getDenumire() == denumire) {
			return poz;
		}
	}
	return -1;
}

vector<Medicament> RepoNou::getAll() {
	vector<Medicament> all;
	determinaSanse();
	all.clear();
	for (auto& it : medicamente) {
		all.push_back(it.second);
	}
	return all;
}