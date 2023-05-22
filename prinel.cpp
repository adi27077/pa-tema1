#include <bits/stdc++.h>
using namespace std;

class Prinel {
 public:
    void solve() {
        read_input();
        get_result();
        print_results();
    }

 private:
    int n, k, res = 0, max_elem = 0;

    vector<int> p, target;

    void get_result() {
        /*aici vom tine minte nr de operatii pentru a 
        ajunge la orice nr pana la cel mai mare nr din sir*/
        vector<int> dp_target(max_elem + 1, INT32_MAX);

        find_min_operations(max_elem, dp_target);

        /*verificam daca incap toate nr in nr maxim de operatii permis*/
        int op_sum = 0;

        for (int i = 1; i <= n; i++) {
            op_sum += dp_target[target[i]];
        }

        if (op_sum <= k) {
            for (const auto &points : p) {
                res += points;
            }
            return;
        }

        /*in cazul in care nu incap toate avem problema rucsac unde
        fiecare nr este un obiect, nr de operatii pentru a ajunge
        la acel nr este greutatea obiectul, iar nr de puncte obtinut
        este profitul*/
        vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));

        /*caz de baza*/
        for (int cap = 0; cap <= k; ++cap) {
            dp[0][cap] = 0;
        }

        /*caz general*/
        for (int i = 1; i <= n; ++i) {
            for (int cap = 0; cap <= k; ++cap) {
                dp[i][cap] = dp[i-1][cap];

                if (cap - dp_target[target[i]] >= 0) {
                    int sol_aux = dp[i-1][cap - dp_target[target[i]]] + p[i];

                    dp[i][cap] = max(dp[i][cap], sol_aux);
                }
            }
        }
        res = dp[n][k];
    }

    int find_min_operations(int target, vector<int> &dp) {
        /*daca targetul este 1 avem 0 operatii*/
        if (target == 1)
            return 0;

        /*caz de baza*/
        dp[1] = 0;
        dp[2] = 1;

        /*caz general*/
        for (int i = 2; i <= target; i++) {
            for (int d = 1; d * d <= i; d++) {
                if (i % d == 0) {
                    if (i + d <= target) {
                        dp[i + d] = min(dp[i + d], dp[i] + 1);
                    }

                    /*completam dp si pt divizorul complementar*/
                    if (i + i / d <= target) {
                        dp[i + i / d] = min(dp[i + i / d], dp[i] + 1);
                    }
                }
            }
        }

        return dp[target];
    }

    void read_input() {
        ifstream fin("prinel.in");
        fin >> n >> k;
        target.reserve(n + 1);
        p.reserve(n + 1);
        int x;
        target.push_back(0);
        p.push_back(0);

        for (int i = 1; i <= n; i++) {
            fin >> x;
            /*calculam elementul maxim la citire*/
            if (x > max_elem)
                max_elem = x;
            target.push_back(x);
        }

        for (int i = 1; i <= n; i++) {
            fin >> x;
            p.push_back(x);
        }

        fin.close();
    }

    void print_results() {
        ofstream fout("prinel.out");

        fout << res;

        fout.close();
    }
};

int main() {
    auto* prinel = new (nothrow) Prinel();
    if (!prinel) {
        cerr << "new failed: WTF are you doing? Throw your PC!\n";
        return -1;
    }
    prinel->solve();
    delete prinel;

    return 0;
}
