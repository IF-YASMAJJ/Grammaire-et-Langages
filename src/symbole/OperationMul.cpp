#include <sstream>
#include "OperationMul.h"

using namespace std;

OperationMul::OperationMul()
{
	m_idSymbole = TERME;
	m_facteur = NULL;
	m_terme = NULL;
}

OperationMul::~OperationMul()
{
	delete m_facteur;
	delete m_terme;
}

OperationMul::operator std::string() const
{
	stringstream ss;
	string terme;
	if (m_terme != NULL)
	{
		terme = (string)*m_terme;
	}
	else
	{
		terme = "";
	}
	string facteur;
	if (m_facteur!=NULL)
	{
		facteur = (string)*m_facteur;
	}
	else
	{
		facteur = "";
	}
	ss << terme << m_op << facteur;
	return ss.str();
}

void OperationMul::initialiser(Symbole **liste, int taille)
{
	if(taille==3){
		//On vient de E17
		//liste : [T,OP,F]
		m_terme = (Terme*)liste[0];
		m_op = (string)*(Symbole*)liste[1];
		m_facteur = (Facteur*)liste[2];

		delete liste[1];
	}
}

void OperationMul::remplirIdsExpression(vector<string> &ids){
	m_terme->remplirIdsExpression(ids);
	m_facteur->remplirIdsExpression(ids);
}

int  OperationMul::calculer(Automate *automate){
	if (m_op == "*")
	{
		return m_terme->calculer(automate) * m_facteur->calculer(automate);
	}
	else
	{
		return m_terme->calculer(automate) / m_facteur->calculer(automate);
	}

}

int* OperationMul::evaluer(Automate *automate) {
	int * t = m_terme->evaluer(automate);
	int * f = m_facteur->evaluer(automate);
	if ((t == NULL) | (f == NULL))
	{
		delete t;
		delete f;
		return NULL;
	}
	else
	{
		int * ret = new int();
		if (m_op == "*")
		{
			(*ret) = (*t) * (*f);
		}
		else
		{
			(*ret) = (*t) / (*f);
		}
		delete t;
		delete f;

		return ret;
	}
}
