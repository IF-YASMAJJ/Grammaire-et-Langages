#include "e34.h"

#include "../Automate.h"
#include "../symbole/BlocDec.h"

E34::E34()
{

}

void E34::transition(Automate* automate)
{
	automate->reduction(new BlocDec(), 4);
}
