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
		string m_carLus;
		boost::regex m_motCle;
		boost::regex m_symbole;
		boost::regex m_nb;
		boost::regex m_id;
};

#endif // LEXER_H
