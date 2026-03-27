#include "teste.h"
#include "domain.h"
#include "exceptii.h"
#include "reteta.h"
#include "repo.h"
#include "service.h"
#include <string>
#include <iostream>
#include <assert.h>
#include "MyVector.h"

using std::string;
using std::cout;

void Teste::toateTestele() {
	testeDomain();
	testeRepo();
	testeService();
	testeReteta();
}

void Teste::testeDomain() {
	//Testare set si get.
	Medicament m1(1, "Paracetamol", 25, "Biofarm", "Paracetamol");
	assert(m1.getId() == 1);
	assert(m1.getDenumire() == "Paracetamol");
	assert(m1.getPret() == 25);
	assert(m1.getProducator() == "Biofarm");
	assert(m1.getSubstantaActiva() == "Paracetamol");

	m1.setDenumire("Zinat");
	m1.setPret(54);
	m1.setProducator("Europharm");
	m1.setSubstantaActiva("Cefuroxima");

	assert(m1.getDenumire() == "Zinat");
	assert(m1.getPret() == 54);
	assert(m1.getProducator() == "Europharm");
	assert(m1.getSubstantaActiva() == "Cefuroxima");

	//Testeaza functia de comparare a denumirii a doua medicamente.
	Medicament m2(2, "Paracetamol", 35, "Biofram", "Paracetamol");
	assert(cmpDenumire(m1, m2) == false);
	assert(cmpDenumire(m2, m1) == true);

	//Testeaza functia de comparare a producatorului a doua medicamente.
	assert(cmpProducator(m1, m2) == false);
	assert(cmpProducator(m2, m1) == true);

	//Testeaza functia de comparare a pretului a doua medicamente.
	assert(cmpPret(m1, m2) == false);
	assert(cmpPret(m2, m1) == true);

	//Testeaza functia de comparare a substantei active a doua medicamente.
	assert(cmpSubstantaActiva(m1, m2) == true);
	assert(cmpSubstantaActiva(m2, m1) == false);

	//Testeaza functia de validare a unui medicament.
	Validator validator;
	validator.valideazaMedicament("Paracetamol", 23, "Biofarm", "Paracetamol");

	try {
		validator.valideazaMedicament("", -1, "", "");
		assert(false);
	}
	catch (const ValidatorExceptii& e) {
		assert(e.getMesage() == "Denumirea nu poate fi vida!\nPretul trebuie sa fie un numar natural nenul!\nProducatorul nu poate fi vid!\nSubstanta activa nu poate fi vida!\n");
	}
}

