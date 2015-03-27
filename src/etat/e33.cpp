#include "e33.h"

#include "../Automate.h"
#include "../MessagesErreurs.h"
#include "../symbole/Symbole.h"
#include "e34.h"
#include "e35.h"

E33::E33()
{

}

void E33::transition(Automate* automate)
{
	Symbole *s = automate->getNextLexer();
	switch(*s){
	case POINTVIRGULE:
        automate->decalage(s, new E34());
        break;
	case VIRGULE:
        automate->decalage(s, new E35());
        break;
    default:
		MessagesErreurs::ErreurSyntaxique(0, 0, ATTENDU_VIRGPOINTVIRG);
        break;
	}
}
