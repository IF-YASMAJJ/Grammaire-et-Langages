#include "e13.h"

#include "../symbole/Symbole.h"
#include "../Automate.h"
#include "e14.h"
#include "e15.h"
#include "../symbole/Expression.h"
#include "e16.h"

E13::E13()
{

}

void E13::transition(Automate* automate)
{
	Symbole *s = automate->getNextLexer();
	switch(*s){
	case MULT:
        automate->decalage(s, new E14());
        break;
	case DIV:
		automate->decalage(s, new E15());
		break;
	default:
		automate->reduction(new Expression(), 3);
	}
}


void E13::transition(Automate* automate, Symbole *s){
	switch(*s){
	case OPERATIONMUL:
		automate->decalage(s, new E16());
		break;
	}
}
