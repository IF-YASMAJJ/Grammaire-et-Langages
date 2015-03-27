#include <sstream>
#include <iostream>
#include "Lecture.h"
#include "../Automate.h"

using namespace std;
Lecture::Lecture()
{
	m_idSymbole = LECTURE;
}

Lecture::~Lecture()
{
	//dtor
}

Lecture::operator std::string() const
{
	std::stringstream ss; 
	ss << "lire " << m_id << ";";
	return ss.str();
}

void Lecture::interpreter(Automate *automate)
{
	int tmp; 
	cin >> tmp;
	SymboleTable * s = automate->chercherSymbole(m_id);
	s->m_valeur = tmp;
}