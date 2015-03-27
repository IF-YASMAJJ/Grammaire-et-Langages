#include "e39.h"

#include "../Automate.h"
#include "../MessagesErreurs.h"
#include "../symbole/Symbole.h"
#include "e40.h"

E39::E39()
{

}

void E39::transition(Automate* automate)
{
	Symbole *s = automate->getNextLexer();
	switch(*s){
	case NOMBRE:
        automate->decalage(s, new E40());
        break;
	default:
		MessagesErreurs::ErreurSyntaxique(0, 0, ATTENDU_VALEUR);
        break;
	}
}
