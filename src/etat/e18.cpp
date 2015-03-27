#include "e18.h"

#include "../Automate.h"
#include "../MessagesErreurs.h"
#include "../symbole/Symbole.h"
#include "e19.h"

E18::E18()
{

}

void E18::transition(Automate* automate)
{
	Symbole *s = automate->getNextLexer();
	switch(*s){
	case NOMBRE:
        automate->decalage(s, new E19());
        break;
	default:
		MessagesErreurs::ErreurSyntaxique(0, 0, ATTENDU_VALEUR);
        break;
	}
}
