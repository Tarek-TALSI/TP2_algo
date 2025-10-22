#include "exo1.hpp"
#include <algorithm>
#include <iostream>

vector<int> read_seq(const string& filename){
    ifstream fin(filename);
    int list_size;
    fin >> list_size;
    vector<int> list_of_number(list_size);
    for(int i=0;i<list_size;i++){
        fin >> list_of_number[i];
    }
    return list_of_number;
}

void genmonoseq(const string &filename){
    vector<int> original_list = read_seq(filename);
    int list_size = original_list.size();

    vector<int> seq_i_size(list_size, 1), prev(list_size, -1);

    for (int i = 0; i < list_size; ++i) {
        for (int j = 0; j < i; ++j) {
            if (original_list[j] < original_list[i] && seq_i_size[j] + 1 > seq_i_size[i]) {
                seq_i_size[i] = seq_i_size[j] + 1;
                prev[i] = j;
            }
        }
    }
    int i_max = 0;
    for(int i=0;i<list_size;i++){
        if(seq_i_size[i]>seq_i_size[i_max]){
            i_max = i;
        }
    }
    vector<int> index;
    while (i_max != -1) {
        index.push_back(i_max);
        i_max = prev[i_max];
    }
    reverse(index.begin(), index.end());

    writelongestseq("OUTMONOSEQ.txt", original_list, index);
}

void writelongestseq(const string& filename, const vector<int>& data, const vector<int>& addr) {
    ofstream fout(filename);
    if (!fout) {
        std::cerr << "Erreur: impossible d'ouvrir " << filename << "\n";
        return;
    }

    // longueur
    fout << addr.size() << "\n";

    // lignes "a[i] = valeur"
    for (int idx : addr) {
        fout << "a[" << (idx + 1) << "] = " << data[idx] << "\n";
    }

    fout.close();
}

int main(){
    genmonoseq("INPMONOSEQ.txt");
    return 0;
}