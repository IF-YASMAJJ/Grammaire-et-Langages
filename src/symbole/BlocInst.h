#ifndef BLOCINST_H
#define BLOCINST_H

#include <string>
#include "Symbole.h"
#include "LigneInstruction.h"

#include <iostream>
using namespace std;
class BlocInst : public Symbole
{
	public:
		BlocInst();
		BlocInst(LigneInstruction * instruction);
		virtual ~BlocInst();
		virtual operator std::string() const;
		void initialiser(Symbole **, int taille);
		virtual void interpreter(Automate *automate);
		LigneInstruction *demanderLigneInstruction() const {return m_currentLine;}
	protected:
	private:
		BlocInst * m_prevInst;
		LigneInstruction* m_currentLine;
};

#endif // BLOCINST_H
