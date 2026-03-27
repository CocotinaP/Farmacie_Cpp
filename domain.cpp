#include "domain.h"
#include "exceptii.h"
#include <string.h>

using std::string;

int Medicament::getId() const noexcept{
	return id;
}

string Medicament::getDenumire() const {
	return denumire;
}

int Medicament::getPret() const noexcept{
	return pret;
}

string Medicament::getProducator() const {
	return producator;
}

string Medicament::getSubstantaActiva() const {
	return substantaActiva;
}

void Medicament::setDenumire(string denumireNoua) {
	denumire = denumireNoua;
}

void Medicament::setPret(int pretNou) noexcept {
	pret = pretNou;
}

void Medicament::setProducator(string producatorNou) {
	producator = producatorNou;
}

void Medicament::setSubstantaActiva(string substantaActivaNoua) {
	substantaActiva = substantaActivaNoua;
}

bool cmpDenumire(const Medicament& medicament1, const Medicament& medicament2) {
	if (medicament1.getDenumire() < medicament2.getDenumire()) {
		return true;
	}
	return false;
}

bool cmpProducator(const Medicament& medicament1, const Medicament& medicament2) {
	if (medicament1.getProducator() < medicament2.getProducator()) {
		return true;
	}
	return false;
}

bool cmpPret(const Medicament& medicament1, const Medicament& medicament2) noexcept{
	if (medicament1.getPret() < medicament2.getPret()) {
		return true;
	}
	return false;
}

bool cmpSubstantaActiva(const Medicament& medicament1, const Medicament& medicament2) {
	if (medicament1.getSubstantaActiva() < medicament2.getSubstantaActiva()) {
		return true;
	}
	return false;
}

void Validator::valideazaMedicament(const string& denumire, const int& pret, const string& producator, const string& substantaActiva) const {
	string erori = "";
	if (denumire.size() == 0) {
		erori.append("Denumirea nu poate fi vida!\n");
	}
	if (pret <= 0) {
		erori.append("Pretul trebuie sa fie un numar natural nenul!\n");
	}
	if (producator.size() == 0) {
		erori.append("Producatorul nu poate fi vid!\n");
	}
	if (substantaActiva.size() == 0) {
		erori.append("Substanta activa nu poate fi vida!\n");
	}
	if (erori.size() > 0) {
		throw ValidatorExceptii(erori);
	}
}