#ifndef LAB6_DOMAIN_H_
#define LAB6_DOMAIN_H_
#include <string>

using std::string;

class DomainException {
	string msg;
public:
	DomainException(string m) : msg{ m } {}
	string getMessage() {
		return msg;
	}
};

class Film
{
private:
	string titlu;
	string gen;
	int an;
	string actor;

public:

	Film() {};


	string getTitlu() const;
	string getGen() const;
	int getAn() const;
	string getActor() const;
	void setTitlu(string titlu);
	void setGen(string gen);
	void setAn(int an);
	void setActor(string actor);
	void validateFilm() const;

	Film(string titlu, string gen, int an, string actor) : titlu{ titlu }, gen{ gen }, an{ an }, actor{ actor } {
	}

	Film(const Film& obj) : titlu{ obj.titlu }, gen{ obj.gen }, an{ obj.an }, actor{ obj.actor }
	{

	}
};

#endif // !LAB6_DOMAIN_H_
