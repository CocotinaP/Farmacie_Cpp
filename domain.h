#ifndef UI_H_
#define UI_H_
#include <string>
#include <iostream>
using std::string;

class DTOMedicament {
private:
	string type;
	int count;
public:

	DTOMedicament(string type1, int count1) : type{ type1 }, count{ count1 }  {

	}

	DTOMedicament(string type1) : type{ type1 }, count{ 0 } {

	}

	DTOMedicament() : type{ "" }, count{ 0 } {

	}

	string getType() const {
		return type;
	}
	int getCount() const noexcept{
		return count;
	}

};

class Medicament {
private:

	int id;
	string denumire;
	int pret;
	string producator;
	string substantaActiva;

public:

	//Constructorul clasei.
	Medicament(int id, string denumire, int pret, string producator, string substantaActiva) : id{ id }, denumire { denumire }, pret{ pret }, producator{ producator }, substantaActiva{ substantaActiva } {

	}

	Medicament() : id{ 0 }, denumire{ "" }, pret{ 0 }, producator{ "" }, substantaActiva{ "" } {

	}

	//Constructorul de copiere.
	Medicament(const Medicament& ot) : id{ ot.getId() }, denumire{ ot.getDenumire() }, pret{ ot.getPret() }, producator{ ot.getProducator() }, substantaActiva{ ot.getSubstantaActiva() } {
		//std::cout << "Hi\n";
	}

	//Retunreaza id-ul unui medicament.
	int getId() const noexcept;

	//Returneaza denumirea unui medicament.
	string getDenumire() const;

	//Returneaza pretul unui medicament.
	int getPret() const noexcept;

	//Returneaza producatorul unui medicament.
	string getProducator() const;

	//Returneaza substanta activa a unui medicament.
	string getSubstantaActiva() const;

	/*
	* Seteaza denumirea unui medicament.
	* @param: denumire - string, noua denumire
	*/
	void setDenumire(string denumireNoua);

	/*
	* Seteaza pretul unui medicament.
	* @param: pretNou - nr. nat. nenul, noul pret
	*/
	void setPret(int pretNou) noexcept;

	/*
	*Seteaza producatorul unui medicament.
	* @param: producatorNou - string, noul producator.
	*/
	void setProducator(string producatorNou);

	/*
	* Seteaza substanta activa a unui medicament.
	* @param: substanaActivaNoua - string, noua substanta activa
	*/
	void setSubstantaActiva(string substantaActivaNoua);

};

//Clasa de validare.
class Validator {
public:

	/*
	* Valideaza datele unui medicament.
	* @param: denumire - string, denumirea medicamentului
	*		: pret - nr. nat. nenul, pretul medicamentului
	*		: producator - string, producatorul medicamentului
	*		: substantaActiva - string, substanta activa a unui medicament
	* @return: arunca exceptii daca medicamentul nu este valid
	*/
	void valideazaMedicament(const string& denumire, const int& pret, const string& producator, const string& substantaActiva) const;
};

/*
	* Compara denumirea a doua medicamente.
	* @param: medicament1, medicament2 - Medicament, medicamentele ce trebuie comparate
	* @return: true - medicament1.denumire < medicament2.denumire
	*		 : false - medicament1.denumire >= medicament2.denumire
	*/
bool cmpDenumire(const Medicament& medicament1, const Medicament& medicament2);

/*
	* Compara producatorul a doua medicamente.
	* @param: medicament1, medicament2 - Medicament, medicamentele ce trebuie comparate
	* @return: true - medicament1.producator < medicament2.producator
	*		 : false - medicament1.producator >= medicament2.producator
	*/
bool cmpProducator(const Medicament& medicament1, const Medicament& medicament2);

/*
	* Compara pretul a doua medicamente.
	* @param: medicament1, medicament2 - Medicament, medicamentele ce trebuie comparate
	* @return: true - medicament1.pret < medicament2.pret
	*		 : false - medicament1.pret >= medicament2.pret
*/
bool cmpPret(const Medicament& medicament1, const Medicament& medicament2) noexcept;

/*
	* Compara substanta activa a doua medicamente.
	* @param: medicament1, medicament2 - Medicament, medicamentele ce trebuie comparate
	* @return: true - medicament1.substantaActiva < medicament2.substantaActiva
	*		 : false - medicament1.substantaActiva >= medicament2.substantaActiva
*/
bool cmpSubstantaActiva(const Medicament& medicament1, const Medicament& medicament2);

#endif // !UI_H_
