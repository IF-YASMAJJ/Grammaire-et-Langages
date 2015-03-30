#include "e05.h"

#include "../symbole/Symbole.h"
#include "../Automate.h"
#include "../MessagesErreurs.h"
#include "e06.h"

E05::E05()
{

}

void E05::transition(Automate* automate)
{
	//On ne peut faire un décalage que si on lit un point-virgule, sinon erreur.
	Symbole *s = automate->getNextLexer();
	switch(*s){
    case POINTVIRGULE:
        automate->decalage(s, new E06());
        break;
	case ERREURLEXICALE:
		automate->arreter();
		break;
	default:
        MessagesErreurs::ErreurSyntaxique(ATTENDU_VIRGPOINTVIRG);
		automate->arreter();
        break;
	}
}
