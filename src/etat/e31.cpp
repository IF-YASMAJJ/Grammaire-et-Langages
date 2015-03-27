#include "e31.h"

#include "../Automate.h"
#include "../MessagesErreurs.h"
#include "../symbole/Symbole.h"
#include "e32.h"
#include "e33.h"

E31::E31()
{

}

void E31::transition(Automate* automate)
{
	Symbole *s = automate->getNextLexer();
	switch(*s){
	case IDENTIFICATEUR:
        automate->decalage(s, new E32());
        break;
	case ERREURLEXICALE:
		automate->arreter();
		break;
	default:
		MessagesErreurs::IdentificateurNonDeclare();
		break;
	}
}

void E31::transition(Automate* automate, Symbole *s)
{
	switch(*s){
	case LIGNEVAR:
        automate->decalage(s, new E33());
        break;
	}
}
