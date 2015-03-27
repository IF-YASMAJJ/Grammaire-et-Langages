#include "e43.h"

#include "../Automate.h"
#include "../MessagesErreurs.h"
#include "../symbole/Symbole.h"
#include "e44.h"

E43::E43()
{

}

void E43::transition(Automate* automate)
{
	Symbole *s = automate->getNextLexer();
	switch(*s){
	case IDENTIFICATEUR:
        automate->decalage(s, new E44());
        break;
	case ERREURLEXICALE:
		automate->arreter();
		break;
	default:
		MessagesErreurs::IdentificateurNonDeclare();
        break;
	}
}
