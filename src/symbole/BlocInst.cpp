#include <sstream>
#include "BlocInst.h"
#include "Lecture.h"
#include "Identificateur.h"
#include "Ecriture.h"
#include "Affectation.h"
using namespace std;

BlocInst::BlocInst(LigneInstruction *instruction) : m_currentLine(instruction)
{
	m_idSymbole = BLOCINSTRUCTION;
}

BlocInst::BlocInst()
{
	m_idSymbole = BLOCINSTRUCTION;
}
BlocInst::~BlocInst()
{
	delete m_prevInst;
	delete m_currentLine;
}

BlocInst::operator std::string() const
{

	stringstream ss;
	string prev;
	if (m_prevInst != NULL)
	{
		prev = (string)*m_prevInst;
	}
	else
	{
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
	ss << prev << current << endl;
	return ss.str();
}

void BlocInst::initialiser(Symbole **liste, int taille)
{
	if(taille==4){
		//On peut venir de E6 ou E9
		//liste : 	[I , lire , id , ; ]
		//			[I , ecrire ,E , ; ]
		Symbole *s = liste[1];
		if((int)*s == LIRE)
		{
			Lecture *lect = (Lecture*)m_currentLine;
			string id = (string)*(Identificateur*)liste[2];
			lect->determinerId(id);
			m_prevInst = (BlocInst*)liste[0];

			delete liste[1];
			delete liste[2];
			delete liste[3];
		}
		else if((int)*s == ECRIRE)
		{
			Ecriture *ecr = (Ecriture*)m_currentLine;
			ecr->determinerExpr((Expression*)liste[2]);
			m_prevInst = (BlocInst*)liste[0];

			delete liste[1];
			delete liste[3];
		}
	}
	else if(taille==5){
		//On vient de E30
		//liste : [I,id,:=,E,;]
        Affectation *aff = (Affectation*)m_currentLine;
        aff->determinerExpr((Expression*)liste[3]);
        aff->determinerId((string)*(Identificateur*)liste[1]);
		m_prevInst=(BlocInst*)liste[0];

		delete liste[1];
		delete liste[2];
		delete liste[4];
	}
}
