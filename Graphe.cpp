//
// Created by Antoine Hintzy on 16/03/2020.
//

#include "Graphe.h"
#include <fstream>
#include <queue>
#include <stack>
#include <list>
#include <vector>
#include <stdexcept>


Graphe::Graphe(std::string cheminFichierGraphe) {
    std::ifstream ifs{cheminFichierGraphe};
    if(!ifs) {
        throw std::runtime_error("Impossible d'ouvrir " + cheminFichierGraphe);
    }
    ifs >> m_estOriente;
    if(ifs.fail()) {
        throw std::runtime_error("Problème de lecture de l'orientation du graphe.");
    }
    int ordre;
    ifs >> ordre;
    if(ifs.fail()) {
        throw std::runtime_error("Problème de lecture de l'ordre du graphe.");
    }
    int taille;
    ifs >> taille;
    if(ifs.fail()) {
        throw std::runtime_error("Problème de lecture de la taille du graphe.");
    }
    for(int i=0; i<ordre; ++i) {
        m_sommets.push_back(new Sommet(i));
    }
    int num1, num2;
    for(int i=0; i<taille; ++i) {
        ifs >> num1 >> num2;
        if(ifs.fail()) {
            throw std::runtime_error("Problème de lecture d'un.e arc/arête.");
        }
        m_sommets[num1]->addSuccesseur(m_sommets[num2]);
        if(!m_estOriente && num1 < num2) {
            m_sommets[num2]->addSuccesseur(m_sommets[num1]);
        }
    }
}

Graphe::~Graphe() {
    for(auto addrSommet : m_sommets) {
        delete addrSommet;
    }
}

void Graphe::afficher() const {
    std::cout << std::endl << "Graphe ";
    std::cout << (m_estOriente ? "orienté" : "non orienté") << std::endl;
    std::cout << "Ordre : " << m_sommets.size() << std::endl;
    std::cout << "Liste d'adjacences : " << std::endl;
    for(auto addrSommet : m_sommets) {
        addrSommet->afficher();
        std::cout << std::endl;
    }

}

// Algo parcoursBFS(s0)
std::vector<int> Graphe::BFS(int numero_s0) const {
    // 1. Tous les sommets sont blancs (non découverts)
    std::vector<int> couleurs((int) m_sommets.size(), 0);
    // 2. Créer une file vide
    std::queue<const Sommet*> file;
    std::vector<int> predecesseurs((int) m_sommets.size(), -1);
    // 3. Enfiler s0 ; s0 devient gris
    file.push(m_sommets[numero_s0]);
    couleurs[numero_s0] = 1; // 0 = blanc, 1 = gris, 2 = noir
    const Sommet* s;
    // 4. Tant que la file n’est pas vide :
    while(!file.empty()) {
        // 4.1 Défiler le prochain sommet s de la file (Traitement éventuel sur s)
        s = file.front();
        file.pop();
        // 4.2 Pour chaque successeur s’ blanc (non découvert) de s :
        for(auto succ : s->getSuccesseurs()) {
            if(couleurs[succ->getNumero()] == 0) { // blanc
                // 4.2.1 Enfiler s’; s’ devient gris
                file.push(succ);
                couleurs[succ->getNumero()] = 1; // gris
                // 4.2.2 Noter que s est le prédécesseur de s’
                predecesseurs[succ->getNumero()] = s->getNumero();
            }
        }
        // 4.3 s devient noir (exploré)
        couleurs[s->getNumero()] = 2;
    }
    return predecesseurs;
}

std::vector<int> Graphe::DFS(int numero_s0, std::vector<int> couleurs, std::queue<const Sommet*> queueDFS, std::vector<int> predecesseurs)  {                         //Parcours DFS(s0)

    queueDFS.push(m_sommets[numero_s0]);                                 //On compte s0 et on le passe à gris
    couleurs[numero_s0] = 1;                                                // 0 = blanc, 1 = gris, 2 = noir
    const Sommet* s = queueDFS.front();
    queueDFS.pop();
    //m_sommets[numero_s0]->getSuccesseurs();
    //while (!couleurs.empty()){

        //const Sommet* s = stack.top();                                     //On change de sommet en tête de file
        //couleurs.pop();

        for(auto succ : m_sommets[numero_s0]->getSuccesseurs()) {

            if(couleurs[succ->getNumero()] == 0) {                           // Si il est blanc on ne l'a pas vu
                // Donc on le rajoute au stack
                /*stack.push(succ);
                couleurs[succ->getNumero()] = 1;  */                         // On le met en gris (on vient de tomber dessus)
                predecesseurs[succ->getNumero()] = s->getNumero();
                DFS(succ->getNumero(), couleurs, queueDFS, predecesseurs);

            }
        }
        couleurs[s->getNumero()] = 2;                                      // On met le sommet en noir
    //}

    return predecesseurs;
}

/*void Graphe::DFSRecur(int numero_s0, bool visite[]) {
                    visite[numero_s0] = true;
                    std::cout << numero_s0 << " ";
                    std::list<int>::iterator i;
                    for (i = adj[numero_s0].begin(); i != adj[numero_s0].end(); i++) {
                        if (!visite[*i]) {
                            DFSRecur(*i, visite);
                        }
                    }
 }*/

/*std::vector<int> Graphe::initDFS(int numero_s0, std::vector<int> couleurs, std::queue<const Sommet*> queueDFS, std::vector<int> predecesseurs){
    /*int nbSom = getSize();
    bool *visite = new bool[nbSom];
    for(int i = 0; i < nbSom; i++){
        visite[i] = false;
    }*/
    /*queueDFS.push(m_sommets[numero_s0]);                                 //On compte s0 et on le passe à gris
    couleurs[numero_s0] = 1;                                                // 0 = blanc, 1 = gris, 2 = noir
    const Sommet* s = queueDFS.front();
    queueDFS.pop();
    DFS(numero_s0, couleurs, queueDFS, predecesseurs, s);

    return predecesseurs;
}*/

int Graphe::getSize() const{
    return m_sommets.size();
}

std::vector< std::vector<int> > Graphe::composantesConnexes() const{

    std::vector<int> couleurs((int) m_sommets.size(), 0);
    std::vector<std::vector<int>> composantes;

    for(int i = 0; i <= m_sommets.size(); i++){                          // On boucle sur tous les sommets
        if(couleurs.at(i) == 0) {
            std::vector<int> composante;
            std::vector<int> bfsPath = BFS(i);
            for (auto som : composante) {
                if (couleurs.at(som) == 0) {
                    composante.push_back(som);
                    couleurs.at(som) = 2;
                }
            }
            couleurs.at(i) = 2;
            if (composante.size()) {
                composantes.push_back(composante);
            }
        }
    }
    return composantes;
}

bool Graphe::eulerien() {
    BFS(1);
    BFS(11);            //Mettre dans BFS un compteur de degrés des sommets
    BFS(14);
}
