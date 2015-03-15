#include "e27.h"

#include "../Automate.h"
#include "../symbole/Symbole.h"
#include "e28.h"

E27::E27()
{

}

void E27::transition(Automate* automate)
{
	Symbole *s = automate->getNextLexer();
	switch(*s){
	case DEUXPOINTSEGAL:
        automate->decalage(s, new E28());
        break;
	}
}