void Teste::testeRepo() {
	//Testeaza functia de adaugare in lista.
	RepoMedicamente repo;
	const auto& mv1 = repo.getAll();
	assert(mv1.size() == 0);
	
	Medicament m1(1, "Zinat", 57, "Biofarm", "Cefuroxima");
	repo.adauga(m1);
	const auto& mv2 = repo.getAll();
	assert(mv2.size() == 1);
	assert(mv2[0].getId() == 1);
	assert(mv2[0].getDenumire() == "Zinat");
	assert(mv2[0].getPret() == 57);
	assert(mv2[0].getProducator() == "Biofarm");
	assert(mv2[0].getSubstantaActiva() == "Cefuroxima");

	//Testeaza functia de cautare a unui medicament in lista (dupa id).
	int pozitie = repo.cautaId(1);
	assert(pozitie == 0);
	Medicament m2(2, "Paracetamol", 32, "Europharm", "Paracetamol");
	pozitie = repo.cautaId(3);
	assert(pozitie == -1);

	//Testeaza functia de cautare a unui medicament in lista (dupa nume).
	pozitie = repo.cautaDenumire("Zinat");
	assert(pozitie == 0);
	pozitie = repo.cautaDenumire("Nurofen");
	assert(pozitie == -1);
	
	//Testeaza functia de stergere a unui medicament din lista.
	try {
		repo.sterge(9);
		assert(false);
	}
	catch (const RepoExceptii& m){
		assert(m.getMesage() == "Nu s-a gasit medicamentul!\n");
	}
	const auto mv4 = repo.getAll();
	assert(mv4.size() == 1);
	repo.sterge(1);
	const auto mv5 = repo.getAll();
	assert(mv5.size() == 0);

	//Introducem noi date.
	repo.adauga(m1);
	repo.adauga(m2);
	Medicament m3(3, "Augumentin", 43, "Fiterman Pharma", "Amoxicilina");
	repo.adauga(m3);
	assert(repo.getAll().size() == 3);

	//Testeaza functia de modificare a unui medicament.
	try {
		repo.modifica(7, "Tantum verde", 43, "Angelini Pharma", "Clorhidratul de benzidamina");
		assert(false);
	}
	catch (const RepoExceptii& m){
		assert(m.getMesage() == "Nu s-a gasit medicamentul!\n");
	}
	repo.modifica(1, "Tantum verde", 43, "Angelini Pharma", "Clorhidratul de benzidamina");
	const auto& mv3 = repo.getAll();
	const int poz = repo.cautaId(1);
	assert(mv3[poz].getDenumire() == "Tantum verde");
	assert(mv3[poz].getPret() == 43);
	assert(mv3[poz].getProducator() == "Angelini Pharma");
	assert(mv3[poz].getSubstantaActiva() == "Clorhidratul de benzidamina");
	
	RepoFile rep{ "test.txt" };
	rep.adauga(m3);
	rep.modifica(3, "dfsg", 3, "Sdffg", "dsffsdd");
	rep.sterge(3);
	try {
		RepoFile repp{ "asdd.txt" };
		assert(false);
	}
	catch (const RepoExceptii msg) {
		assert(true);
	}

	//Testam RepoNou.
	Medicament mm1{ 12, "Paracetamol", 12, "Biofarm", "Paracetamol" };
	auto rep1 = RepoNou(1);
	rep1.adauga(mm1);
	const auto& ll1 = rep1.getAll();
	assert(ll1.size() == 1);
	assert(ll1[0].getId() == 12);
	assert(ll1[0].getDenumire() == "Paracetamol");
	assert(ll1[0].getPret() == 12);
	assert(ll1[0].getProducator() == "Biofarm");
	assert(ll1[0].getSubstantaActiva() == "Paracetamol");

	rep1.modifica(12, "Parasinus", 13, "Terapia", "Paracetamol");
	const auto& ll2 = rep1.getAll();
	assert(ll2.size() == 1);
	assert(ll2[0].getId() == 12);
	assert(ll2[0].getDenumire() == "Parasinus");
	assert(ll2[0].getPret() == 13);
	assert(ll2[0].getProducator() == "Terapia");
	assert(ll2[0].getSubstantaActiva() == "Paracetamol");

	auto pozz = rep1.cautaId(12);
	assert(pozz == 0);

	auto pozz1 = rep1.cautaId(15);
	assert(pozz1 == -1);

	pozz = rep1.cautaDenumire("Paracetanol");
	assert(pozz == -1);

	pozz = rep1.cautaDenumire("Parasinus");
	assert(pozz == 0);

	rep1.sterge(12);
	const auto& ll3 = rep1.getAll();
	assert(ll3.size() == 0);

	rep1 = RepoNou((int)0.0);
	try {
		rep1.adauga(mm1);
		assert(false);
	}
	catch (RepoExceptii msg) {
		assert(true);
	}

}

