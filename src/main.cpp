#include <iostream>
#include <boost/regex.hpp>
#include <string>
#include "Lexer.h"
#include "Automate.h"
#include "MessagesErreurs.h"

using namespace std;

queue<string> MessagesErreurs::m_FileMessagesStatiques;
queue<string> MessagesErreurs::m_FileMessagesDoubleDeclaration;

int main(int argc, const char * argv[])
{

	string cheminFichier;
	Automate automate;

	if (argc == 1) {
		MessagesErreurs::NoArgument();

		return EXIT_FAILURE;
	}

	if (argc >= 2) {
		cheminFichier = argv[argc-1];

		if (automate.scannerFichier(cheminFichier) == 0) {
			bool execution = false;
			bool statique = false;
			bool affichage = false;
			bool transformation = false;
			for (int i = 1; i < argc-1; i++) {
				string option = argv[i];
				if (option.length() == 2 && option[0] == '-') {
					switch (option[1]) {
						case 'e':
							// executer le programme
							execution = true;
							break;

						case 'a':
							// analyser le programme de maniere statique
							statique = true;
							break;

						case 'p':
							//automate.afficherProgramme();
							affichage = true;
							break;

						case 'o':
							//optimiser les expressions et instructions
							transformation = true;
							break;

						default:
							break;
					}
				} else {
					//TODO : on signale une mauvaise option ?
				}
			}
			automate.lecture(execution, statique, affichage, transformation);
			return EXIT_SUCCESS;
		} else {
			MessagesErreurs::FichierInexistant(cheminFichier);
			return EXIT_FAILURE;
		}
	}

	//Automate *automate = new Automate(cheminFichier);
	string pause;
	cin >> pause;
	return 0;
}

