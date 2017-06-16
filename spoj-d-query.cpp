#include <bits/stdc++.h>
using namespace std;

int BLOCK_SIZE;
int ara[30010], cnt[1000010], answers[200010];
int ans = 0;

pair < pair <int, int>, int > queries[200010];

inline bool mo_cmp(const pair < pair <int, int>, int > &x, const pair < pair <int, int>, int > &y)
{
    int block_x = x.first.first / BLOCK_SIZE;
    int block_y = y.first.first / BLOCK_SIZE;

    if(block_x != block_y)
        return block_x < block_y;
    else
        return x.first.second < y.first.second;
}

void add(int x)
{
    cnt[x]++;
    if(cnt[x] == 1)
        ans++;
}

void remove(int x)
{
    if(cnt[x] == 1)
        ans--;
    cnt[x]--;
}

int main()
{
    int n;
    scanf("%d", &n);

    BLOCK_SIZE = static_cast<int> (sqrt(n));

    for(int i = 0; i < n; i++)
        scanf("%d", &ara[i]);

    int q;
    scanf("%d", &q);

    for(int i = 0; i < q; i++)
    {
        scanf("%d %d", &queries[i].first.first, &queries[i].first.second);
        queries[i].second = i;
    }

    sort(queries, queries+q, mo_cmp);

    int mo_left = 0, mo_right = 0;

    for(int i = 0; i < q; i++)
    {
        int left = queries[i].first.first-1, right = queries[i].first.second-1;

        while(mo_right <= right)
        {
            add(ara[mo_right]);
            mo_right++;
        }

        while(mo_right > right+1)
        {
            remove(ara[mo_right-1]);
            mo_right--;
        }

        while(mo_left < left)
        {
            remove(ara[mo_left]);
            mo_left++;
        }

        while(mo_left > left)
        {
            add(ara[mo_left-1]);
            mo_left--;
        }
        answers[queries[i].second] = ans;
    }

    for(int i = 0; i < q; i++)
        printf("%d\n", answers[i]);

    return 0;
}