void Teste::testeService() {
	//Testeaza functia de adaugare.
	RepoMedicamente repo;
	ServiceMedicamente service(repo);
	const auto& mv1 = service.getLista();
	assert(mv1.size() == 0);

	service.adaugaMedicament("Zinat", 56, "Biofarm", "Cefuroxima");
	const auto& mv2 = service.getLista();
	assert(mv2.size() == 1);
	assert(mv2[0].getId() == 1);
	assert(mv2[0].getDenumire() == "Zinat");
	assert(mv2[0].getPret() == 56);
	assert(mv2[0].getProducator() == "Biofarm");
	assert(mv2[0].getSubstantaActiva() == "Cefuroxima");

	service.adaugaMedicament("Paracetamol", 56, "Biofarm", "Paracetamol");
	const auto& mv3 = service.getLista();
	assert(mv3.size() == 2);
	assert(mv3[1].getId() == 2);
	assert(mv3[1].getDenumire() == "Paracetamol");
	assert(mv3[1].getPret() == 56);
	assert(mv3[1].getProducator() == "Biofarm");
	assert(mv3[1].getSubstantaActiva() == "Paracetamol");

	try {
		service.adaugaMedicament("", -2, "", "");
		assert(false);
	}
	catch (const ValidatorExceptii& e) {
		assert(e.getMesage() == "Denumirea nu poate fi vida!\nPretul trebuie sa fie un numar natural nenul!\nProducatorul nu poate fi vid!\nSubstanta activa nu poate fi vida!\n");
	}

	try {
		service.adaugaMedicament("Zinat", 56, "Biofarm", "Cefuroxima");
		assert(false);
	}
	catch (const RepoExceptii& e) {
		assert(e.getMesage() == "Medicament deja existent!\n");
	}

	//Testeaza functia de cautare a unui medicament (dupa id).
	int pozitie = service.cautaMedicamentId(1);
	assert(pozitie == 0);
	pozitie = service.cautaMedicamentId(4);
	assert(pozitie == -1);

	//Testeaza functia de cautare a unui medicament (dupa denumire).
	pozitie = service.cautaMedicamentDenumire("Paracetamol");
	assert(pozitie == 1);
	pozitie = service.cautaMedicamentDenumire("Nurofen");
	assert(pozitie == -1);

	//Testeaza functia de stergere a unui medicament.
	try {
		service.stergeMedicament(5);
		assert(false);
	}
	catch (const RepoExceptii& m) {
		assert(m.getMesage() == "Nu s-a gasit medicamentul!\n");
	}
	const auto& mv4 = service.getLista();
	assert(mv4.size() == 2);
	service.stergeMedicament(2);
	const auto& mv5 = service.getLista();
	assert(mv5.size() == 1);

	//Testeaza functia de modificare a unui medicament.
	try {
		service.modificaMedicament(6, "Tantum verde", 43, "Angelini Pharma", "Clorhidratul de benzidamina");
		assert(false);
	}
	catch (const RepoExceptii& m) {
		assert(m.getMesage() == "Nu s-a gasit medicamentul!\n");
	}
	try {
		service.modificaMedicament(1, "", -3, "", "");
		assert(false);
	}
	catch (const ValidatorExceptii& m) {
		assert(m.getMesage() == "Denumirea nu poate fi vida!\nPretul trebuie sa fie un numar natural nenul!\nProducatorul nu poate fi vid!\nSubstanta activa nu poate fi vida!\n");
	}
	service.modificaMedicament(1, "Tantum verde", 43, "Angelini Pharma", "Clorhidratul de benzidamina");
	const int poz = service.cautaMedicamentId(1);
	const auto& mv6 = service.getLista();
	assert(mv6[poz].getDenumire() == "Tantum verde");
	assert(mv6[poz].getPret() == 43);
	assert(mv6[poz].getProducator() == "Angelini Pharma");
	assert(mv6[poz].getSubstantaActiva() == "Clorhidratul de benzidamina");

	//Testeaza functia de filtrare.
	service.adaugaMedicament("Cefrox", 43, "Fiterman Pharma", "Cefuroxima");
	vector<Medicament> lf;
	const auto& lf1 = service.filtreazaMedicamente(43, "", 1);
	assert(lf1.size() == 2);
	assert(lf1[0].getId() == 1);
	assert(lf1[1].getId() == 2);
	const auto& lf2 = service.filtreazaMedicamente(3, "", 1);
	assert(lf2.size() == 0);
	const auto lf3 = service.filtreazaMedicamente(0, "Cefuroxima", 2);
	assert(lf3.size() == 1);
	assert(lf3[0].getId() == 2);
	const auto& lf4 = service.filtreazaMedicamente(0, "Amoxicilina", 2);
	assert(lf4.size() == 0);

	//Testeaza functia de soratre dupa denumire.
	const auto& ls1 = service.sorteazaDupaDenumire();
	assert(ls1.size() == 2);
	assert(ls1[0].getId() == 2);
	assert(ls1[1].getId() == 1);

	//Testeaza functia de sortare dupa producator.
	const auto& ls2 = service.sorteazaDupaProducator();
	assert(ls2.size() == 2);
	assert(ls2[0].getId() == 1);
	assert(ls2[1].getId() == 2);

	//Testeaza functia de sortare dupa substanta activa + pret.
	service.adaugaMedicament("Zinat", 12, "Fiterman Pharma", "Cefuroxima");
	const auto& ls3 = service.sorteazaDupaSubstantaActivaSiPret();
	assert(ls3.size() == 3);
	assert(ls3[0].getId() == 3);
	assert(ls3[1].getId() == 2);
	assert(ls3[2].getId() == 1);

	service.stergeMedicament(1);
	service.stergeMedicament(2);
	service.stergeMedicament(3);
	const auto& mv7 = service.getLista();
	assert(mv7.size() == 0);

	//Testeaza functia de raport.
	service.adaugaMedicament("Zinat", 23, "Europharm", "Cefuroxima");
	service.adaugaMedicament("Paracetamol", 12, "Biofarm", "Paracetamol");
	service.adaugaMedicament("Augumentin", 45, "Europharm", "Amoxicilina");
	service.adaugaMedicament("Cefrox", 54, "Fiterman Phrama", "Cefuroxima");
	service.adaugaMedicament("Parasiuns", 21, "Terapia", "Paracetamol");
	map <string, DTOMedicament> rp;
	rp = service.raport();
	assert(rp.size() == 3);
	assert(rp["Cefuroxima"].getCount() == 2);
	assert(rp["Paracetamol"].getCount() == 2);
	assert(rp["Amoxicilina"].getCount() == 1);
	assert(rp["Cefuroxima"].getType() == "Cefuroxima");

	//Testeaza undo.
	service.undo();
	const auto& l1  = service.getLista();
	assert(l1.size() == 4);
	service.undo();
	const auto& l2 = service.getLista();
	assert(l2.size() == 3);
	service.stergeMedicament(2);
	const auto& l3 = service.getLista();
	assert(l3.size() == 2);
	service.undo();
	const auto& l4 = service.getLista();
	assert(l4.size() == 3);
	service.modificaMedicament(2, "Parasinus", 12, "Biofarm", "Paracetamol");
	const auto& l5 = service.getLista();
	const Medicament& m1 = l5[service.cautaMedicamentId(2)];
	assert(m1.getDenumire() == "Parasinus");
	assert(m1.getPret() == 12);
	assert(m1.getProducator() == "Biofarm");
	assert(m1.getSubstantaActiva() == "Paracetamol");
	service.undo();
	const auto& l6 = service.getLista();
	const Medicament& m2 = l6[service.cautaMedicamentId(2)];
	assert(m2.getDenumire() == "Paracetamol");
	assert(m2.getPret() == 12);
	assert(m2.getProducator() == "Biofarm");
	assert(m2.getSubstantaActiva() == "Paracetamol");
	try {
		service.undo();
		service.undo();
		service.undo();
		service.undo();
		service.undo();
		service.undo();
		service.undo();
		service.undo();
		service.undo();
		service.undo();
		service.undo();
		service.undo();
		service.undo();
		assert(false);
	}
	catch (const RepoExceptii& msg) {
		assert(msg.getMesage() == "Nu mai sunt operatii disponibile!\n");
	}

}

