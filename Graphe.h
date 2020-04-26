//
// Created by Antoine Hintzy on 16/03/2020.
//

#ifndef TP2_TG_GRAPHE_H
#define TP2_TG_GRAPHE_H

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <list>
#include <string>
#include "Sommet.h"

class Graphe {
private:
    bool m_estOriente;
    std::vector<Sommet*> m_sommets;
    void DFSRecur(int numero_s0, bool visite[]);
    std::list<int> *adj;
public:
    Graphe(std::string cheminFichierGraphe);
    ~Graphe();
    void afficher() const;
    std::vector<int> BFS(int numero_s0) const;
    std::vector<int> DFS(int numero_s0, std::vector<int> couleurs, std::queue<const Sommet*> queueDFS, std::vector<int> predecesseurs);
    //std::vector<int> initDFS(int numero_s0, std::vector<int> couleurs, std::queue<const Sommet*> queueDFS, std::vector<int> predecesseurs);
    //void DFS(int numero_s0);
    int getSize() const;
    std::vector< std::vector<int> > composantesConnexes() const;
    bool eulerien();
};


#endif //TP2_TG_GRAPHE_H