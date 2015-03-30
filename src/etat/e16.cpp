#include "e16.h"

#include "../symbole/Symbole.h"
#include "../MessagesErreurs.h"
#include "../Automate.h"
#include "e24.h"
#include "e21.h"
#include "e22.h"
#include "e17.h"


E16::E16()
{

}

void E16::transition(Automate* automate)
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

void E16::transition(Automate* automate, Symbole *s){
	switch(*s){
	case FACTEUR:
        automate->decalage(s, new E17());
        break;
	}
}
