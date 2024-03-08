#include "domain.h"

string Film::getTitlu() const
{
	return titlu;
}

string Film::getGen() const
{
	return gen;
}

int Film::getAn() const
{
	return an;
}

string Film::getActor() const
{
	return actor;
}

void Film::setTitlu(string titlu)
{
	this->titlu = titlu;
}

void Film::setGen(string gen)
{
	this->gen = gen;
}

void Film::setAn(int an)
{
	this->an = an;
}

void Film::setActor(string actor)
{
	this->actor = actor;
}

void Film::validateFilm() const
{
	if (this->titlu.length() < 2)
		throw DomainException("\nDate invalide!\n");
	if (this->gen.length() < 2)
		throw DomainException("\nDate invalide!\n");
	if (this->an < 1850 or this->an > 2023)
		throw DomainException("\nDate invalide!\n");
	if (this->actor.length() < 2)
		throw DomainException("\nDate invalide!\n");
}