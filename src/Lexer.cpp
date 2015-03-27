#define DEBUG false


#include <boost/regex.hpp>

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include "Lexer.h"
#include "symbole/Symbole.h"

#include "symbole/Var.h"
#include "symbole/Identificateur.h"
#include "symbole/Virgule.h"
#include "symbole/ParFermante.h"
#include "symbole/ParOuvrante.h"
#include "symbole/Plus.h"
#include "symbole/Div.h"
#include "symbole/PointVirgule.h"
#include "symbole/EndOfFile.h"
#include "symbole/Const.h"
#include "symbole/Egal.h"
#include "symbole/Nombre.h"
#include "symbole/Virgule.h"
#include "symbole/DeuxPointsEgal.h"
#include "symbole/Mult.h"
#include "symbole/Moins.h"
#include "symbole/Lire.h"
#include "symbole/Ecrire.h"
#include "symbole/ErreurLexicale.h"
#include "MessagesErreurs.h"


Lexer::Lexer()
{

	m_motCle = boost::regex("var|const|lire|ecrire");
	m_symbole = boost::regex("-|\\+|/|\\*|,|;|\\(|\\)|=|:=");
	m_nb = boost::regex("[0-9]+");
	m_id = boost::regex("[a-zA-Z][a-zA-Z0-9]*");
}

Lexer::~Lexer()
{
	//dtor
}

int Lexer::scannerFichier(string cheminFichier)
{
	//if(DEBUG) std::cout << "Lexer : lecture de " << cheminFichier << std::endl;
	std::ifstream file(cheminFichier.c_str(), std::ifstream::in);

    if ( file )
    {

        m_ss << file.rdbuf();
		//cout << file.rdbuf();
        file.close();

    }else
    {
		if(DEBUG) std::cerr << "Erreur à l'ouverture de " << cheminFichier << std::endl;
		return -1;
	}

    if(DEBUG) std::cout<< " lecture du fichier finie"<<std::endl;
    return 0 ;

}

Symbole * getCurrent()
{
	// TO DO
	return NULL;

}