void Teste::testeReteta() {
	Reteta recipe;
	auto r = recipe.getReteta();
	assert(r.size() == 0);

	Medicament m1(1, "Zinat", 43, "Fiterman Pharma", "Cefuroxima");
	Medicament m2(2, "Parasiuns", 21, "Biofarm", "Paracetamol");
	recipe.adaugaMedicamentInReteta(m1);
	r = recipe.getReteta();
	assert(r.size() == 1);
	recipe.adaugaMedicamentInReteta(m2);
	r = recipe.getReteta();
	assert(r.size() == 2);

	//Golire reteta.
	recipe.golesteReteta();
	r = recipe.getReteta();
	assert(r.size() == 0);

	//Adaugare random.
	RepoMedicamente repo;
	try {
		recipe.adaugaRandom(repo.getAll(), 2);
		r = recipe.getReteta();
		assert(r.size() == 0);
	}
	catch (const RetetaExceptii& m) {
		assert(m.getMesage() == "Medicamente insuficiente!\n");
	}
	Medicament m3(3, "Parasiuns", 45, "Europharm", "Paracetamol");
	Medicament m4(4, "Tantum Verde", 63, "Biofarm", "Clorhidratul de benzidamina");
	Medicament m5(5, "Decasept", 12, "Fitermam Farma", "Vitamina B1");
	repo.adauga(m1);
	repo.adauga(m2);
	repo.adauga(m3);
	repo.adauga(m4);
	repo.adauga(m5);
	recipe.adaugaRandom(repo.getAll(), 3);
	assert(recipe.getReteta().size() == 3);
	recipe.exportHTML("test");
	recipe.exportHTML("test2.html");
	recipe.exportHTML("t.3");

}