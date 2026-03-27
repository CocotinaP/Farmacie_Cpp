#ifndef RETETA_H_

#define RETETA_H_

#include <vector>
#include "domain.h"
#include "observer.h"

using std::vector;

class Reteta : public Observable {
private:

	vector<Medicament> reteta;

public:
	
	Reteta();

	/*
	* Functia adauga un medicament in reteta.
	* @param: medicament - medicament, medicamentul ce trebuie adugat
	*/
	void adaugaMedicamentInReteta(const Medicament& medicament);

	/*
	* Functia adauga medicamente random in reteta.
	* @param: nr - nr. nat. nenul, numarul de medicamente ce trebuie adaugate.
	*		: medicamente - lista de medicamente din care se aleg medicamentele vor fi puse in reteta
	*/
	void adaugaRandom(const vector<Medicament>& medicamente, int nr);

	/*
	* Sterge toate medicamentele din reteta.
	*/
	void golesteReteta() noexcept;

	/*
	* Exporta reteta intr-un fisier html.
	* @param: fileName - string, numele fisierului in care se exporta
	*/
	void exportHTML(const string& fileName);

	/*
	* Returneaza reteta.
	*/
	vector<Medicament> getReteta();
};

#endif // !RETETA_H_
