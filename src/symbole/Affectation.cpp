#include <sstream>
#include "Affectation.h"
#include "../Automate.h"

using namespace std;
Affectation::Affectation() {
	m_idSymbole = AFFECTATION;
	m_expression = NULL;
}

Affectation::~Affectation()
{
	delete m_expression;
}

Affectation::operator std::string() const
{
	stringstream ss;
	string expression;
	if (m_expression != NULL)
	{
		expression = (string)*m_expression;
	}
	else
	{
		expression = "";
	}
	ss << m_id << " := " << expression << ";"<<endl;
	return ss.str();
}

void Affectation::interpreter(Automate *automate)
{
	SymboleTable * s = automate->chercherSymbole(m_id);
	s->m_valeur = m_expression->calculer(automate);
}

void Affectation::transformer(Automate* automate)
{
	//simplifier l'expression
	Expression *tmp =  m_expression->transformer(automate);
	if (tmp)
	{
		delete m_expression;
		m_expression = tmp;
	}

	//met à jour la table des symboles 
	int * val = m_expression->evaluer(automate);
	if (val)
	{
		auto symb = automate->chercherSymbole(m_id);
		symb->m_connnue = true; 
		symb->m_valeur = *val;
	}
}