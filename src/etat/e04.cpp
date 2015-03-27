#include "e04.h"

#include "../symbole/Symbole.h"
#include "../Automate.h"
#include "../MessagesErreurs.h"
#include "e05.h"


E04::E04()
{

}

void E04::transition(Automate* automate)
{
	Symbole *s = automate->getNextLexer();
	switch(*s){
    case IDENTIFICATEUR:
        automate->decalage(s, new E05());
        break;
	case ERREURLEXICALE:
		automate->arreter();
		break;
	default:
		MessagesErreurs::IdentificateurNonDeclare();
        break;
	}

}
