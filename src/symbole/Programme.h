#ifndef PROGRAMME_H
#define PROGRAMME_H

#include <string>
#include "Symbole.h"
#include "LigneInstruction.h"
#include "LigneDeclaration.h"

class Programme : public Symbole
{
	public:
		Programme();
		virtual ~Programme();
		virtual operator std::string() const;
		void initialiser(Symbole **, int taille);
		void interpreter(Automate *automate);
		void transformer(Automate *automate);
	protected:
	private:
		LigneDeclaration * m_blocDec;
		LigneInstruction * m_blocInst;

};

#endif // PROGRAMME_H
