#include <iostream>
#include <stack>
#include <queue>
#include "Graphe.h"

void afficherParcours(size_t s0, const std::vector<int>& precesseur) {
    for(size_t i = 0; i < precesseur.size(); ++i) {
        if (i != s0) {
            if(precesseur[i] != -1) {
                std::cout << i << " <--- ";
                size_t j = precesseur[i];
                while(j != s0) {
                    std::cout << j << " <--- ";
                    j = precesseur[j];
                }
                std::cout << j << std::endl;
            }
        }
    }
}

int main() {
    size_t s0 = 0;
    Graphe g{"../graphe-no-1.txt"};
    std::vector<int> arborescence;
    g.afficher();

    std::cout << std::endl << "BFS : Veuillez saisir le numero du sommet initial pour la recherche du plus court chemin : ";
    std::cin >> s0;
    arborescence = g.BFS(s0);
    std::cout << "Plus courts chemins depuis le sommet " << s0 << " (BFS) : " << std::endl;
    afficherParcours(s0, arborescence);

    std::cout << std::endl << "DFS : Veuillez saisir le numero du sommet initial pour la recherche du plus court chemin : ";
    std::cin >> s0;
    std::vector<int> couleurs((int) g.getSize(), 0) ;
    std::queue<const Sommet*> queueDFS;                                           //On met tous les sommets à blanc et on créé un file vide
    std::vector<int> predecesseurs((int) g.getSize(), -1);              //En dehors de la fonction pour que ce ne soit pas remis à 0 lors de la récursivité
    arborescence = g.DFS(s0, couleurs, queueDFS, predecesseurs);
    std::cout << "Plus courts chemins depuis le sommet " << s0 << " (DFS) : " << std::endl;
    afficherParcours(s0, arborescence);

    g.composantesConnexes();
    return 0;
}