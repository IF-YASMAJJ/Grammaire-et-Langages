#ifndef E39_H
#define E39_H
#include "etat.h"

class E39 : public Etat
{
public:
	E39();
	virtual void transition(Automate* automate, Symbole *s); //goNext()
	virtual ~E39(){}
};

#endif
