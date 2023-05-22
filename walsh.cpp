#include <bits/stdc++.h>
using namespace std;

class Walsh {
 public:
    void solve() {
        read_input();
        get_result();
        print_results();
    }

 private:
    int n, k;

    vector<pair<int, int>> coords;
    vector<int> results;

    void get_result() {
        int x, y;

        for (const auto &coord : coords) {
            x = coord.first;
            y = coord.second;

            int res = n == 0 ? 0 : helper(x, y, n);

            results.push_back(res);
        }
    }

    int helper(int x, int y, int size) {
        /*intram pe primul cadran*/
        if ((x <= size / 2) && (y <= size / 2)) {
            if (size == 2)
                return 0;

            return helper(x, y, size / 2);
        /*intram in al doilea cadran*/
        } else if ((x <= size / 2) && (y > size / 2)) {
            if (size == 2)
                return 0;

            return helper(x, y - size / 2, size / 2);
        /*intram in al treilea cadran*/
        } else if ((x > size / 2) && (y <= size / 2)) {
            if (size == 2)
                return 0;

            return helper(x - size / 2, y, size / 2);
        /*intram in ultimul cadran, caz in care rezultatul trebuie negat*/
        } else {
            if (size == 2)
                return 1;

            return (helper(x - size / 2, y - size / 2, size / 2) == 1) ? 0 : 1;
        }
    }

    void read_input() {
        int x, y;
        pair<int, int> coord;
        ifstream fin("walsh.in");
        fin >> n >> k;
        coords.reserve(k);

        for (int i = 0; i < k; i++) {
            fin >> x >> y;
            coord.first = x;
            coord.second = y;
            coords.push_back(coord);
        }

        fin.close();
    }

    void print_results() {
        ofstream fout("walsh.out");

        for (const auto &res : results) {
            fout << res << "\n";
        }

        fout.close();
    }
};

int main() {
    auto* walsh = new (nothrow) Walsh();
    if (!walsh) {
        cerr << "new failed: WTF are you doing? Throw your PC!\n";
        return -1;
    }
    walsh->solve();
    delete walsh;
    return 0;
}
