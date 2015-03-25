#ifndef NOMBRE_H
#define NOMBRE_H

#include "Facteur.h"


class Nombre : public Facteur
{
	public:
		Nombre(int nb);
		virtual ~Nombre();
		virtual bool estTerminal(){return m_idSymbole==NOMBRE;}
		virtual operator std::string() const{ return std::to_string(m_valeur); }
		int getValeur(){return m_valeur;}
		virtual int calculer(Automate *automate){return m_valeur;}
		virtual int* evaluer(Automate *automate){ return new int(m_valeur); }
		virtual void remplirIdsExpression(vector<string> &ids){}
	protected:
	private:
		int m_valeur;
};

#endif // NOMBRE_H
