#include <iostream>
#include <cmath>
using namespace std;
const long long size = 10000009;
long long ara[size];
long long ara2[size];
void seive() {

    int k, j, root;
    for(k = 2; k <= size; k++) {
        ara[k] = 1;
    }
    for(k = 2; k <= size; k++) {
        if(ara[k] == 1) {
            for(j = 2; k*j <= size; j++) {
                if(ara[k*j] == 1) ara[k*j] = k;
            }
            ara[k] = k;
            ara2[k] = ara2[k-1] + ara[k];
        }
        else {
            ara2[k] = ara2[k-1] + ara[k];
        }
    }
}

int main()
{
    int t, i;
    long long n;
    ara2[0] = 0;
    ara2[1] = 0;
    seive();
    cin >> t;
    while(t--) {
        cin >> n;
        cout << ara2[n] << endl;
    }
    return 0;
}
