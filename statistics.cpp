#include <bits/stdc++.h>
using namespace std;

typedef struct word_type {
    string word;
    int dominance;
}wordt;

class DominanceComparator {
 public:
    bool operator() (const wordt &s1, const wordt &s2) const {
        return s1.dominance > s2.dominance;
    }
};

class Statistics {
 public:
    void solve() {
        read_input();
        get_result();
        print_results();
    }

 private:
    int n, res = -1;
    char current_char;

    vector<bool> char_exists;
    vector<wordt> words;

    void get_result() {
        int local_max = 0, global_max = 0;

        for (char c = 'z'; c >= 'a'; c--) {
            /*nu ne intereseaza cazul in care caracterul nu exista
            in niciun cuvant*/
            if (char_exists[c - '0'] == false)
                continue;

            current_char = c;
            int current_char_max = 0;

            /*calculam dominanta literei curente pentru toate
            cuvintele*/
            for (auto &word : words) {
                word.dominance = dominant_char_diff(word.word);
            }

            /*sortam cuvintele dupa dominanta*/
            sort(words.begin(), words.end(), DominanceComparator());

            int dom_char_count = 0;
            int total_char_count = 0;

            /*calculam nr maxim de cuvinte pana cand nu mai avem
            litera dominanta*/
            for (const auto &word : words) {
                for (const auto &ch : word.word) {
                    if (ch == current_char)
                        dom_char_count++;
                    total_char_count++;
                }

                if (dom_char_count > total_char_count / 2) {
                    /*am adaugat un cuvant, iar litera dominata
                    s-a pastrat*/
                    current_char_max++;
                } else {
                    /*am ajuns la primul cuvant pentru care nu mai avem
                    litera dominanta*/
                    break;
                }
                local_max = current_char_max;
            }

            if (local_max > global_max) {
                global_max = local_max;
            }
        }

        if (global_max != 0)
            res = global_max;
    }

    int dominant_char_diff(const string &s) {
        /*dominanta este diferenta dintre nr de aparitii al literei
        curente (cea de verificat ca fiind dominanta) si nr de aparitii
        al restului de litere*/
        int difference = 0;
        for (const auto &ch : s) {
            if (ch == current_char)
                difference++;
            else
                difference--;
        }
        return difference;
    }

    void read_input() {
        string word;
        ifstream fin("statistics.in");
        fin >> n;
        words.reserve(n);
        char_exists.assign(26, false);

        for (int i = 0; i < n; i++) {
            fin >> word;
            for (const auto &ch : word) {
                char_exists[ch - '0'] = true;
            }
            wordt wordstruc;
            wordstruc.word = word;
            words.push_back(wordstruc);
        }

        fin.close();
    }

    void print_results() {
        ofstream fout("statistics.out");

        fout << res;

        fout.close();
    }
};

int main() {
    auto* statistics = new (nothrow) Statistics();
    if (!statistics) {
        cerr << "new failed: WTF are you doing? Throw your PC!\n";
        return -1;
    }
    statistics->solve();
    delete statistics;

    return 0;
}
