#include <vector>
#include <string>
#include <fstream>

using namespace std;

vector<int> read_seq(const string& filename);

void genmonoseq(const string& filename);

void writelongestseq(const string& filename, const vector<int>& data, const vector<int>& addr);

vector<vector<int>> txt_to_matrix(const string& filename);