#ifndef SERVICE_H_
#define SERVICE_H_
#include "repo.h"
#include <string>
#include "undo.h"
#include <map>
#include <memory>
#include "MyVector.h"

using std::string;
using std::map;
using std::unique_ptr;

class ServiceMedicamente {
private:

	RepoAbstract& repo;
	vector<unique_ptr<ActiuneUndo>> undoActions;

	/*
	* Genereaza un id unic.
	* @return: id - nr. nat. nenul
	*/
	int genereazaId();

	/*
	* Verifica daca exista in lista un medicament cu aceleasi date.
	* @param: lista - vector<Medicament>, lista in care se cauta
	*		: denumire - string, denumirea medicamentului
	*		: pret - nr. nat. nenul, pretul medicamentului
	*		: producator - string, producatorul medicamentului
	*		: substantaActiva - string, substanta activa a medicamentului
	* @return: true - daca medicamentul exista deja in lista
	*		 : false - altfel
	*/
	bool existaMedicament(const vector<Medicament>& lista, const string& denumire, const int& pret, const string& producator, const string& substantaActiva);

	/*
	* Functie generala de sortare.
	* @param: functieMaiMare - functie care compara 2 medicamente, verifica daca are loc relatia mai mare
	        : poate fi orice functie (din afara clasei) care respecta signatura (retunreaza bool si are 2 parametrii Medicament)
			:poate fi o functie lambda (care nu capteaza nicim in caputre list)
	* @return: o lista dupa criteriul dat ca parametru
	*/
	//vector<Medicament> sortareGenerala(bool(*functieMaiMare)(const Medicament&, const Medicament&));

public:

	//Constructorul clasei.
	ServiceMedicamente(RepoAbstract& repo) noexcept : repo{ repo } {

	}

	ServiceMedicamente(const ServiceMedicamente& ot) = delete;
	ServiceMedicamente() = default;

	/*
	* Adauga un medicament in lista.
	* @param: denumire - string, denumirea medicamentului
	*		: pret - nr. nat. nenul, pretul medicamentului
	*		: producator - string, producatorul medicamentului
	*		: substantaActiva - string, substanta activa a medicamentului
	*/
	void adaugaMedicament(const string& denumire, const int& pret, const string& producator, const string& substantaActiva);

	/*
	* Sterge un medicament din lista.
	* @param: id - nr. nat. nenul, id-ul medicamentului ce trebuie sters.
	*/
	void stergeMedicament(const int& id);

	/*
	* Modifica un medicament din lista.
	* @param: id - nr. nat. nenul, id-ul medicamentului ce trebuie modificat
	*  @param: id - nr. nat. nenul, id-ul medicamentului ce trebuie modificat
	*		: denumire - string, denumirea cu care se modifica
	*		: pret - nr. nat. nenul, pretul cu care se modifica
	*		: producator - string, producatorul modificat
	*		: substantaActiva - string, substanta activa ce se modifica
	*/
	void modificaMedicament(const int& id, const string& denumire, const int& pret, const string& producator, const string& substantaActiva);

	/*
	* Operatia de undo.
	*/
	void undo();

	/*
	* Filtreaza medicamentele dupa un anumit criteriu.
	* @param: pret - nr. nat. nenul, pretul dupa care se poate face filtrarea
	*		: substantaActiva - substanta dupa care se poate face filtarea
	*		: tip - tipul filtrarii, tip = 1 - filtrare dupa pret
	*								 tip = 2 - filtrare dupa substanta activa
	* @return: lista filtrata .
	*/
	vector<Medicament> filtreazaMedicamente(const int& pret, const string& substantaActiva, const int& tip);

	/*
	* Sorteaza medicamentele dupa denumire.
	* @return: lista sortata
	*/
	vector<Medicament> sorteazaDupaDenumire();

	/*
	* Sorteaza medicamentele dupa producator.
	* @return: lista sortata
	*/
	vector<Medicament> sorteazaDupaProducator();

	/*
	* Sorteaza medicamentele dupa substanta activa + pret.
	* @return: lista sortata
	*/
	vector<Medicament> sorteazaDupaSubstantaActivaSiPret();


	/*
	* Cauta un medicament in lista (dupa id).
	* @param: id - id-ul medicamentului cautat
	* @return: pozitia medicamentului dace se afla in lista
	*		 : -1 daca medicamentul nu se afla in lista.
	*/
	int cautaMedicamentId(const int& id) const noexcept;

	/*
	* Cauta un medicament in lista (dupa denumire).
	* @param: id - id-ul medicamentului cautat
	* @return: pozitia medicamentului dace se afla in lista
	*		 : -1 daca medicamentul nu se afla in lista.
	*/
	int cautaMedicamentDenumire(const string& denumire) const;

	/*
	* Creeaza un raport car determina numarul medicamentelor care au aceeasi substanta activa.
	*/
	map<string,DTOMedicament> raport();

	/*
	* Retunreaza lista medicamentelor.
	*/
	vector<Medicament> getLista() const;

	~ServiceMedicamente() = default;
};

#endif // !SERVICE_H_
