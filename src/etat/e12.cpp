#include "e12.h"

#include "../symbole/Symbole.h"
#include "../MessagesErreurs.h"
#include "../Automate.h"
#include "e24.h"
#include "e21.h"
#include "e22.h"
#include "e13.h"
#include "e20.h"

E12::E12()
{

}

void E12::transition(Automate* automate)
{
	Symbole *s = automate->getNextLexer();
	switch(*s){
	case PAROUVRANTE:
        automate->decalage(s, new E24());
        break;
	case IDENTIFICATEUR:
		automate->decalage(s, new E21());
		break;
	case NOMBRE:
		automate->decalage(s, new E22());
		break;
	case ERREURLEXICALE:
		automate->arreter();
		break;
	default:
		MessagesErreurs::Erreur("un identificateur, un numérique ou un symbole "
						"'(' est attendu");
		automate->arreter();
        break;
	}
}

void E12::transition(Automate* automate, Symbole *s){
	switch(*s){
	case TERME:
		automate->decalage(s, new E13());
		break;
	case FACTEUR:
		automate->decalage(s, new E20());
		break;
	}
}
