#include "e38.h"

#include "../Automate.h"
#include "../MessagesErreurs.h"
#include "../symbole/Symbole.h"
#include "e39.h"

E38::E38()
{

}

void E38::transition(Automate* automate)
{
	Symbole *s = automate->getNextLexer();
	switch(*s){
	case EGAL:
        automate->decalage(s, new E39());
        break;
	case ERREURLEXICALE:
		automate->arreter();
		break;
	default:
		MessagesErreurs::ErreurSyntaxique(0, 0, ATTENDU_EGAL);
        break;
	}
}
