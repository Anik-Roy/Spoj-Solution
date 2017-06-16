#include <bits/stdc++.h>
using namespace std;

const int fx[] = { -1, 1, 0, 0 }; /// 4 side moves.
const int fy[] = { 0, 0, -1, 1 };
const int dx[] = { 1, 1, 0, -1, -1, -1, 0, 1 }; /// 8 side moves.
const int dy[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
const int kx[] = { 1, 1, -1, -1, 2, 2, -2, -2 }; /// Knight Moves.
const int ky[] = { 2, -2, 2, -2, 1, -1, 1, -1 };

typedef  long long            ll;

typedef  map <int,int>	           mii;
typedef  map <int,string>	       mis;
typedef  map <ll, ll>              mll;
typedef  map <char,int>            mci;
typedef  map <string,int>          msi;
typedef  map <string, string>      mss;

typedef  pair <int,int> 	       pii;
typedef  pair <ll, ll>             pll;
typedef  pair <char,int>           pci;
typedef  pair <string,int>         psi;
typedef  pair <string, string>     pss;

typedef  vector<int> 	           vi;
typedef  vector<string> 	       vs;
typedef  vector<char>	           vc;
typedef  vector<bool>              vb;
typedef  vector < pii >            vii;

#define EPS                   1e-9
#define mp                    make_pair
#define pb                    push_back
#define clr(ara)              memset(ara, 0, sizeof(ara))
#define dp(ara)            memset(ara, -1, sizeof(ara))
#define White                 0
#define Grey                  1
#define Black                 2

#define sf                    scanf
#define pf                    printf

#define Test_Case(a)             for(int i = 1; i <= t; i++)
#define REP(i, a, b)      for(int i=a;i<b;i++)
#define loop(i,n)       for(int i=0;i<n;i++)

#define READ                  freopen("input.txt", "r", stdin);
#define WRITE                 freopen("output.txt", "w", stdout);

bool cmp(const pii &a, const pii &b)
{
    return a.first < b.first;
}

int table[2010][2010];

int knapsack(vii store, int sz, int highest_weight)
{

    for(int i = 0; i <= sz; i++) {
        for(int w = 0; w <= highest_weight; w++) {
            if(i == 0 || w == 0)
                table[i][w] = 0;

            else if(store[i-1].first <= w) {
                table[i][w] = max(store[i-1].second + table[i-1][w - store[i-1].first], table[i-1][w]);
            }

            else
                table[i][w] = table[i-1][w];
        }
    }

    return table[sz][highest_weight];
}

int main()
{
    int highest_weight, n;

    sf("%d %d", &highest_weight, &n);

    vii store;

    for(int i = 1; i <= n; i++) {
        int weight, price;
        sf("%d %d", &weight, &price);

        store.pb(mp(weight, price));
    }

    sort(store.begin(), store.end(), cmp);

    int optimal_price = knapsack(store, store.size(), highest_weight);

    pf("%d\n", optimal_price);

    return 0;

}
