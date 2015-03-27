#ifndef ERREURLEXICALE_H
#define ERREURLEXICALE_H

#include "Symbole.h"


class ErreurLexicale : public Symbole
{
	public:
		ErreurLexicale();
		virtual operator std::string() const {return "";}
		virtual ~ErreurLexicale();
	protected:
	private:
};

#endif // ERREURLEXICALE_H
