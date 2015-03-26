#ifndef BLOCINSTRUCTION_H
#define BLOCINSTRUCTION_H

#include "Symbole.h"

class Automate;
class LigneInstruction : public Symbole
{
	public:
		LigneInstruction();
		virtual ~LigneInstruction();
		virtual void interpreter(Automate *automate) = 0;
		virtual void transformer(Automate *automate){}
	protected:
	private:
};

#endif // BLOCINSTRUCTION_H
