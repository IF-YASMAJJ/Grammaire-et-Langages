#include <sstream>
#include "OperationAd.h"
#include "Nombre.h"

using namespace std;
OperationAd::OperationAd()
{
	m_idSymbole = EXPRESSION;
	m_expression = NULL;
	m_terme = NULL;
}

OperationAd::~OperationAd()
{
	delete m_expression;
	delete m_terme;
}

OperationAd::operator std::string() const
{
	stringstream ss;
	string exp;
	if (m_expression != NULL)
	{
		exp = (string)*m_expression;
	}
	else
	{
		exp = "";
	}
	string terme;
	if (m_terme != NULL)
	{
		terme = (string)*m_terme;
	}
	else
	{
		terme = "";
	}
	ss << exp << m_opA << terme;

	return ss.str();
}

void OperationAd::initialiser(Symbole **liste, int taille){
	if (taille == 3)
	{
		//On vient de E13
		//liste : [E,OpA,T]
		m_expression = (Expression*)liste[0];
		m_opA = (string)*liste[1];
		m_terme = (Terme*) liste[2];

		delete liste[1];
	}
}

void OperationAd::remplirIdsExpression(vector<string> &ids){
	m_expression->remplirIdsExpression(ids);
	m_terme->remplirIdsExpression(ids);
}

int  OperationAd::calculer(Automate *automate){
	if (m_opA == "+")
	{
		return m_expression->calculer(automate) + m_terme->calculer(automate);
	}
	else
	{
		return m_expression->calculer(automate) - m_terme->calculer(automate);
	}
}


int* OperationAd::evaluer(Automate *automate) {
	int * e = m_expression->evaluer(automate);
	int * t = m_terme->evaluer(automate);
	if ((e == NULL) | (t == NULL))
	{
		delete e;
		delete t;
		return NULL;
	}
	else
	{
		int * ret = new int();
		if (m_opA == "+")
		{
			(*ret) = (*e) + (*t);
		}
		else
		{
			(*ret) = (*e) - (*t);
		}
		delete e;
		delete t;

		return ret;
	}
}

Expression * OperationAd::transformer(Automate* automate)
{
	//test si l'expression peut �rte ramen� � une constante
	int * tmp = evaluer(automate);
	if (tmp)
	{
		Nombre * ret = new Nombre(*tmp);
		delete tmp;
		return ret;
	}

	//transformation des deux membre
	Terme* t = (Terme*)m_terme->transformer(automate);
	if (t)
	{
		delete m_terme;
		m_terme = t;
	}

	Expression * e = m_expression->transformer(automate);
	if (e)
	{
		delete m_expression;
		m_expression = e;
	}

	//gestion de l'�l�ment neutre;
	tmp = m_expression->evaluer(automate);
	if (tmp)
	{
		if (*tmp == 0 && m_opA == "+")
		{
			Terme * ret = m_terme;
			m_terme = NULL;
			delete tmp;
			return ret;
		}
		delete tmp;
	}

	tmp = m_terme->evaluer(automate);
	if (tmp)
	{
		if (*tmp == 0)
		{
			Expression * ret = m_expression;
			m_expression = NULL;
			delete tmp;
			return ret;
		}
		delete tmp;
	}

	return NULL;

}
