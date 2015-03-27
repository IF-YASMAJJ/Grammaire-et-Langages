#ifndef AUTOMATE_H
#define AUTOMATE_H

#include <string>
#include <stack>
#include <map>

#include "Lexer.h"
#include "symbole/Expression.h"

using namespace std;

class Symbole;
class Etat;

struct SymboleTable {
    int m_valeur;
    bool m_declaree;
    bool m_use;
    bool m_affectee;
    bool m_constante;
    bool m_connnue;
    SymboleTable(int valeur, bool declaree, bool use, bool affectee, bool constante, bool connue) : m_valeur(valeur), m_declaree(declaree), m_use(use), m_affectee(affectee), m_constante(constante), m_connnue(connue){}
};

typedef map<string,SymboleTable*> ArbreSymboles;

class Automate
{
    public:
		Automate();
        virtual ~Automate();

        void lecture(bool execution, bool statique, bool affichage, bool transformation);
        void decalage(Symbole *s, Etat *e);
        Symbole *getNextLexer();
		void reduction(Symbole *s, int nbSymboles);
		void reduction();
		void erreur();//Empile l'état d'acceptation pour sortir de la boucle de compile
		SymboleTable *chercherSymbole(string key);
		int scannerFichier(string cheminFichier);

		void afficherProgramme();
		//void analyseStatic();
		void interpreter();
		void transformer();
		void arreter(){m_arret = true;}

    protected:
        stack <Symbole*> m_pileSymbole;
        stack <Etat*> m_pileEtats;
        ArbreSymboles m_aSymboles;
		Lexer m_lexer;
		Symbole *m_symbole;
		bool m_statique;
		bool m_affichage;
		bool m_transformation;
		bool m_execution;
		bool m_etatAnalyse;
		bool m_arret;
    private:
		void majTableSymboles(Symbole *s);
		/**
		 * Vérifie les indicateurs pour une expression en vue d'une utilisation de celle-ci.
		 **/
		bool verifierIdentificateurs(vector<string> identificateurs, vector<SymboleTable*> &listeSymboles);
		SymboleTable *creerDeclaration();
		void majFlagsPartieDroite(vector<SymboleTable*> &listeSymboles);
		/**
		 * Parcourt la table des symboles à la recherche de :
		 *		-variables non déclarées
		 *		-variables non affectées (ni utilisées)
		 */
		void verifierTable();
};

#endif // AUTOMATE_H
