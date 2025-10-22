#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n = 100;
    if (argc >= 2) n = atoi(argv[1]);
    if (n <= 0 || n > 5000) {
        cerr << "n invalide (1..5000)\n";
        return 1;
    }

    // seed optionnelle en argv[2] pour reproductibilité
    mt19937 gen( (argc >= 3) ? (uint32_t)strtoul(argv[2], nullptr, 10)
                             : random_device{}() );
    uniform_int_distribution<int> dist(-10000, 10000);

    ofstream fout("INPMONOSEQ.txt");
    if (!fout) {
        cerr << "Impossible d'ouvrir INPMONOSEQ.txt\n";
        return 1;
    }

    fout << n << "\n";
    for (int i = 0; i < n; ++i) {
        if (i) fout << ' ';
        fout << dist(gen);
    }
    fout << "\n";

    cout << "OK: INPMONOSEQ.txt écrit avec " << n << " entiers\n";
    return 0;
}
