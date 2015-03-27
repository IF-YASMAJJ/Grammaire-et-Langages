#ifndef SYMBOLE_H
#define SYMBOLE_H

//Déclaration des id des symboles (utilisé dans Etat::transition)
#define PROGRAMME 1
#define BLOCDECLARATION 2
#define BLOCINSTRUCTION 3
#define LIGNECONST 4
#define LIGNEVAR 5
#define LECTURE 6
#define AFFECTATION 7
#define ECRITURE 8
#define EXPRESSION 9
#define TERME 10
#define OPERATEURAD 11
#define FACTEUR 12
#define OPERATEURMUL 13
#define EXPPAR 14
#define IDENTIFICATEUR 15
#define NOMBRE 16
#define VIRGULE 17
#define EGAL 18
#define PAROUVRANTE 19
#define PARFERMANTE 20
#define MOINS 21
#define PLUS 22
#define DIV 23
#define MULT 24
#define POINTVIRGULE 25
#define DEUXPOINTSEGAL 26
#define CONST 27
#define VAR 28
#define LIRE 29
#define ECRIRE 30
#define ENDOFFILE 31
#define ERREURLEXICALE 32
#include <string>

class Symbole
{
	public:
		Symbole(int id) : m_idSymbole(id) {}
		Symbole();
		virtual ~Symbole();
		operator int() const { return m_idSymbole; }
		virtual bool estTerminal(){ return false; }
		virtual bool modificateurTableSymboles(){return false;}
		virtual operator std::string() const = 0;
		virtual std::string const demanderId(){return "null";}
		virtual void castUp(){}
		virtual void initialiser(Symbole **, int taille){}


	protected:
		int m_idSymbole;
	private:
};




#endif // SYMBOLE_H
