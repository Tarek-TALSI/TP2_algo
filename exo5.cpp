#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
using namespace std;

/*
Cette méthode n'est surement pas la plus optimisé mais je n'ai pas trouvé mieux.

Principe :
On part du sommet de départ, puis à chaque étape :
- on cherche parmi les sommets non visités celui qui a la plus petite distance actuelle.
- ensuite, on met à jour les distances de tous ses voisins.
On répète jusqu’à avoir visité tous les sommets ou atteint le sommet d’arrivée.

Exemple rapide :
Graphe :
1 2 1
2 3 2
3 4 5

Départ : 1, arrivée : 4
→ Distances au début : [0, ∞, ∞, ∞]
→ Après avoir visité 1 : dist(2)=1
→ Après 2 : dist(3)=3
→ Après 3 : dist(4)=8
Résultat : distance = 8, chemin = 1 → 2 → 3 → 4
*/

int main() {
    ifstream fin("INPDIJGRAPH.TXT");
    ofstream fout("OUTDIJGRAPH.TXT");

    int n, m, start, end;
    fin >> n >> m >> start >> end;

    const int INF = 999999;
    vector<vector<int>> adj(n + 1, vector<int>(n + 1, INF));

    
    for (int i = 0; i < m; i++) {
        int a, b, w;
        fin >> a >> b >> w;
        adj[a][b] = w;
        adj[b][a] = w; 
    }

    vector<int> dist(n + 1, INF);
    vector<bool> visite(n + 1, false);
    vector<int> precedent(n + 1, -1);

    dist[start] = 0;

    
    for (int i = 1; i <= n; i++) {
        
        int u = -1, minDist = INF;
        for (int j = 1; j <= n; j++) {
            if (!visite[j] && dist[j] < minDist) {
                minDist = dist[j];
                u = j;
            }
        }

        if (u == -1) break; 
        visite[u] = true;

        
        for (int v = 1; v <= n; v++) {
            if (!visite[v] && adj[u][v] < INF) {
                int newDist = dist[u] + adj[u][v];
                if (newDist < dist[v]) {
                    dist[v] = newDist;
                    precedent[v] = u;
                }
            }
        }
    }

    
    vector<int> chemin;
    for (int at = end; at != -1; at = precedent[at])
        chemin.insert(chemin.begin(), at);

    
    fout << dist[end] << endl;
    for (int i = 0; i < (int)chemin.size(); i++) {
        fout << chemin[i];
        if (i < (int)chemin.size() - 1) fout << " → ";
    }
    fout << endl;

    return 0;
}
