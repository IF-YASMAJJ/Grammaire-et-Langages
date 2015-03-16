#include "e29.h"

#include "../Automate.h"
#include "../symbole/Symbole.h"
#include "e30.h"
#include "e10.h"
#include "e11.h"
#include "e12.h"

E29::E29()
{

}

void E29::transition(Automate* automate)
{
	Symbole *s = automate->getNextLexer();
	switch(*s){
	case POINTVIRGULE:
        automate->decalage(s, new E30());
        break;
	case PLUS:
        automate->decalage(s, new E10());
        break;
	case MOINS:
        automate->decalage(s, new E11());
        break;
	}
}

void E29::transition(Automate* automate, Symbole *s)
{
	switch(*s){
	case OPERATEURAD:
        automate->decalage(s, new E12());
        break;
	}
}
