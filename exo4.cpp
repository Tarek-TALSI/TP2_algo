#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

/*
De même que pour l'exercice 2 la méthode de résolution n'est pas triviale donc je vais l'expliquer rapidement:

Le but est de trouver toutes les composantes connexes d’un graphe non orienté à partir de 
sa matrice d’adjacence. On lit le graphe depuis un fichier, on construit la matrice, puis 
on parcourt chaque sommet avec une recherche en profondeur (DFS). À chaque parcours, 
on marque les sommets reliés entre eux : ce groupe de sommets forme une composante connexe.

Exemple :
Graphe avec 5 sommets et 4 arêtes :
1 2
3 4
3 5
4 5

Matrice d’adjacence :
   1 2 3 4 5
1 [0 1 0 0 0]
2 [1 0 0 0 0]
3 [0 0 0 1 1]
4 [0 0 1 0 1]
5 [0 0 1 1 0]

→ On commence au sommet 1 : on découvre 1 et 2 (1ère composante)
→ Puis au sommet 3 : on découvre 3, 4, 5 (2ème composante)

Résultat : 
composante connexe 1 → 1 2
composante connexe 2 → 3 4 5

J’ai choisi cette méthode car la matrice d’adjacence permet de visualiser facilement les liens 
entre sommets, ce qui rend la logique du DFS plus intuitive à comprendre.
*/

void dfs_matrice(int u, const vector<vector<int>>& adj, vector<bool>& visite, vector<int>& composante) {
    visite[u] = true;
    composante.push_back(u + 1); 
    for (int v = 0; v < adj.size(); v++) {
        if (adj[u][v] && !visite[v])
            dfs_matrice(v, adj, visite, composante);
    }
}

int main() {
    ifstream fin("INPCONGRAPH.TXT");
    ofstream fout("OUTCONGRAPH.TXT");

    int n, m;
    fin >> n >> m;

    vector<vector<int>> adj(n, vector<int>(n, 0));

    for (int i = 0; i < m; i++) {
        int a, b;
        fin >> a >> b;
        adj[a - 1][b - 1] = 1;
        adj[b - 1][a - 1] = 1;
    }

    vector<bool> visite(n, false);
    vector<vector<int>> composantes;

    for (int i = 0; i < n; i++) {
        if (!visite[i]) {
            vector<int> comp;
            dfs_matrice(i, adj, visite, comp);
            composantes.push_back(comp);
        }
    }

    fout << composantes.size() << endl;
    for (int i = 0; i < composantes.size(); i++) {
        fout << "composante connexe " << i + 1 << endl;
        for (int sommet : composantes[i])
            fout << sommet << " ";
        fout << endl;
    }

    return 0;
}
