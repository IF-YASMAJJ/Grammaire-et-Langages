#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <sstream>
#include <boost/regex.hpp>


using namespace std;

class Symbole;

class Lexer
{
	public:
		Lexer();
		virtual ~Lexer();
		Symbole *getNext();  // ???
		Symbole *getCurrent();
		int scannerFichier(string cheminFichier);
	private:
		stringstream m_ss;
		boost::regex m_motCle;
		boost::regex m_symbole;
		boost::regex m_nb;
		boost::regex m_id;

		unsigned int m_colonne;
		unsigned int m_ligne;
};

#endif // LEXER_H
