#include <sstream>
#include <vector>
//#include <boost\algorithm\string.hpp>
#include <boost/algorithm/string.hpp>
#include "LigneConst.h"
#include "Nombre.h"
#include "../Automate.h"

using namespace std;
LigneConst::LigneConst()
{
	m_idSymbole = LIGNECONST;
	m_prevConst = NULL;
}

LigneConst::~LigneConst()
{
	delete m_prevConst;
}

LigneConst::operator std::string() const
{
	std::stringstream ss;
	ss << "const ";
	//affichage des précédentes constantes déclarées sur la même ligne
	if (m_prevConst != NULL)
	{
		string prevConst = *m_prevConst;
		vector<string> tmp;
		boost::split(tmp, prevConst, boost::is_any_of(" \r\n;"));
		tmp.erase(tmp.begin());
		for (unsigned int i = 0; i < tmp.size(); i++)
		{
			if (tmp[i] != "")
			{
				ss << " " << tmp[i];
			}
		}
		ss << ",";
	}

	//affichage de la constante courante
	ss << m_id << " = " << m_value << ";"<<endl;

	return ss.str();

}

void LigneConst::initialiser(Symbole **liste, int taille)
{
    if(taille==3)
    {
		//On vient de l'état 40
		//liste : [id,=,nb]
		m_id = (string)*liste[0];
		m_value = ((Nombre*)liste[2])->getValeur();
		m_prevConst = NULL;

		for(int i=0 ; i<taille ; i++)
		{
			delete liste[i];
		}
    }
    else if (taille==5)
    {
		//On vient de l'état 19
		//liste : [C,,,id,=,nb]
		m_id = (string)*liste[2];
		m_value = ((Nombre*)liste[4])->getValeur();
		m_prevConst = (LigneConst*)liste[0];

		for(int i=1 ; i<taille ; i++){
			delete liste[i];
		}
    }
}

SymboleTable *LigneConst::construireSymboleTable(){
	return new SymboleTable(m_value,true,false,true,true,true);
}
