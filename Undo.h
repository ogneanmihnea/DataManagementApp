#pragma once
#include "domain.h"
#include "repository.h"

class ActiuneUndo {
public:
	virtual void doUndo() = 0;
	virtual ~ActiuneUndo() {};
};


class UndoAdauga: public ActiuneUndo {
private:
	FilmRepo& repo;
	Film FilmAdaugat;
	
public:
	UndoAdauga(FilmRepo& repo, Film FilmAdaugat) :FilmAdaugat{ FilmAdaugat }, repo{ repo } {}
	void doUndo() override {
		repo.del(repo.findobj(FilmAdaugat));
	}
};

class UndoSterge : public ActiuneUndo {
private:
	FilmRepo& repo;
	Film FilmSters;
public:
	UndoSterge(FilmRepo& repo, Film FilmSters) :FilmSters{ FilmSters }, repo{ repo } {}
	void doUndo() override {
		repo.store(FilmSters);
	}
};

class UndoModify :public ActiuneUndo {
private:
	FilmRepo& repo;
	Film FilmMod;
public:
	UndoModify(FilmRepo& repo, Film FilmMod) :FilmMod{ FilmMod }, repo{ repo } {}
	void doUndo() override {
		repo.modify(FilmMod);
	}
};