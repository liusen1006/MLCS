#include <time.h>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <vector>
using namespace std;
const long long MAXN = 150000000 + 5;
const long long mm = 150000000 + 4;
int n, length;

int cmap[256], ans;
vector<int> ID(MAXN, 0), OD(MAXN, 0);
string s[3005], s2[3005];
vector<int> ST[3005][5];
vector<vector<int> > G(MAXN);
vector<vector<int> > pre(MAXN);
vector<vector<int> > Set(MAXN);
int from[MAXN];
map<vector<int>, int> mp;
vector<int> result(MAXN, 0), cnt(MAXN, 0), level(MAXN, 0);
queue<int> q;
vector<bool> vis(MAXN, false);
int id, repeat[3005][205], dp[3005][205][5];
int maxcnt;
int c1, c2;
double tot = 0;
void Init() {
    mp.clear();
    memset(repeat, 0, sizeof(repeat));
    cmap['A'] = 1;
    cmap['C'] = 2;
    cmap['G'] = 3;
    cmap['T'] = 4;
    maxcnt = 0;
    id = 0;
    for (int i = 0; i < MAXN; i++) {
        from[i] = i;
    }
}
void Delete_char() {
    for (int i = 1; i <= n; i++) {
        int d = s[i].length(), k = 1;
        for (int j = 0; j < d; j++) {
            repeat[i][j]++;
        }
        for (int j = 1; j < d; j++) {
            if (s[i][k - 1] == s[i][k]) {
                s[i].erase(k - 1, 1);
                repeat[i][k - 1]++;
            } else {
                k++;
            }
        }
    }
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = 0; k < s[j].size(); k++) {
                if (k == 0) {
                    if (cmap[s[j][k]] == i)
                        dp[j][k][i] = repeat[j][k];
                    else {
                        dp[j][k][i] = 0;
                    }
                } else {
                    if (cmap[s[j][k]] == i)
                        dp[j][k][i] = dp[j][k - 1][i] + repeat[j][k];
                    else {
                        dp[j][k][i] = dp[j][k - 1][i];
                    }
                }
            }
        }
    }
}
void Construct_ST() {
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < s[i].length(); j++) {
            int d = ST[i][cmap[s[i][j]]].size();
            for (int k = d; k <= j; k++) {
                ST[i][cmap[s[i][j]]].push_back(j + 1);
            }
        }
    }
}
void Merge() {
    clock_t n1 = clock();
    double p = 0;
    Delete_char();
    clock_t n2 = clock();
    p = (double)(n2 - n1) / CLOCKS_PER_SEC;
    tot += p;
    cout << "Merage char time : " << p << "\n";
    Construct_ST();
    n1 = clock();
    p = (double)(n1 - n2) / CLOCKS_PER_SEC;
    tot += p;
    cout << "Construct_ST time : " << p << "\n";
}
int main() {
    Init();
    n = 0;
    while (cin >> s[n + 1]) {
        ++n;
    }
    cout << "number of strings :" << n << "\n";
    tot = 0;
    length = s[1].size();
    Merge();
    cout << "time : " << tot << "\n";
    cout << maxcnt << endl;
    return 0;
}
