#ifndef EXPPAR_H
#define EXPPAR_H

#include <string>
#include "Facteur.h"


class ExpPar : public Facteur
{
	public:
		ExpPar();
		virtual ~ExpPar();
		virtual operator std::string() const;
		void initialiser(Symbole **, int taille);
		virtual int calculer(Automate *automate){return m_expression->calculer(automate); }
		virtual int* evaluer(Automate *automate){ return m_expression->evaluer(automate); }
		virtual Expression* transformer(Automate *automate);
		virtual void remplirIdsExpression(vector<string> &ids){m_expression->remplirIdsExpression(ids);}
	protected:
	private:
		Expression* m_expression;
};

#endif // EXPPAR_H
