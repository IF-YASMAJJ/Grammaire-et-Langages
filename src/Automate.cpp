
#include "Automate.h"
#include "etat/etat.h"
#include "etat/e00.h"
#include "etat/e01.h"
#include "symbole/LigneDeclaration.h"
#include "symbole/LigneConst.h"
#include "symbole/Affectation.h"
#include "symbole/Ecriture.h"
#include "symbole/BlocInst.h"
#include "MessagesErreurs.h"

#include <vector>
using namespace std;

Automate::Automate()
{
	m_symbole = NULL;
}

int Automate::scannerFichier(string cheminFichier)
{
	return m_lexer.scannerFichier(cheminFichier);
}

Automate::~Automate()
{
}

void Automate::lecture()
{
	m_pileEtats.push(new E00());
	while (!m_pileEtats.top()->isFinal())
	{
		m_pileEtats.top()->transition(this);
	}
	verifierTable();
}

void Automate::decalage(Symbole *s, Etat *e){
	if(s->estTerminal())
		m_symbole = NULL;

    m_pileSymbole.push(s);
    m_pileEtats.push(e);
}

Symbole * Automate::getNextLexer(){
	if(m_symbole == NULL)
		m_symbole = m_lexer.getNext();

	return m_symbole;
}


void Automate::reduction(Symbole* s, int nbSymboles)
{
	Symbole** listSymbole = new Symbole*[nbSymboles];
	for (int i = nbSymboles -1 ; i > -1; i--)
	{
		Etat * tmp;
		listSymbole[i] = m_pileSymbole.top();
		m_pileSymbole.pop();

		tmp = m_pileEtats.top();
		m_pileEtats.pop();
		delete tmp;
	}
	s->initialiser(listSymbole, nbSymboles);
	majTableSymboles(s);
	m_pileEtats.top()->transition(this, s);
}

void Automate::reduction()
{
	//cas où on cast un symbole en son parent
	Symbole *s = m_pileSymbole.top();
	m_pileSymbole.pop();
	s->castUp();

	Etat * tmp = m_pileEtats.top();
	m_pileEtats.pop();
	delete tmp;
	m_pileEtats.top()->transition(this, s);
}

void Automate::erreur()
{
	m_pileEtats.push(new E01());
}

void Automate::afficherProgramme()
{
	string tmp = *m_pileSymbole.top();
	cout << tmp;
}

SymboleTable *Automate::chercherSymbole(string key){
	if(key=="null") return NULL;	//Si key vient de Symbole::demanderId

	ArbreSymboles::iterator it = m_aSymboles.find(key);
	if(it != m_aSymboles.end())	return it->second;

	return NULL;
}

