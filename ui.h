#ifndef UserInterface_H_
#define UserInterface_H_
#include "service.h"
#include "reteta.h"

class Console {
private:

	ServiceMedicamente& service;

	/*
	Afiseaza un medicament.
	@param: m - Medicament, medicamentul ce trebuie cautat.
	*/
	void printMedicament(const Medicament& m) const;

public:

	//Constructorul clasei.
	Console(ServiceMedicamente& service) noexcept : service{ service } {

	}

	/*
	* Afiseaza lista in ordine invera.
	* @param: l - vector<Medicament>, lista ce trebuie afisata
	*/
	void printListaInvers(const vector<Medicament>& l) const ;

	/*
	* Afiseaza lista curenta.
	* @param: lista ce trebuie filtrata.
	*/
	void printLista(const vector<Medicament>& lista);

	void adaugaLaInceput();

	/*
	* Meniul functionalitatii de adaugare a unui medicament in lista.
	*/
	void adaugaMedicament();

	/*
	* Meniul functionalitatii de stergere a unui medicament din lista.
	*/
	void stergeMedicament();

	/*
	* Meniul functionalitatii de modificare a unui medicament din lista.
	*/
	void modificaMedicament();

	/*
	* Meniul functionalitatii de filtrare.
	*/
	void filtrareMedicamente();

	/*
	* Meniul functionalitatii de cautare a unui medicament.
	*/
	void cautaMedicament();

	/*
	* Meniul functionalitatii de sortare.
	*/
	void sorteaza();

	/*
	* Meniul pentru raport.
	*/
	void raport();

	/*
	* Meniul pentru undo.
	*/
	void undo();

	/*
	* Meniul pricipal al aplicatiei.
	*/
	void start();

	/*
	* Meniul pentru retea.
	*/
	void reteta(Reteta& recipe);
};

#endif // !UserInterface_H_
