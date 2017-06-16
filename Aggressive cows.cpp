#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int n, c;
ll ara[100010];

bool F(int x)
{
    int cowTaken = 1;
    ll curPos = ara[0];

    for(int i = 1; i < n; i++)
    {
        if(ara[i] - curPos >= x)
        {
            cowTaken++;
            curPos = ara[i];

            if(cowTaken == c)
                return true;
        }
    }

    return false;
}

int main()
{
    int t;
    scanf("%d", &t);

    while(t--)
    {
        memset(ara, 0, sizeof(ara));

        scanf("%d %d", &n, &c);

        for(int i = 0; i < n; i++)
            scanf("%lld", &ara[i]);

        sort(ara, ara+n);

        int beg = 0, end_ = ara[n-1]-ara[0]+1, mid;

        while(end_ - beg > 1)
        {
            mid = (beg+end_) >> 1;

            (F(mid)? beg : end_) = mid;
        }

        printf("%lld\n", beg);
    }
    return 0;
}
