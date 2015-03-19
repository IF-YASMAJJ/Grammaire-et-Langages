#ifndef OPERATIONAD_H
#define OPERATIONAD_H

#include <string>
#include "Expression.h"
#include "Terme.h"


class OperationAd : public Expression
{
	public:
		OperationAd();
		virtual ~OperationAd();
		virtual operator std::string() const;
		void initialiser(Symbole **liste, int taille);
	protected:
	private:
		Expression * m_expression;
		std::string m_opA;
		Terme * m_terme;

};

#endif // OPERATIONAD_H
