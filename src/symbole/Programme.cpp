#include <sstream>
#include "Programme.h"

using namespace std;
Programme::Programme()
{
	m_idSymbole = PROGRAMME;
	m_blocDec = NULL;
	m_blocInst = NULL;
}

Programme::~Programme()
{
	delete m_blocDec;
	delete m_blocInst;
}

Programme::operator std::string() const
{
	stringstream ss;

	string dec;
	if (m_blocDec != NULL)
	{
		dec = (string)*m_blocDec;
	}
	else
	{
		dec = "";
	}

	string inst;
	if (m_blocInst != NULL)
	{
		inst = (string)*m_blocInst;
	}
	else
	{
		inst = "";
	}

	ss << dec << inst;
	return ss.str();
}

void Programme::initialiser(Symbole **liste, int taille)
{
	//On vient de E3
	//liste : [D,I]
	if(taille==2){
		m_blocDec = (LigneDeclaration*)liste[0];
		m_blocInst = (LigneInstruction*)liste[1];
	}
}

void Programme::interpreter(Automate *automate)
{
	m_blocInst->interpreter(automate);
}

void Programme::transformer(Automate* automate)
{
	m_blocInst->transformer(automate);
}