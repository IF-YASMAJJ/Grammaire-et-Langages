#include "e44.h"

#include "../Automate.h"
#include "../MessagesErreurs.h"
#include "../symbole/Symbole.h"
#include "e18.h"

E44::E44()
{

}

void E44::transition(Automate* automate)
{
	Symbole *s = automate->getNextLexer();
	switch(*s){
	case EGAL:
        automate->decalage(s, new E18());
        break;
	case ERREURLEXICALE:
		automate->arreter();
		break;
	default:
		MessagesErreurs::ErreurSyntaxique(ATTENDU_EGAL);
		automate->arreter();
        break;
	}
}
