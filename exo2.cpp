#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

/* Cette méthode m'a été expliqué par un camarade et est peu compliqué à comprendre au début donc je 
l'explique et l'illustre avec un exemple simple dans ce commentaire:

On parcourt les nombres de la séquence un par un. Pour chaque nombre, on regarde toutes les sous-séquences 
qu’on a déjà et on calcule le reste de leur somme modulo k si on ajoute ce nouveau nombre. 
Pour chaque reste possible, on garde la sous-séquence la plus longue qui donne ce reste.Au fur et à mesure,
on met à jour ces sous-séquences pour chaque reste. À la fin, la sous-séquence correspondant au reste 0 est
la plus longue sous-séquence dont la somme est divisible par k. 
J'ai choisi cette méthode pour ne pas avoir à calculer toutes les combinaisons possible(qui est ce j'aurai
fait sans mon camarade)

Exemple:

Séquence : [3, 1, 4, 2]
k = 3
et le dp qui sera le vecteur contenant les restes [0, -1, -1]     
(l'indice 0 correspond à la somme maximum parmi les combinaisons qui a le reste 0 et ainsi de suite pour le -1 qui sera de reste 1)


Étape 1 : ajouter 3
Pour reste 0 : (0+3)%3=0 => longueur = dp[0]+1 = 1
dp = [1, -1, -1] ici on rajoute 1 car la plus grande combinaison donnant un reste 0 est 1 

Étape 2 : ajouter 1
Pour reste 0 : (0+1)%3=1 => longueur = dp[0]+1 = 2
dp = [1,2,-1]

Étape 3 : ajouter 4
Pour reste 0 : (0+4)%3=1 => longueur = dp[0]+1=2 => dp_new[1]=max(2,2)=2
Pour reste 1 : (1+4)%3=2 => longueur = dp[1]+1=3 => dp_new[2]=3
dp = [1,2,3]

Étape 4 : ajouter 2
Pour reste 0 : (0+2)%3=2 → longueur = dp[0]+1=2 → dp_new[2]=max(3,2)=3 
Pour reste 1 : (1+2)%3=0 → longueur = dp[1]+1=3 → dp_new[0]=3
Pour reste 2 : (2+2)%3=1 → longueur = dp[2]+1=4 → dp_new[1]=4
dp = [3,4,3]

Donc la plus grande combinaison est de taille 3 avec les nombres qui ont permi d'incrémenter ce 3 à savoir 1,2,3.

C'est cette méthode que j'ai généralisé dans le code.
*/

int main() {
    vector<int> valeurs;
    int val;

    ifstream fichier("INPDIVSEQ.TXT");
    while (fichier >> val) valeurs.push_back(val);
    fichier.close();

    int k = 49;

    vector<int> dp(k, -1);
    dp[0] = 0;

    vector<vector<int>> subseq(k);
    subseq[0] = {};

    for (int i = 0; i < valeurs.size(); i++) {
        vector<int> dp_new = dp;
        vector<vector<int>> subseq_new = subseq;

        for (int r = 0; r < k; r++) {
            if (dp[r] != -1) {
                int new_r = (r + valeurs[i]) % k;
                if (dp_new[new_r] < dp[r] + 1) {
                    dp_new[new_r] = dp[r] + 1;
                    subseq_new[new_r] = subseq[r];
                    subseq_new[new_r].push_back(valeurs[i]);
                }
            }
        }

        dp = dp_new;
        subseq = subseq_new;
    }

    int sum_test = 0;
    for (int x : subseq[0]) sum_test += x;

    ofstream sortie("OUTDIVSEQ.TXT");
    sortie << dp[0] << endl;
    for (int i = 0; i < subseq[0].size(); i++) {
        sortie << "a[" << dp[0] - i << "] = " << subseq[0][i] << endl;
    }
    sortie << "Sum = " << sum_test << endl;
    sortie.close();

    cout << "Max nombre d'éléments dont la somme est divisible par " << k << " : " << dp[0] << endl;
    return 0;
}
