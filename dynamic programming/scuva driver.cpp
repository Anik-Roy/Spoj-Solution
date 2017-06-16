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
#define inf                   1e9
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

int table[1010][22][80];
int Ox[1010], Ny[1010], Wi[1010];

int knapsack(int numOfCylinder, int O, int N)
{
    for(int cy = 0; cy <= numOfCylinder; cy++)
    {
        for(int o = 0; o <= O; o++)
        {
            for(int n = 0; n <= N; n++)
            {
                if(cy == 0)
                {
                    table[cy][o][n] = inf;

                    if(o == 0 && n == 0)
                        table[cy][o][n] = 0;
                }

                else
                {
                    table[cy][o][n] = min(table[cy-1][o][n], Wi[cy] + table[cy-1][max(0, o - Ox[cy])][max(0, n - Ny[cy])]);
                }
            }
        }
    }

    return table[numOfCylinder][O][N];
}

int main()
{
    int t;
    sf("%d", &t);

    while(t--)
    {
        clr(Ox);
        clr(Ny);
        clr(Wi);
        clr(table);

        int O, N, numOfCylinder;
        sf("%d %d %d", &O, &N, &numOfCylinder);

        for(int i = 1; i <= numOfCylinder; i++)
            cin >> Ox[i] >> Ny[i] >> Wi[i];

        int miniNumOfCylinder = knapsack(numOfCylinder, O, N);

        pf("%d\n", miniNumOfCylinder);
    }

    return 0;

}
