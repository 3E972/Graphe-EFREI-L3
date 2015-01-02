#ifndef GRAPHEORIENTE_H
#define GRAPHEORIENTE_H


#include <vector>
#include <list>

#include "string"

#include "petit-helwani-tp1-Sommet.h"
#include "petit-helwani-tp1-Arc.h"
#include "petit-helwani-tp1-Exeption.h"
#include <ostream>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

/**
 * @brief The GrapheOriente class : STRUCTURE DE DONNEES D'UN GRAPHE ORIENTE EN MEMOIRE
 */
class GrapheOriente{

public:

    GrapheOriente();
    ~GrapheOriente();
     void ajouterSommet(string nomSommet);
     void ajouterArc(string nomSommetInitial,double value, string nomSommetTerminal);
      void modifierLaValeurDUnArcParRapportASontSommetInitiale(string nomSommetInitial,double value);
     Sommet &getSommetByName(string nomSommet);


     vector<vector<string> > genererLaMatriceAdjacente() const ;

     void afficherLaListeDesArcs();
      void supprimerUnSommet(string nomSommet);
     list <Arc> &getListeDesArcs(){return listeDesArcs;}
      list <Sommet> &getListeDesSommets(){return listeDesSommets;}

      GrapheOriente( const GrapheOriente& grapheOrienteACopier);

private:

    void suprimerUnArc(Arc &arc);
     string const toString(const double &number)const{ostringstream s;s << number;return s.str();}
     Arc *trouverArc(const string &nomSommetInitial, const string &nomSommetTerminal)const;
     Sommet *trouverSommet(string nomSommet);

    list<Arc> listeDesArcs;
    list<Sommet>  listeDesSommets;

};

#endif // GRAPHEORIENTE_H