void Automate::majTableSymboles(Symbole *s)
{
	string idTable = s->demanderId();
	SymboleTable *symbole = chercherSymbole(idTable);

	const int typeS = (int)*s;
    if(typeS == LIGNEVAR)
    {
		if(symbole != NULL){
			MessagesErreurs::DoubleDeclaration(idTable);
			return;
		}
		//Ajout de la déclaration dans la table.
		SymboleTable *st = creerDeclaration();
//        m_aSymboles[idTable] = st;
		m_aSymboles.insert(pair<string,SymboleTable*>(idTable,st));
	}
	else if(typeS == LIGNECONST)
	{
		if(symbole != NULL){
			MessagesErreurs::DoubleDeclaration(idTable);
			return;
		}
		//Ajout de la définition de constante la table.
        SymboleTable *st = ((LigneConst*)s)->construireSymboleTable();
        m_aSymboles.insert(pair<string,SymboleTable*>(idTable,st));
	}
	else if(typeS == BLOCINSTRUCTION){
		//
		BlocInst *bInstr = (BlocInst *)s;
		LigneInstruction *lInstr = bInstr->demanderLigneInstruction();
		if(lInstr==NULL)	return;

		idTable = lInstr->demanderId();
		symbole = chercherSymbole(idTable);


		const int typeAff = (int)*lInstr;
		if(typeAff == AFFECTATION)
		{
			/*
			 * TODO :
			 * 	(DONE) au moins une variable partie droite de affectation non affectée (chercher dans la table)
			 *	(DONE) variable partie gauche est une constante
			 * 	(DONE) une des deux variables n'a pas été déclarée
			 */
			 bool calcul = true;
			 if(symbole == NULL){
				MessagesErreurs::ASVariableNonDeclaree(idTable);

				symbole = creerDeclaration();
				symbole->m_declaree = false;
				m_aSymboles.insert(pair<string,SymboleTable*>(idTable,symbole));
				calcul = false;
			 }
			 else if(symbole->m_constante){
				MessagesErreurs::ConstanteNonModifiable(idTable);
				calcul = false;
			 }

			 Affectation *aff = (Affectation*)lInstr;
			 vector<string> identificateurs;
			 vector<SymboleTable*> listeSymboles;

			 aff->remplirIdsExpression(identificateurs);
			 if(!verifierIdentificateurs(identificateurs, listeSymboles)){
				MessagesErreurs::ASValeurInconnue(aff->MessageErreur());
				calcul = false;
			}

			if(!calcul){
			 //Si on arrive ici, alors l'affectation peut avoir lieu.
//			 symbole->m_valeur = aff->calculerExpression();
			}


			if(symbole->m_declaree){
				symbole->m_affectee = true;
				symbole->m_connnue = true;
			}
			majFlagsPartieDroite(listeSymboles);


		}
		else if(typeAff == ECRITURE)
		{
			/*
			 * TODO :
			 * 	la variable à écrire n'a pas été déclarée ou affectée.
			 */
			 Ecriture *ecr = (Ecriture*)lInstr;
			 vector<string> identificateurs;
			 vector<SymboleTable*> listeSymboles;

			 ecr->remplirIdsExpression(identificateurs);
			 if(!verifierIdentificateurs(identificateurs, listeSymboles)){
				MessagesErreurs::ASValeurInconnue(ecr->MessageErreur());
			}

			 majFlagsPartieDroite(listeSymboles);
		}
		else if(typeAff == LECTURE)
		{
			if(symbole == NULL){
				MessagesErreurs::ASVariableNonDeclaree(idTable);
				return;
			}

			symbole->m_affectee = true;
			symbole->m_connnue = false;
		}
		//
	}
}

bool Automate::verifierIdentificateurs(vector<string> identificateurs, vector<SymboleTable*> &listeSymboles){
	bool aRetourner = true;
	for(unsigned i=0; i<identificateurs.size() ; i++){
		ArbreSymboles::iterator it = m_aSymboles.find(identificateurs[i]);

		if(it==m_aSymboles.end()){
			aRetourner =  false;
		}
		else{
			if(!it->second->m_affectee){
				aRetourner = false;
			}
			listeSymboles.push_back(it->second);
		}
	}
	return aRetourner;
}


SymboleTable *Automate::creerDeclaration(){
	return new SymboleTable(0,true,false,false,false,false);
}

void Automate::majFlagsPartieDroite(vector<SymboleTable*> &listeSymboles){
	for(unsigned i=0; i<listeSymboles.size() ; i++){
		listeSymboles[i]->m_use = true;
	}
}

void Automate::verifierTable(){
	ArbreSymboles::iterator it ;
	SymboleTable *sTable;
    for(it = m_aSymboles.begin() ; it!=m_aSymboles.end() ; it++){
		sTable = it->second;

		if(!sTable->m_declaree){
			MessagesErreurs::ASVariableNonDeclaree(it->first);
		}
		else{
			if(!sTable->m_affectee){
				MessagesErreurs::ASVariableNonAffectee(it->first);
			}
			if(!sTable->m_use){
				MessagesErreurs::ASVariableNonUtilisee(it->first);
			}
		}
    }
}

void Automate::interpreter()
{
	//m_pileSymbole.top()->interpreter;
}