Symbole * Lexer::getNext(){

	/* boucler sur la lecture de caractere
		*
		* rechercher les expreg correspondant totalement ou partiellement aux caractères lus jusqu'a present
		*
		* on lit les caractères jusqu'a ce que plus aucune expreg ne corresponde.
		* A ce moment la, si l'on avait une expreg correspondait (totalement), on enregistre le m_symbole associé.
		* Sinon il y a une erreur.
		*
		* http://www.boost.org/doc/libs/1_31_0/libs/regex/doc/partial_matches.html
		*
	*/

	if(DEBUG) std::cout  << "Lexer::getNext()"<<std::endl;


	m_carLus = "";
	char carLu;

	bool prevCanBeMotCle=false;
	bool prevCanBeSymbole=false;
	bool prevCanBeId=false;
	bool prevCanBeNb=false;

	bool canBeMotCle=false;
	bool canBeSymbole=false;
	bool canBeId=false;
	bool canBeNb=false;

	bool err_lexicale = false;
	boost::cmatch matchMotCle;
	boost::cmatch matchSymbole;
	boost::cmatch matchId;
	boost::cmatch matchNb;
	Symbole * symb = NULL;

	while (symb == NULL)
	{
		if (!m_ss.get(carLu) && m_carLus=="")
		{
			symb = new EndOfFile();
			break;
		}
		err_lexicale = false;
		canBeMotCle = boost::regex_match((m_carLus+carLu).c_str(), matchMotCle, m_motCle, boost::match_default | boost::match_partial);
		canBeSymbole = boost::regex_match((m_carLus+carLu).c_str(), matchSymbole, m_symbole, boost::match_default | boost::match_partial);
		canBeId = boost::regex_match((m_carLus+carLu).c_str(), matchId, m_id, boost::match_default | boost::match_partial);
		canBeNb = boost::regex_match((m_carLus+carLu).c_str(), matchNb, m_nb, boost::match_default | boost::match_partial);

		if(!canBeMotCle && !canBeSymbole && !canBeId && !canBeNb)
		{
			// pas de correspondance, regarder les match précédent
			if(prevCanBeMotCle)
			{
				if(DEBUG) std::cout<<"mot clé ("<<m_carLus<<")"<<std::endl;
				if(m_carLus == "var")
				{
					symb = new Var();
				}
				if(m_carLus == "const")
				{
					symb = new Const();
				}
				if(m_carLus == "lire")
				{
					symb = new Lire();
				}
				if(m_carLus == "ecrire")
				{
					symb = new Ecrire();
				}
			}else
			{
				if(prevCanBeSymbole)
				{
					if(DEBUG) std::cout<<"Symbole ("<<m_carLus<<")"<<std::endl;
					if(m_carLus == "-")
					{
						symb = new Moins();
					}
					if(m_carLus == "+")
					{
						symb = new Plus();
					}
					if(m_carLus == "/")
					{
						symb = new Div();
					}
					if(m_carLus == "*")
					{
						symb = new Mult();
					}
					if(m_carLus == ",")
					{
						symb = new Virgule();
					}
					if(m_carLus == ";")
					{
						symb = new PointVirgule();
					}
					if(m_carLus == "(")
					{
						symb = new ParOuvrante();
					}
					if(m_carLus == ")")
					{
						symb = new ParFermante();
					}
					if(m_carLus == "=")
					{
						symb = new Egal();
					}
					if(m_carLus == ":=")
					{
						symb = new DeuxPointsEgal();
					}

				}else
				{
						if(prevCanBeId)
						{
							if(DEBUG) std::cout<<"Identifiant ("<<m_carLus<<")"<<std::endl;
							symb = new Identificateur(m_carLus);
						}else
						{
							if(prevCanBeNb)
							{
								if(DEBUG) std::cout<<"Nombre ("<<m_carLus<<")"<<std::endl;
								symb = new Nombre(atoi(m_carLus.c_str()));
							}else
							{
								if(!isspace(carLu))
								{
									err_lexicale = true;
									if(DEBUG) std::cout<<"Erreur lexicale 42 !   ("<<(m_carLus+carLu)<<")"<<std::endl;
								}else
								 {
									if(DEBUG) std::cout<<"SPAAAACE"<<std::endl;
								 }
							}
						}
				}
			}
			if(err_lexicale)
			{
				//erreur lexicale detectée
				//on continue la recherche, on ignore le dernier caractère lu
				if(canBeMotCle)
				{
					prevCanBeMotCle = matchMotCle[0].matched;
				}
				if(canBeSymbole)
				{
					prevCanBeSymbole = matchSymbole[0].matched;
				}
				if(canBeId)
				{
					prevCanBeId = matchId[0].matched;
				}
				if(canBeNb)
				{
					prevCanBeNb = matchNb[0].matched;
				}
				else{
					MessagesErreurs::ErreurLexicale(0,0,&carLu);
					symb = new ErreurLexicale();
				}

			}else
			{
				prevCanBeMotCle=false;
				prevCanBeSymbole=false;
				prevCanBeId=false;
				prevCanBeNb=false;
				if(!isspace(carLu))
				{
					m_carLus = "";
					m_ss.unget();
				}else
				 {
					 m_carLus = "";
				 }
			}
		}else
		{
			if(canBeMotCle)
			{
				prevCanBeMotCle = matchMotCle[0].matched;
			}
			if(canBeSymbole)
			{
				prevCanBeSymbole = matchSymbole[0].matched;
			}
			if(canBeId)
			{
				prevCanBeId = matchId[0].matched;
			}
			if(canBeNb)
			{
				prevCanBeNb = matchNb[0].matched;
			}
			m_carLus += carLu;

		}


	}



	return symb;
}



