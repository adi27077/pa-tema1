#include <bits/stdc++.h>
using namespace std;

class Regele {
 public:
    void solve() {
        read_input();
        get_result();
        print_results();
    }

 private:
    int n, q;

    vector<int> coord, quest, res;

    void get_result() {
        int max_traders = *max(quest.begin(), quest.end());

        vector<int> dp(max_traders + 1, 0);

        for (const auto &no_traders : quest) {
        }
    }

    void read_input() {
        ifstream fin("regele.in");
        fin >> n;
        coord.reserve(n);
        int x;

        for (int i = 0; i < n; i++) {
            fin >> x;
            coord.push_back(x);
        }

        fin >> q;
        quest.reserve(q);
        res.reserve(q);

        for (int i = 0; i < n; i++) {
            fin >> x;
            quest.push_back(x);
        }

        fin.close();
    }

    void print_results() {
        ofstream fout("regele.out");

        for (const auto &x : res) {
            cout << x << "\n";
        }

        fout.close();
    }
};

int main() {
    auto* regele = new (nothrow) Regele();
    if (!regele) {
        cerr << "new failed: WTF are you doing? Throw your PC!\n";
        return -1;
    }
    regele->solve();
    delete regele;

    return 0;
}
