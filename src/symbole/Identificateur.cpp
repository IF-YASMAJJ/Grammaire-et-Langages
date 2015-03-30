#include "Identificateur.h"
#include "../Automate.h"
#include "Nombre.h"

Identificateur::Identificateur(std::string id) : m_id(id)
{
	m_idSymbole = IDENTIFICATEUR;
}

Identificateur::~Identificateur()
{
	//dtor
}

int  Identificateur::calculer(Automate *automate){

	return (automate->chercherSymbole(m_id))->m_valeur;
}

int* Identificateur::evaluer(Automate *automate) {
	//renvoie un pointeur sur la valeur associé à l'identificateur 
	//renvoie null si la valeur n'est pas connue
	SymboleTable* s = automate->chercherSymbole(m_id);
	if (s->m_connnue | s->m_constante)
	{
		return new int(s->m_valeur);
	}
	else
	{
		return NULL;
	}
}

Expression* Identificateur::transformer(Automate *automate) {
	int* tmp = evaluer(automate);
	if (tmp)
	{
		Nombre * ret = new Nombre(*tmp);
		delete tmp;
		return ret;
	}
	
	return NULL;
}