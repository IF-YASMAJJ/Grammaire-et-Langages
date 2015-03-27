#ifndef EXPRESSION_H
#define EXPRESSION_H
#include <vector>
#include <string>
#include "Symbole.h"
//#include "../Automate.h"


using namespace std;

class Automate;
class Expression : public Symbole
{
	public:
		Expression();
		virtual ~Expression();
		virtual void castUp(){ m_idSymbole = EXPRESSION; }
		virtual void remplirIdsExpression(vector<string> &ids)=0;
		virtual int calculer(Automate *automate)=0;
		virtual int* evaluer(Automate *automate)=0;
		virtual Expression * transformer(Automate* automate) = 0;// { return NULL; }
	protected:
	private:
};

#endif // EXPRESSION_H
