#include <bits/stdc++.h>
using namespace std;

const int maxi = 50010;

struct node {
    bool endmark;
    node* next[60+1];
    int cnt = 0;

    node() {
        endmark = false;

        for(int i = 0; i < 60; i++)
            next[i] = NULL;
    }
} * root;

int tot = 0;

void insert(char str[], int len)
{
    node *cur = root;

    for(int i = 0; i < len; i++) {
        int id = str[i] - 'A';
        if(cur->next[id] == NULL)
            cur->next[id] = new node(), tot++;
        cur = cur->next[id];
    }

    cur->endmark = true;
}

void del(node* cur)
{
    for(int i = 0; i < 60; i++) {
        if(cur->next[i])
            del(cur->next[i]);
    }

    delete (cur);
}

unsigned char mask[] = { 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 };
#define tget(i) ( (t[(i)/8]&mask[(i)%8]) ? 1 : 0 )
#define tset(i, b) t[(i)/8]=(b) ? (mask[(i)%8]|t[(i)/8]) : ((~mask[(i)%8])&t[(i)/8])
#define chr(i) (cs==sizeof(int)?((int*)s)[i]:((unsigned char *)s)[i])
#define isLMS(i) (i>0 && tget(i) && !tget(i-1))

void getBuckets(unsigned char *s, int *bkt, int n, int K, int cs, bool end) {
    int i, sum = 0;
    for (i = 0; i <= K; i++)
        bkt[i] = 0;
    for (i = 0; i < n; i++)
        bkt[chr(i)]++;
    for (i = 0; i <= K; i++) {
        sum += bkt[i];
        bkt[i] = end ? sum : sum - bkt[i];
    }
}

void induceSAl(unsigned char *t, int *SA, unsigned char *s, int *bkt, int n, int K, int cs, bool end) {
    int i, j;
    getBuckets(s, bkt, n, K, cs, end);
    for (i = 0; i < n; i++) {
        j = SA[i] - 1;
        if (j >= 0 && !tget(j))
            SA[bkt[chr(j)]++] = j;
    }
}

void induceSAs(unsigned char *t, int *SA, unsigned char *s, int *bkt, int n, int K, int cs, bool end) {
    int i, j;
    getBuckets(s, bkt, n, K, cs, end);
    for (i = n - 1; i >= 0; i--) {
        j = SA[i] - 1;
        if (j >= 0 && tget(j))
            SA[--bkt[chr(j)]] = j;
    }
}

void SA_IS(unsigned char *s, int *SA, int n, int K, int cs) {
    int i, j;
    unsigned char *t = (unsigned char *) malloc(n / 8 + 1);
    tset(n-2, 0);
    tset(n-1, 1);
    for (i = n - 3; i >= 0; i--)
        tset(i, (chr(i)<chr(i+1) || (chr(i)==chr(i+1) && tget(i+1)==1))?1:0);

    int *bkt = (int *) malloc(sizeof(int) * (K + 1));
    getBuckets(s, bkt, n, K, cs, true);
    for (i = 0; i < n; i++)
        SA[i] = -1;
    for (i = 1; i < n; i++)
        if (isLMS(i))
            SA[--bkt[chr(i)]] = i;
    induceSAl(t, SA, s, bkt, n, K, cs, false);
    induceSAs(t, SA, s, bkt, n, K, cs, true);
    free(bkt);

    int n1 = 0;
    for (i = 0; i < n; i++)
        if (isLMS(SA[i]))
            SA[n1++] = SA[i];
    for (i = n1; i < n; i++)
        SA[i] = -1;
    int name = 0, prev = -1;
    for (i = 0; i < n1; i++) {
        int pos = SA[i];
        bool diff = false;
        for (int d = 0; d < n; d++)
            if (prev == -1 || chr(pos+d) != chr(prev+d) || tget(pos+d) != tget(prev+d)) {
                diff = true;
                break;
            } else if (d > 0 && (isLMS(pos+d) || isLMS(prev+d)))
                break;
        if (diff) {
            name++;
            prev = pos;
        }
        pos = (pos % 2 == 0) ? pos / 2 : (pos - 1) / 2;
        SA[n1 + pos] = name - 1;
    }
    for (i = n - 1, j = n - 1; i >= n1; i--)
        if (SA[i] >= 0)
            SA[j--] = SA[i];

    int *SA1 = SA, *s1 = SA + n - n1;
    if (name < n1)
        SA_IS((unsigned char*) s1, SA1, n1, name - 1, sizeof(int));
    else
        for (i = 0; i < n1; i++)
            SA1[s1[i]] = i;
    bkt = (int *) malloc(sizeof(int) * (K + 1));

    getBuckets(s, bkt, n, K, cs, true);
    for (i = 1, j = 0; i < n; i++)
        if (isLMS(i))
            s1[j++] = i;
    for (i = 0; i < n1; i++)
        SA1[i] = s1[SA1[i]];
    for (i = n1; i < n; i++)
        SA[i] = -1;
    for (i = n1 - 1; i >= 0; i--) {
        j = SA[i];
        SA[i] = -1;
        SA[--bkt[chr(j)]] = j;
    }
    induceSAl(t, SA, s, bkt, n, K, cs, false);
    induceSAs(t, SA, s, bkt, n, K, cs, true);
    free(bkt);
    free(t);
}

const int maxn = 200000;
int sa[maxn];
int lcp[maxn];
int rank_[maxn];
unsigned char *s;
int n;

void calc_lcp() {
    for (int i = 0; i < n; i++)
        rank_[sa[i]] = i;
    for (int i = 0, h = 0; i < n; i++) {
        if (rank_[i] < n - 1) {
            for (int j = sa[rank_[i] + 1]; s[i + h] == s[j + h]; ++h)
                ;
            lcp[rank_[i]] = h;
            if (h > 0)
                --h;
        }
    }
}


int main()
{
    int t;
    scanf("%d", &t);
    getchar();

    while(t--)
    {
        root = new node();

        memset(rank_, 0, sizeof(rank_));
        memset(sa, 0, sizeof(sa));
        memset(lcp, 0, sizeof(lcp));

        char input[50010];
        scanf("%s", input);
        n = strlen(input);

        s = (unsigned char*) input;

        SA_IS(s, sa, n + 1, 256, 1);
        calc_lcp();

        for( int i = 0; i <= n; i++ )
        {
            insert(input + sa[i], strlen(input + sa[i]));
        }

        printf("%d\n", tot);

        tot = 0;

        del(root);
    }

    return 0;
}
