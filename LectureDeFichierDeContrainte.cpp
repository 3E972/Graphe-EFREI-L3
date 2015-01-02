#include "LectureDeFichierDeContrainte.h"

LectureDeFichierDeContrainte::LectureDeFichierDeContrainte()
{

}

LectureDeFichierDeContrainte::~LectureDeFichierDeContrainte()
{

}

GrapheOriente LectureDeFichierDeContrainte::readFile(string path){

   /* ifstream graphFile(path.c_str(), ios::binary );

    // TEST SI LE FICHIER DU GRAPH EST CORRECTEMENT OUVERT
    if(!graphFile.is_open()) THROW_EXEPTION( "Erreur imposible d'ouvrir le fichier '" + path+"', verifier si il n'est pas deja utilisee dans un autre programme.");

    string graphText((std::istreambuf_iterator<char>(graphFile)),std::istreambuf_iterator<char>());

    // RETIRE TOUS LES ESPACES, LES RETOURS CHAIRIOT, AINSI QUE LES TABULATIONS
    stripString(graphText);

    // CHERCHE LA POSITION DU MARQUEUR "SOMMETS:[ 1,2 ]"
    //                                  ^^^^^^^^^
    size_t posBeginSommet=graphText.find("SOMMETS:[");
    if(posBeginSommet==-1)THROW_EXEPTION( "Erreur le marqueur 'SOMMETS:[' n'a pas ete trouve dans le fichier : "+path);

    // CHERCHE LA POSITION DU MARQEUR "SOMMETS:[ 1,2 ]", A PARTIR DE LA POSITION DU MARQUEUR "SOMMETS:[ 1,2 ]"
    //                                               ^                                        ^^^^^^^^^
    size_t posEndSommet=graphText.find(']',posBeginSommet);
    if(posEndSommet==-1)THROW_EXEPTION( "Erreur le marqueur ']' de fin de 'SOMMETS:[' n'a pas ete trouve dans le fichier : "+path);

    // EXTRAIT LES SOMMETS  :"[ 1,2 ]"
    //                          ^^^
    string sommetsText(graphText.substr(posBeginSommet+9,posEndSommet-(posBeginSommet+9)));

    // SUPRIME "SOMMETS:[ 1,2 ]ARCS:{[1, 10, 2],[2, 44, 1]} A PARTIR DU MARQUEUR SOMMETS:[ 1,2 ] JUSQU'AU MARQUEUR SOMMETS:[ 1,2 ]
    //          ^^^^^^^^^^^^^^^                                                  ^^^^^^^^^                                       ^
    graphText.erase(posBeginSommet,posEndSommet-posBeginSommet+1);

    GrapheOriente graphe;

    size_t posSplitVirguleSommets = 0;

    // BOUCLE PARCOUR SPLITER LES SOMMET A PARTIR DU MARQUEUR "1,2"
    //                                                          ^
    while (( posSplitVirguleSommets = sommetsText.find(",")) != std::string::npos) {
        graphe.ajouterSommet(sommetsText.substr(0, posSplitVirguleSommets));
        sommetsText.erase(0, posSplitVirguleSommets + 1); // +1 : longeur du delimiteur
    }
    // AJOUTE LE DERNIER SOMMET
     graphe.ajouterSommet(sommetsText.substr(0, posSplitVirguleSommets));

     // CHERCHE LE MARQUEUR "ARCS:["
     size_t posBeginArcs=graphText.find("ARCS_DE_CONTRAINTE:{");
     if(posBeginArcs==-1)THROW_EXEPTION( "Erreur le marqueur 'ARCS_DE_CONTRAINTE:[' n'a pas ete trouve dans le fichier : "+path);

     // CHERCHE LE MARQUEUR "]", LA FIN DU MARQUEUR "ARCS_DE_CONTRAINTE:["
     size_t posEndArcs=graphText.find('}',posBeginArcs);
     if(posEndArcs==-1)THROW_EXEPTION( "Erreur le marqueur ']' de fin de 'ARCS_DE_CONTRAINTE:[' n'a pas ete trouve dans le fichier : "+path);

     // EXTRAIT LES ARCS
     string arcsText(graphText.substr(posBeginArcs+6,posEndArcs-(posBeginArcs+5)));

    // PARCOUR LES ARCS
    size_t posSplitArcs = 0;
    while (( posSplitArcs = arcsText.find("],[")) != std::string::npos) {

        // CHERCHE LE MARQUEUR "["
        size_t posBeginArc=arcsText.find("[");
        if(posBeginArc==-1)THROW_EXEPTION( "Erreur le marqueur '[', debut d'un arc, n'a pas ete trouve dans le fichier : "+path);

        // CHERCHE LE MARQUEUR "]", LA FIN DU MARQUEUR "ARCS_DE_CONTRAINTE:["
        size_t posEndArc=arcsText.find(']',posBeginArc);
        if(posEndArc==-1)THROW_EXEPTION( "Erreur le marqueur ']' de fin d'un n'a pas ete trouve dans le fichier : "+path);

        // EXTRAIT UN ARC
        string arcText(arcsText.substr(posBeginArc+1,posEndArc-(posBeginArc+1)));

        size_t posSplitArc = 0;
        vector<string> vStringArc;
        while (( posSplitArc = arcText.find(",")) != std::string::npos) {
            vStringArc.push_back(arcText.substr(0,posSplitArc));
            arcText.erase(0, posSplitArc + 1); // +1 : longeur du delimiteur pour chaque element d'un arc
        }

        // AJOUTE LE SOMMET TERMINAL D'UN ARC
        vStringArc.push_back(arcText);

        // VERIFIE SI LA DECLARARION DE L'ARC A BIEN 3 ELEMENTS
        if(vStringArc.size()>=2)THROW_EXEPTION( "Erreur l'arc '"+arcsText+"' ne contien pas au moins 2 elements dans sa declarartion.");

        cout<<endl<<"FICHIER DE CONTRAINTRE : La tâche "+StringArc[0]+" a pour durée d’exécution ‘"+vStringArc[1]+"’.";

        if(vStringArc.size()>=3){

            cout<<" Elle ne peut s’exécuter que lorsque la tâche ";
            for(unsigned int i=3;i<vStringArc.size();i++)
                if(i=3) cout<<vStringArc[i];
                else if(i>3 && i<vStringArc.size()-1) cout<<", "+vStringArc[i];
                else cout<<" et "+vStringArc[i];
            cout<<" est terminée.";
        }
        else cout<<" Aucune contrainte.";

        graphe.ajouterArc(vStringArc[0],atof(vStringArc[1].c_str()),vStringArc[2]);

        arcsText.erase(0, posSplitArcs + 2); // +3 : longeur du delimiteur pour chaque arc
    }

    // SUPRIME "]}"
    arcsText.erase(arcsText.end()-2,arcsText.end());
    arcsText.erase(arcsText.begin(),arcsText.begin()+1);
    // AJOUTE LE DERNIER ARC
    size_t posSplitArc = 0;
    vector<string> vStringArc;
    while (( posSplitArc = arcsText.find(",")) != std::string::npos) {
        vStringArc.push_back(arcsText.substr(0,posSplitArc));
        arcsText.erase(0, posSplitArc + 1); // +1 : longeur du delimiteur pour chaque element d'un arc
    }

    // AJOUTE LE SOMMET TERMINAL DU DERNIER ARC
    vStringArc.push_back(arcsText);

    // VERIFIE SI LA DECLARARIONT DU DERNIER ARC A BIEN 3 ELEMENTS
    if(vStringArc.size()!=3)THROW_EXEPTION( "Erreur l'arc '"+arcsText+"' ne contien pas 3 elements dans sa declarartion, verifier la syntaxe au niveau de ',,' ou [,,] .");

    graphe.ajouterArc(vStringArc[0],atof(vStringArc[1].c_str()),vStringArc[2]);

    return graphe;*/

}
/**
 * @brief GrapheFileReader::stripString : PERMET DE NETOYER UN STRING
 * @param str : LE STRING A NETOYER
 */
void LectureDeFichierDeContrainte::stripString(string &str, char chars[]){

           while(chars != '\0')
          str.erase (std::remove(str.begin(), str.end(), (*chars)++), str.end());

}