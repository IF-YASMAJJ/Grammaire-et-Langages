#ifndef AFFECTATION_H
#define AFFECTATION_H


#include <string>
#include "LigneInstruction.h"
#include "Expression.h"

#include <vector>
using namespace std;


class Affectation : public LigneInstruction
{
	public:
		Affectation();
		virtual ~Affectation();
		virtual operator std::string() const;
		void determinerExpr(Expression *expr){m_expression = expr;}
		void determinerId(std::string id){m_id = id;}
		std::string const demanderId(){return m_id;}
		void remplirIdsExpression(vector<string> &ids){m_expression->remplirIdsExpression(ids);}
		virtual void interpreter(Automate *automate);
		string MessageErreur() const {return (string)*m_expression;}
		int calculerExpression(Automate *automate) const {return m_expression->calculer(automate);}
	protected:
	private:
		std::string m_id;
		Expression* m_expression;
};

#endif // AFFECTATION_H
