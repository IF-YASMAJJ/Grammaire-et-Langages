#ifndef ECRITURE_H
#define ECRITURE_H

#include <string>
#include "LigneInstruction.h"
#include "Expression.h"

#include <vector>
using namespace std;

class Ecriture : public LigneInstruction
{
	public:
		Ecriture();
		virtual ~Ecriture();
		virtual operator std::string() const;
		void determinerExpr(Expression *exp){m_expression=exp;}
		void remplirIdsExpression(vector<string> &ids){m_expression->remplirIdsExpression(ids);}
		virtual void interpreter(Automate *automate);
		string MessageErreur() const {return (string)*m_expression;}
	protected:
	private:
		Expression* m_expression;
};

#endif // ECRITURE_H
