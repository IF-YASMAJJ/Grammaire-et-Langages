#include "e37.h"

#include "../Automate.h"
#include "../symbole/Symbole.h"
#include "e38.h"
#include "e41.h"

E37::E37()
{

}

void E37::transition(Automate* automate)
{
	Symbole *s = automate->getNextLexer();
	switch(*s){
	case IDENTIFICATEUR:
        automate->decalage(s, new E38());
        break;
	}
}


void E37::transition(Automate* automate, Symbole *s)
{
	switch(*s){
	case LIGNECONST:
        automate->decalage(s, new E41());
        break;
	}
}
