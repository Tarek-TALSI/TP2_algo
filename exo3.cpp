#include <fstream>
#include <vector>
#include <utility>

int main() {
    std::ifstream in("INPARBGRAPH.TXT");
    if (!in) return 1;

    int n, m;
    in >> n >> m;

    std::vector<std::vector<int>> A(n + 1, std::vector<int>(n + 1, 0));
    for (int k = 0; k < m; ++k) {
        int u, v; in >> u >> v;
        if (u == v) continue;
        if (u >= 1 && u <= n && v >= 1 && v <= n) {
            ++A[u][v];
            ++A[v][u];
        }
    }
    in.close();

    std::vector<int> seen(n + 1, 0), idx(n + 1, 1), st;
    std::vector<std::pair<int,int>> T;
    st.push_back(1);
    seen[1] = 1;

    while (!st.empty() && (int)T.size() < n - 1) {
        int u = st.back();
        bool advanced = false;
        for (int &j = idx[u]; j <= n; ++j) {
            if (A[u][j] > 0 && !seen[j]) {
                seen[j] = 1;
                st.push_back(j);
                T.emplace_back(u, j);
                ++j;
                advanced = true;
                break;
            }
        }
        if (!advanced) st.pop_back();
    }

    if ((int)T.size() != n - 1) return 2;

    std::ofstream out("OUTARBGRAPH.TXT");
    for (auto &e : T) out << e.first << ' ' << e.second << '\n';
    out.close();
    return 0;
}
