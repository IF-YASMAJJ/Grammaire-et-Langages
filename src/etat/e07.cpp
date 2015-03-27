#include "e07.h"

#include "../symbole/Symbole.h"
#include "../MessagesErreurs.h"
#include "../Automate.h"
#include "e21.h"
#include "e22.h"
#include "e24.h"
#include "e08.h"
#include "e23.h"
#include "e20.h"

E07::E07()
{

}

void E07::transition(Automate* automate)
{
	Symbole *s = automate->getNextLexer();
	switch(*s){
    case IDENTIFICATEUR:
        automate->decalage(s, new E21());
        break;
	case NOMBRE:
        automate->decalage(s, new E22());
        break;
	case PAROUVRANTE:
        automate->decalage(s, new E24());
        break;
	case ERREURLEXICALE:
		automate->arreter();
		break;
	default:
		MessagesErreurs::Erreur("un identificateur, un numérique ou un symbole "
						"'(' est attendu");
        break;
	}
}

void E07::transition(Automate* automate, Symbole *s){
	switch(*s){
	case EXPRESSION:
		automate->decalage(s, new E08());
		break;
	case TERME:
		automate->decalage(s, new E23());
		break;
	case FACTEUR:
		automate->decalage(s, new E20());
		break;
	}
}
