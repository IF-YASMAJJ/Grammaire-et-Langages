#include "e24.h"

#include "../Automate.h"
#include "../MessagesErreurs.h"
#include "../symbole/Symbole.h"
#include "e20.h"
#include "e21.h"
#include "e22.h"
#include "e23.h"
#include "e25.h"


E24::E24()
{

}

void E24::transition(Automate* automate)
{
	Symbole *s = automate->getNextLexer();
	switch(*s){
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
		MessagesErreurs::Erreur("un identificateur, un numérique est "
								"attendu");
		automate->arreter();
        break;
	}
}

void E24::transition(Automate* automate, Symbole *s)
{
	switch(*s){
	case EXPRESSION:
        automate->decalage(s, new E25());
        break;
	case TERME:
		automate->decalage(s, new E23());
		break;
	case FACTEUR:
		automate->decalage(s, new E20());
		break;
	}
}
