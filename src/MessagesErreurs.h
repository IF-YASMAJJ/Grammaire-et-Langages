#ifndef MESSAGESERREURS_H
#define MESSAGESERREURS_H

#include <string>
#include <queue>
#include <iostream>
using namespace std;

#define ATTENDU_VIRGPOINTVIRG 1
#define ATTENDU_EGAL 2
#define ATTENDU_VALEUR 4
#define ATTENDU_OPERATEUR 8

/*
 * Destiné à contenir l'ensemble des messages d'erreurs que peut renvoyer le programme
 */
class MessagesErreurs
{
	public:
		MessagesErreurs() {}
		virtual ~MessagesErreurs() {}

		static void NoArgument (){
			cerr << "Erreur, veuillez specifier des arguments\n"
				 "\tUtilisation :\n"
				"\t\t../lut [-p] [-a] [-e] [-o] source.lt\n"
				"\t\t\t[-p] affiche le code source reconnu\n"
				"\t\t\t[-a] analyse le programme de maniere statique\n"
				"\t\t\t[-e] execute interactivement le programme\n"
				"\t\t\t[-o] optimise les expressions et instructions\n";
		}

		static void Erreur(string description){
			cerr << "Erreur : " << description;
		}

		static void FichierInexistant(string nomFichier){
			cerr << "Erreur a l'ouverture du fichier " << nomFichier << endl;
		}

		static void IdentificateurNonDeclare(){
			m_FileMessagesStatiques.push("Identificateur requis");
		}

		static void DoubleDeclaration(string nomVariable){
			m_FileMessagesDoubleDeclaration.push("la variable " + nomVariable + " est deja declaree");
		}

		static void ConstanteNonModifiable(string nomVariable){
			m_FileMessagesStatiques.push("la variable " + nomVariable + " est une constante.");
		}

		static void ASValeurInconnue(string expression){
			m_FileMessagesStatiques.push("une valeur dans l'expression " + expression + " n'est pas connue.");
		}

		static void ASVariableNonAffectee(string nomVariable){
			m_FileMessagesStatiques.push("variable non affectee : " + nomVariable);
		}

		static void ASVariableNonUtilisee(string nomVariable){
			m_FileMessagesStatiques.push("variable non utilisee : " + nomVariable);
		}

		static void ASVariableNonDeclaree(string nomVariable){
			m_FileMessagesStatiques.push("la variable " + nomVariable + " n'a pas ete declaree.");
		}

		static void ErreurLexicale(int ligne, int colonne, string caractere){
			cerr << "Erreur lexicale (" << std::to_string(ligne) << ":" << std::to_string(colonne) << ") caractere _";
		}

		static void ErreurSyntaxique(int ligne, int colonne, int nature){
			switch(nature){
			case ATTENDU_VIRGPOINTVIRG:
				m_FileMessagesStatiques.push("Erreur syntaxique (" + std::to_string(ligne) + ":" + std::to_string(colonne) + ") symbole , ou ; attendu");
				return;
			case ATTENDU_EGAL:
				m_FileMessagesStatiques.push("Erreur syntaxique (" + std::to_string(ligne) + ":" + std::to_string(colonne) + ") symbole = attendu");
				return;
			case ATTENDU_VALEUR:
				m_FileMessagesStatiques.push("Erreur syntaxique (" + std::to_string(ligne) + ":" + std::to_string(colonne) + ") valeur attendue");
				return;
			case ATTENDU_OPERATEUR:
				m_FileMessagesStatiques.push("Erreur syntaxique (" + std::to_string(ligne) + ":" + std::to_string(colonne) + ") operateur := attendu");
				return;
			}
		}

		static void EcrireMessagesStatiques(){
			while(!m_FileMessagesStatiques.empty()){
				cerr << m_FileMessagesStatiques.front() << endl;
				m_FileMessagesStatiques.pop();
			}
		}

		static void EcrireMessagesDoubleDeclaration(){
			while(!m_FileMessagesDoubleDeclaration.empty()){
				cerr << m_FileMessagesDoubleDeclaration.front() << endl;
				m_FileMessagesDoubleDeclaration.pop();
			}
		}
	protected:
	private:
		/**
		 * Ne contient que les messages concernant des doubles déclarations de variables.
		 */
		static queue<string> m_FileMessagesDoubleDeclaration;
		/**
		 * Ne contient que les messages émanant de l'analyse statique.
		 */
		static queue<string> m_FileMessagesStatiques;
};

#endif // MESSAGESERREURS_H
