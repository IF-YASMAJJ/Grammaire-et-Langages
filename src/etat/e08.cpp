#include "e08.h"

#include "../symbole/Symbole.h"
#include "../MessagesErreurs.h"
#include "../Automate.h"
#include "e09.h"
#include "e10.h"
#include "e11.h"
#include "e12.h"

E08::E08()
{

}

void E08::transition(Automate* automate)
{
	Symbole *s = automate->getNextLexer();
	switch(*s){
	case POINTVIRGULE:
        automate->decalage(s, new E09());
        break;
	case PLUS:
		automate->decalage(s, new E10());
		break;
	case MOINS:
		automate->decalage(s, new E11());
		break;
	case ERREURLEXICALE:
		automate->arreter();
		break;
	default:
		MessagesErreurs::Erreur("Opérateur '+'/'-' ou ';' attendu");
		break;
	}
}

void E08::transition(Automate* automate, Symbole *s){
	switch(*s){
	case OPERATEURAD:
		automate->decalage(s, new E12());
		break;
	}
}
