#include <time.h>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <vector>
using namespace std;
const int MAXN = 150000000 + 5;
const int mm = 150000000 + 4;
int n, length;
clock_t start_time, end_time;
int cmap[256], ans;
vector<int> OD(MAXN, 0), ID(MAXN, 0), result(MAXN, 0), level(MAXN, 0);
vector<bool> vis(MAXN, false);
string s[3005];
vector<int> ST[3005][5];
vector<vector<int> > G(MAXN), pre(MAXN), Set(MAXN);
map<vector<int>, int> mp;
double tot;
int maxcnt, id;
queue<int> q;
struct cmp1 {
    bool operator()(int a, int b) { return ID[a] > ID[b]; }
};

void Init() {
    mp.clear();
    cmap['A'] = 1;
    cmap['T'] = 2;
    cmap['C'] = 3;
    cmap['G'] = 4;
    maxcnt = 0;
    id = 0;
}

void Construct_ST() {
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < length; j++) {
            int d = ST[i][cmap[s[i][j]]].size();
            for (int k = d; k <= j; k++) {
                ST[i][cmap[s[i][j]]].push_back(j + 1);
            }
        }
    }
}

void Construct() {
    cout << "start Construct" << endl;
    q.push(1);
    for (int i = 0; i < n; i++) {
        Set[1].push_back(0);
        Set[mm].push_back(mm);
    }
    mp[Set[1]] = 1;
    ans = 2;
    int flag = 0, number = 0;
    int p;
    while (!q.empty()) {
        p = q.front();
        q.pop();
        if (vis[p]) {
            continue;
        }
        vis[p] = true;
        number = 0;
        flag = 0;
        for (int i = 1; i <= 4; i++) {
            flag = 0;
            for (int j = 1; j <= n; j++) {
                if (ST[j][i].size() > Set[p][j - 1]) {
                    Set[ans].push_back(ST[j][i][Set[p][j - 1]]);
                } else {
                    flag = 1;
                    break;
                }
            }
            if (flag == 0) {
                int ddt;
                if (mp[Set[ans]] == 0) {
                    mp[Set[ans]] = ans;
                    ddt = ans;
                    ans++;
                    q.push(ddt);
                } else {
                    ddt = mp[Set[ans]];
                    Set[ans].clear();
                }
                G[p].push_back(ddt);
                ID[ddt]++;
                OD[p]++;
                number++;
            } else {
                Set[ans].clear();
            }
        }
        if (number == 0) {
            if (p != mm) {
                G[p].push_back(mm);
                OD[p]++;
                ID[mm]++;
            }
        }
    }
    cout << ans << endl;
    cout << "over Construct" << endl;
}

void ForwardTopSort() {
    cout << "start  ForwardTopSort" << endl;
    maxcnt = 0;
    q.push(1);
    level[1] = 1;
    int p;
    while (!q.empty()) {
        p = q.front();
        q.pop();
        int d = G[p].size();
        if (p != mm) maxcnt = max(maxcnt, level[p]);
        for (int i = 0; i < d; i++) {
            ID[G[p][i]]--;
            pre[G[p][i]].push_back(p);
            if (ID[G[p][i]] == 0) {
                q.push(G[p][i]);
                level[G[p][i]] = level[p] + 1;
            }
        }
        G[p].clear();
    }
    cout << "over  ForwardTopSort" << endl;
}
void BackwardTopSort() {
    cout << "start BackwardTopSort" << endl;
    int p;
    level[mm] = maxcnt + 1;
    q.push(mm);
    while (!q.empty()) {
        p = q.front();
        q.pop();
        if (vis[p]) {
            continue;
        }
        vis[p] = true;
        int d = pre[p].size();
        int nowlevel = level[p];
        for (int i = 0; i < d; i++) {
            if (level[pre[p][i]] == nowlevel - 1) {
                q.push(pre[p][i]);
                G[pre[p][i]].push_back(p);
            }
        }
    }
    cout << "over BackwardTopSort" << endl;
}

void dfs(int x, int number) {
    int d = G[x].size();
    if (x == mm) {
        id++;
        cout << "The " << id << " mlcs is : ";
        for (int i = 0; i < number - 1; i++) {
            cout << s[1][Set[result[i]][0] - 1];
        }
        cout << "\n";
        return;
    }
    for (int i = 0; i < G[x].size(); i++) {
        result[number] = G[x][i];
        dfs(G[x][i], number + 1);
    }
}
void Output() {
    cout << "length of mlcs is : " << maxcnt - 1 << endl;
    dfs(1, 0);
}
void TOP_MLCS() {
    clock_t n1 = clock();
    double p = 0;
    Construct_ST();
    clock_t n2 = clock();
    p = ((double)(n2 - n1)) / CLOCKS_PER_SEC;
    tot += p;
    cout << " Construct_ST time : " << p << "\n";
    Construct();
    n1 = clock();
    p = ((double)(n1 - n2)) / CLOCKS_PER_SEC;
    tot += p;
    cout << "Construct  time : " << p << "\n";
    ForwardTopSort();
    n2 = clock();
    p = ((double)(n2 - n1)) / CLOCKS_PER_SEC;
    tot += p;
    cout << "ForwardTopSort time :" << p << "\n";
    vis = vector<bool>(MAXN, false);
    n2 = clock();
    BackwardTopSort();
    n1 = clock();
    p = ((double)(n1 - n2)) / CLOCKS_PER_SEC;
    tot += p;
    cout << "BackwardTopSort time :" << p << "\n";
    Output();
}
int main() {
    Init();
    n = 0;
    tot = 0;
    while (cin >> s[n + 1]) {
        ++n;
    }
    cout << n << endl;
    length = s[1].size();
    TOP_MLCS();
    cout << "total time : " << tot << "\n";
    cout << maxcnt - 1 << endl;
    return 0;
}
