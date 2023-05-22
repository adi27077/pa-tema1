#include <bits/stdc++.h>
using namespace std;

#define MOD ((int)1e9+7)

class Crypto {
 public:
    void solve() {
        read_input();
        get_result();
        print_results();
    }

 private:
    int n, l, res = 0;
    string k, s;

    vector<int> p, target;
    vector<bool> char_exists;

    void get_result() {
        char_exists.assign(26, false);

        for (const auto &c : s) {
            if (char_exists[c - 'a'] == false) {
                char_exists[c - 'a'] = true;
            }
        }

        count_subsq_all();
    }

    void count_subsq_all() {
        vector<vector<int>> dp(n + 1, vector<int>(l + 1, 0));

        /*caz de baza*/
        for (int i = 0; i <= n; i++) {
            dp[i][0] = 1;
        }

        /*caz general*/
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= l; j++) {
                if (k[i - 1] == '?') {
                    /*in cazul in care caracterul curent din cheie
                    este '?' luam in calcul toate variantele*/
                    int tmp_res = 0;
                    for (char c = 0; c < 26; c++) {
                        if (char_exists[c]) {
                            if (c + 'a' == s[j - 1]) {
                                /*in cazul in care caracterul curent din cheie
                                este egal cu caracterul curent din subsir
                                inseamna ca adunam si rezultatul de la
                                ambele caractere anterioare si cel de la
                                caracterul anterior din cheie*/
                                tmp_res = ((dp[i - 1][j - 1] + dp[i - 1][j])
                                    % MOD + tmp_res) % MOD;
                            } else {
                                /*daca cele doua caractere nu sunt egale,
                                copiem doar rezultatul de la caracterul
                                anterior din cheie*/
                                tmp_res = (dp[i - 1][j] + tmp_res) % MOD;
                            }
                        }
                    }
                    dp[i][j] = tmp_res;
                } else {
                    if (k[i - 1] == s[j - 1]) {
                        /*in cazul in care caracterul curent din cheie
                        este egal cu caracterul curent din subsir
                        inseamna ca adunam si rezultatul de la
                        ambele caractere anterioare si cel de la
                        caracterul anterior din cheie*/
                        dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j]) % MOD;
                    } else {
                        /*daca cele doua caractere nu sunt egale,
                        copiem doar rezultatul de la caracterul
                        anterior din cheie*/
                        dp[i][j] = dp[i - 1][j];
                    }
                }
            }
        }
        res = dp[n][l];
    }

    void read_input() {
        ifstream fin("crypto.in");
        fin >> n >> l;

        fin >> k >> s;

        fin.close();
    }

    void print_results() {
        ofstream fout("crypto.out");

        fout << res;

        fout.close();
    }
};

int main() {
    auto* crypto = new (nothrow) Crypto();
    if (!crypto) {
        cerr << "new failed: WTF are you doing? Throw your PC!\n";
        return -1;
    }
    crypto->solve();
    delete crypto;

    return 0;
}
