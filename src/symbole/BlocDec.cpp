#include <sstream>
#include "BlocDec.h"

using namespace std;
BlocDec::BlocDec()
{
	m_idSymbole = BLOCDECLARATION;
	m_currentLine = NULL;
	m_prevDec = NULL;
}

BlocDec::~BlocDec()
{
	delete m_currentLine;
	delete m_prevDec;
}

BlocDec::operator std::string() const
{
	stringstream ss;

	string prev;
	if (m_prevDec != NULL)
	{
		prev = (string)*m_prevDec;
	}
	else{
		prev = "";
	}

	string current;
	if (m_currentLine != NULL)
	{
		current = (string)*m_currentLine;
	}
	else
	{
		current = "";
	}

	ss << prev << current;
	return ss.str();
}

void BlocDec::initialiser(Symbole **liste, int taille)
{
	if(taille==4)
	{
		//On vient de E34 ou E42
		//liste : [D , var ou const , V ou C , ;]
		m_prevDec = (BlocDec*)liste[0];
		m_currentLine = (LigneDeclaration*)liste[2];

		delete liste[1];
		delete liste[3];
	}
}
