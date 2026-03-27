#ifndef UNDO_H_
#define UNDO_H_

#include "domain.h"
#include "repo.h"

class ActiuneUndo {
public:
	virtual void doUndo() = 0;
	virtual ~ActiuneUndo() = default;
};

class UndoAdauga : public ActiuneUndo {
private:
	Medicament medicamentAdaugat;
	RepoAbstract& rep;
public:
	UndoAdauga(RepoAbstract& rep, const Medicament& m) : rep{ rep }, medicamentAdaugat{ m } {

	}

	void doUndo() override {
		rep.sterge(medicamentAdaugat.getId());
	}
};

class UndoSterge : public ActiuneUndo {
private:
	Medicament medicamentSters;
	RepoAbstract& rep;
public:
	UndoSterge(RepoAbstract& rep, const Medicament& m) : rep{ rep }, medicamentSters{ m } {

	}

	void doUndo() override {
		rep.adauga(medicamentSters);
	}
};

class UndoModifica : public ActiuneUndo {
private:
	Medicament medicamentModificat;
	RepoAbstract& rep;
public:
	UndoModifica(RepoAbstract& rep, const Medicament& m) : rep{ rep }, medicamentModificat{ m } {

	}

	void doUndo() override{
		rep.modifica(medicamentModificat.getId(), medicamentModificat.getDenumire(), medicamentModificat.getPret(), medicamentModificat.getProducator(), medicamentModificat.getSubstantaActiva());
	}
};

#endif // !UNDO_H_
