#ifndef E09_H
#define E09_H
#include "etat.h"

class E09 : public Etat
{
public:
	E09();
	virtual void transition(); //goNext()
	virtual ~E09(){}
};

#endif