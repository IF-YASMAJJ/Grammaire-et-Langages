#ifndef BLOCINST_H
#define BLOCINST_H

#include <string>
#include "Symbole.h"
#include "LigneInstruction.h"

class BlocInst : public Symbole
{
	public:
		BlocInst();
		BlocInst(LigneInstruction * instruction);
		virtual ~BlocInst();
		virtual operator std::string() const;
		void initialiser(Symbole **, int taille);
		virtual void interpreter(Automate *automate);
	protected:
	private:
		BlocInst * m_prevInst;
		LigneInstruction* m_currentLine;
};

#endif // BLOCINST_H
