#include <bits/stdc++.h>
using namespace std;

#define ssize(x) static_cast<int>(x.size())
#define rep(var,start,end) for(int var = (start); var < (end); var++)
using ll = long long;

struct Fenwick
{
    vector<ll> ft;
    template<typename T> Fenwick(vector<T>& data)
    {
        ft.push_back(0);
        ft.insert(ft.end(), data.begin(), data.end());
        for(int i = 1, j = 2; i < ssize(ft); ++i, j = i+(i&-i))
            if(j < ssize(ft))
                ft[j] += ft[i];
    }
    void add(int p, int v)
    {
        for(++p; p < ssize(ft); p += p&-p)
            ft[p] += v;
    }
    ll query(int b)
    {
        ll res = 0;
        for(++b; b > 0; b -= b&-b)
            res += ft[b];
        return res;
    }
    ll query(int a, int b)
    {
        return query(b) - query(a-1);
    }
    void set(int p, int v)
    {
        add(p, v - query(p, p));
    }
};

int main()
{
    int n, q;
    cin >> n >> q;
    vector<int> v(n);
    rep(i, 0, n) cin >> v[i];
    Fenwick ft(v);

    while(q--)
    {
        int t, a, b;
        cin >> t >> a >> b;
        if(t == 1)
            ft.set(a-1, b);
        else
            cout << ft.query(a-1, b-1) << endl;
    }
}
