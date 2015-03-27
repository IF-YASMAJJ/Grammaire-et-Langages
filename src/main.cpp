#include <iostream>
#include <boost/regex.hpp>
#include <string>
#include "Lexer.h"
#include "Automate.h"
#include "MessagesErreurs.h"

using namespace std;

queue<string> MessagesErreurs::m_FileMessages;

int main(int argc, const char * argv[])
{


	//-----------------------------------------------------------------------------
	string cheminFichier;
	Automate automate;

	if (argc == 1) {
		MessagesErreurs::NoArgument();

		return EXIT_FAILURE;
	}

	if (argc >= 2) {
		cheminFichier = argv[argc-1];

		if (automate.scannerFichier(cheminFichier) == 0) {
			automate.lecture();
			for (int i = 1; i < argc-1; i++) {
				string option = argv[i];
				if (option.length() == 2 && option[0] == '-') {
					switch (option[1]) {
						case 'p':
							automate.afficherProgramme();
							break;

						case 'a':
							// analyser le programme de maniere statique
							break;

						case 'e':
							automate.interpreter();
							break;

						case 'o':
							automate.transformer();
							break;

						default:
							break;
					}
				}
			}

			return EXIT_SUCCESS;
		} else {
			// afficher sur sortie d'erruer
			return EXIT_FAILURE;
		}
	}

	//Automate *automate = new Automate(cheminFichier);
	string pause;
	cin >> pause;
	return 0;
}

// void analyserLigneCommande(int argc, const char * argv[])
// {
// 	string cheminFichier;
// 	Lexer lexer;
// 	if (argc == 0) {
// 		fprintf(stderr, "Erreur, veuillez specifier des arguments\n
// 			\tUtilisation :\n
// 			\t\t../lut [-p] [-a] [-e] [-o] source.lt\n
//       \t\t\t[-p] affiche le code source reconnu\n
//       \t\t\t[-a] analyse le programme de maniere statique\n
//       \t\t\t[-e] execute interactivement le programme\n
//       \t\t\t[-o] optimise les expressions et instructions");
// 	} else if (argc == 1) {
// 		cheminFichier = argv[0];
// 		lexer.scannerFichier(cheminFichier)
// 	}
// }
