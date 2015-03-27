#include <iostream>
#include <sstream>
#include "Ecriture.h"


using namespace std;
Ecriture::Ecriture()
{
	m_idSymbole = ECRITURE;
	m_expression = NULL;
}

Ecriture::~Ecriture()
{
	delete m_expression;
}

Ecriture::operator std::string() const
{
	stringstream ss;
	string s;
	if (m_expression != NULL)
	{
		s = (string)*m_expression;
	}
	else
	{
		s = "";
	}
	ss << "ecrire " << s << ";"<<endl;
	return ss.str();

}

void Ecriture::interpreter(Automate *automate)
{
	cout << m_expression->calculer(automate)<<endl;
}

void Ecriture::transformer(Automate* automate)
{
	Expression *tmp = m_expression->transformer(automate);
	if (tmp)
	{
		delete m_expression;
		m_expression = tmp;
	}
}