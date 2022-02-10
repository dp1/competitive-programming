#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main()
{
    int n, q;
    cin >> n >> q;
    vector<ll> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];;
    partial_sum(a.begin(), a.end(), a.begin());

    while(q--)
    {
        int x, y;
        cin >> x >> y;
        x--; y--;
        ll res = a[y];
        if(x) res -= a[x-1];
        cout << res << endl;
    }
}
