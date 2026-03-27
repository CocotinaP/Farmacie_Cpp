#ifndef REPO_H_
#define REPO_H_
#include "domain.h"
#include <vector>
#include <map>
#include <fstream>
#include "MyVector.h"

using std::vector;
using std::ifstream;
using std::map;
using std::ofstream;

class RepoAbstract {
public:
	virtual void adauga(const Medicament& medicament) = 0;
	virtual void sterge(const int& id) = 0;
	virtual void modifica(const int& id, const string& denumire, const int& pret, const string& producator, const string& substantaActiva) = 0;
	virtual int cautaId(const int& id) const = 0;
	virtual int cautaDenumire(const string& denumire) const = 0;
	virtual vector<Medicament> getAll() = 0;
	virtual ~RepoAbstract() = default;
};

class RepoMedicamente : public RepoAbstract {
private:

	//vector<Medicament> medicamente;
	vector<Medicament> medicamente;

public:

	RepoMedicamente(const RepoMedicamente& ot) = delete;
	RepoMedicamente() = default;
	/*
	RepoMedicamente(const VectorDinamic<Medicament>& medicamente) : medicamente{ medicamente } {

	}*/

	/*
	* Adauga un medicament in lista.
	* @param: medicament - Medicament, medicamentul ce trebuie adaugat in lista.
	*/
	virtual void adauga(const Medicament& medicament) override;

	/*
	* Sterge un medicament din lista.
	* @param: id - nr. nat. nenul, id-ul medicamentului ce trebuie sters.
	* @throw: exceptie - daca medicamentul nu se afla in lista
	*/
	virtual void sterge(const int& id) override;

	/*
	* Modifica un medicament.
	* @param: id - nr. nat. nenul, id-ul medicamentului ce trebuie modificat
	*		: denumire - string, denumirea cu care se modifica
	*		: pret - nr. nat. nenul, pretul cu care se modifica
	*		: producator - string, producatorul modificat
	*		: substantaActiva - string, substanta activa ce se modifica
	* @throw: exceptie - daca medicamentul nu se afla in lista
	*/
	virtual void modifica(const int& id, const string& denumire, const int& pret, const string& producator, const string& substantaActiva) override;

	/*
	* Cauta un medicament in lista (dupa id).
	* @param: id - id-ul medicamentului ce trebuie cautat
	* @return: pozitie - pozitia elementului in lista
	*		 : -1 - daca elementul nu se afla in lista.
	*/
	int cautaId(const int& id) const override;

	/*
	* Cauta un medicament in lista (dupa denumire).
	* @param: denumire - string, denumirea medicamentului ce trebuie cautat
	* @return: pozitie - pozitia elementului in lista
	*		 : -1 - daca elementul nu se afla in lista.
	*/
	int cautaDenumire(const string& denumire) const override;

	/*
	* Retunreaza lista medicamentelor.
	* @return: medicamente - lista de medicamente.
	*/
	vector<Medicament> getAll() override;

	virtual ~RepoMedicamente() = default;
};

class RepoFile : public RepoMedicamente {
private:
	string fileName;
	void loadFromFile();
	void writeToFile();
public:
	RepoFile(const string& fileName) : RepoMedicamente(), fileName{ fileName } {
		loadFromFile();
	}

	void adauga(const Medicament& medicament) override {
		RepoMedicamente::adauga(medicament);
		writeToFile();
	}

	void sterge(const int& id) override {
		RepoMedicamente::sterge(id);
		writeToFile();
	}

	void modifica(const int& id, const string& denumire, const int& pret, const string& producator, const string& substantaActiva) override {
		RepoMedicamente::modifica(id, denumire, pret, producator, substantaActiva);
		writeToFile();
	}
};

class RepoNou : public RepoAbstract {
private:
	float probabilitate;
	map<int, Medicament> medicamente;
	void determinaSanse();
public:
	RepoNou() = default;

	explicit RepoNou(float prob);
	void adauga(const Medicament& medicament) override;
	void sterge(const int& id) override;
	void modifica(const int& id, const string& denumire, const int& pret, const string& producator, const string& substantaActiva) override;
	int cautaId(const int& id) const override;
	int cautaDenumire(const string& denumire) const override;
	vector<Medicament> getAll() override;
};

#endif // !REPO_H_
