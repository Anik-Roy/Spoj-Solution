#include <bits/stdc++.h>
using namespace std;

#define SIZE_N 3000000
#define SIZE_P 4000000
typedef long long ll;

bool status[SIZE_N/2+5]; // used to check a number is prime or not
int prime[SIZE_P];

void seive()  // by this algorithm, we can find prime upto SIZE_N
{
    for(int i = 2; i <= SIZE_N >> 1; i++) {
        status[i] = 0; // status array used to check a number is prime or not
    }

    int rt = int( sqrt((double)SIZE_N)) + 1;
    for(int i = 3; i <= rt; i += 2) {
        if(status[i>>1] == 0) {
            for(int j = i*i; j <= SIZE_N; j += i+i) {
                status[j>>1] = 1;
            }
        }
    }

    int indx = 0;
    prime[indx++] = 2;
    for(int i = 3; i <= SIZE_N; i+=2) {
        if(status[i>>1] == 0) {
            prime[indx++] = i; // prime array is used to store all prime number upto SIZE_N
        }
    }
}

ll BigMod(ll b, int p, int m)
{
    ll r = 1;
    while(p > 0) {
        if(p%2 == 1)
            r = (r*b)%m;
        p /= 2;
        b = (b*b)%m;
    }
    return r;
}

int Phi(int n, int prime_factor[])
{
    float res = (float)n;
    int rt = (int)sqrt(n), indx = 0;

    for(int i = 0; prime[i] <= rt; i++) {
        if(n % prime[i] == 0) {
            int cnt = 0;

            prime_factor[indx++] = prime[i];
            while(n % prime[i] == 0) {
                n /= prime[i];
                cnt++;
            }
            //cout << prime[i] << " " << cnt << endl;
            //res *= (1.0 - (1.0/(float)prime[i]));
            rt = sqrt(n);
        }
    }

    if(n > 1) {
        //res *= (1.0 - (1.0/(float)n));
        prime_factor[indx++] = n;
    }
    return indx;
}

int main()
{
    seive();

    long long p, n, r;

    while(scanf("%lld %lld", &p, &n))
    {
        int prime_factor[100];

        if(p == 0 && n == 0)
            break;

        int phi = p-1;

        int sz = Phi(phi, prime_factor);

        for(int i = 1; i <= n; i++)
        {
            bool flag = true;

            scanf("%lld", &r);

            for(int j = 0; j < sz; j++) {
                int d = phi / prime_factor[j];
                if(BigMod(r, d, p) == 1) {
                    flag = false;
                    break;
                }
            }

            if(flag)
                printf("YES\n");
            else
                printf("NO\n");
        }
    }

    return 0;
}

