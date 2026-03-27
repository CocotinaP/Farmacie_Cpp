#include "service.h"
#include "exceptii.h"
#include <algorithm>

int ServiceMedicamente::genereazaId() {
	int id, max = 0;
	for (const auto& x : repo.getAll()) {
		if (x.getId() > max) {
			max = x.getId();
		}
	}
	id = max + 1;
	return id;
}

bool ServiceMedicamente::existaMedicament(const vector<Medicament>& lista, const string& denumire, const int& pret, const string& producator, const string& substantaActiva) {
	for (const auto& el : lista) {
		if (el.getDenumire() == denumire && el.getPret() == pret && el.getProducator() == producator && el.getSubstantaActiva() == substantaActiva) {
			return true;
		}
	}
	return false;
}

void ServiceMedicamente::adaugaMedicament(const string& denumire, const int& pret, const string& producator, const string& substantaActiva) {
	Validator validator;
	validator.valideazaMedicament(denumire, pret, producator, substantaActiva);
	const auto& v = repo.getAll();
	if (existaMedicament(v, denumire, pret, producator, substantaActiva) == true) {
		throw (RepoExceptii("Medicament deja existent!\n"));
	}
	else {
		const int id = genereazaId();
		Medicament medicament(id, denumire, pret, producator, substantaActiva);
		repo.adauga(medicament);
		undoActions.push_back(std::make_unique<UndoAdauga>(repo, medicament));
	}
}

void ServiceMedicamente::stergeMedicament(const int& id) {
	const auto& l = getLista();
	const int poz = cautaMedicamentId(id);
	repo.sterge(id);
	if (poz != -1) {
		const Medicament& m = l[poz];
		undoActions.push_back(std::make_unique<UndoSterge>(repo, m));
	}
}

void ServiceMedicamente::modificaMedicament(const int& id, const string& denumire, const int& pret, const string& producator, const string& substantaActiva) {
	Validator validator;
	validator.valideazaMedicament(denumire, pret, producator, substantaActiva);
	const int poz = cautaMedicamentId(id);
	if (poz != -1) {
		const auto& l = getLista();
		const Medicament& m = l[poz];
		undoActions.push_back(std::make_unique<UndoModifica>(repo, m));
	}
	repo.modifica(id, denumire, pret, producator, substantaActiva);
}

void ServiceMedicamente::undo() {
	if (undoActions.empty()) {
		throw RepoExceptii("Nu mai sunt operatii disponibile!\n");
	}
	undoActions.back()->doUndo();
	undoActions.pop_back();
}

vector<Medicament> ServiceMedicamente::filtreazaMedicamente(const int& pret, const string& substantaActiva, const int& tip) {
	vector<Medicament> listaFiltrata;
	for (const auto& medicament : getLista()) {
		if (tip == 1) {
			if (medicament.getPret() == pret) {
				listaFiltrata.push_back(medicament);
			}
		}
		else {
			if (medicament.getSubstantaActiva() == substantaActiva) {
				listaFiltrata.push_back(medicament);
			}
		}
	}
	return listaFiltrata;

}

/*
vector<Medicament> ServiceMedicamente::sortareGenerala(bool(*functieMaiMare)(const Medicament&, const Medicament&)) {
	vector<Medicament> v = repo.getAll(); // facem o copie
	for (int i = 0; i < v.size(); i++) {
		for (int j = i + 1; j < v.size(); j++) {
			if (functieMaiMare(v[i], v[j])) {
				Medicament aux = v[i];
				v[i] = v[j];
				v[j] = aux;
			}
		}
	}
	return v;
}*/

vector<Medicament> ServiceMedicamente::sorteazaDupaDenumire() {
	//return sortareGenerala(cmpDenumire);
	auto v = this->getLista();
	sort(v.begin(), v.end(), cmpDenumire);
	return v;
}

vector<Medicament> ServiceMedicamente::sorteazaDupaProducator() {
	//return sortareGenerala(cmpProducator);
	auto v = this->getLista();
	sort(v.begin(), v.end(), cmpProducator);
	return v;
}

vector<Medicament> ServiceMedicamente::sorteazaDupaSubstantaActivaSiPret() {
	auto v = this->getLista();
	/*
	return sortareGenerala([](const Medicament& m1, const Medicament& m2) {
		if (m1.getSubstantaActiva() == m2.getSubstantaActiva()) {
			return m1.getPret() > m2.getPret();
		}
		return m1.getSubstantaActiva() > m2.getSubstantaActiva();
		});*/
	sort(v.begin(), v.end(), [](const Medicament& m1, const Medicament& m2) {
		if (m1.getSubstantaActiva() == m2.getSubstantaActiva()) {
			return m1.getPret() < m2.getPret();
		}
		return m1.getSubstantaActiva() < m2.getSubstantaActiva();
		});
	return v;
}

map<string, DTOMedicament> ServiceMedicamente::raport() {
	map<string, DTOMedicament> mp;
	//vector <Medicament> l;
	const auto& l = repo.getAll();
	
	for (const auto& m : l) {
		DTOMedicament d(m.getSubstantaActiva());
		mp[m.getSubstantaActiva()] = d;
	}
	for (const auto& m : l) {
		const int nr = mp[m.getSubstantaActiva()].getCount() + 1;
		DTOMedicament val(m.getSubstantaActiva(), nr);
		mp[m.getSubstantaActiva()] = val;
	}
	return mp;
}

int ServiceMedicamente::cautaMedicamentId(const int& id) const  noexcept{
	return repo.cautaId(id);
}

int ServiceMedicamente::cautaMedicamentDenumire(const string& denumire) const {
	return repo.cautaDenumire(denumire);
}

vector<Medicament> ServiceMedicamente::getLista() const {
	return repo.getAll();
}