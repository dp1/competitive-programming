#pragma GCC optimize("O3,inline")
#include <bits/stdc++.h>
using namespace std;

#define all(c) begin(c),end(c)
#define pb push_back
#define ssize(c) static_cast<int>(c.size())
#define rep(var,start,end) for(int var = (start); var < (end); var++)

using ll = long long;

struct Fenwick
{
    vector<int> ft;
    Fenwick(int n) { ft.assign(n+1, 0); }
    void add(int p, int v)
    {
        for(++p; p < ssize(ft); p += p&-p)
            ft[p] += v;
    }
    int query(int b)
    {
        int res = 0;
        for(++b; b > 0; b -= b&-b)
            res += ft[b];
        return res;
    }
    int query(int a, int b) { return query(b) - query(a-1); }
};

struct Query
{
    char op;
    int a, b;
};

template<typename T>
struct CoordinateCompression
{
    vector<T> values;
    CoordinateCompression(const vector<T>& data) : values(data)
    {
        // assert(!data.empty());
        sort(all(values));
        int n = 1;
        for(int i = 1; i < ssize(values); i++)
            if(values[i] != values[i-1])
                values[n++] = values[i];
        values.resize(n);
    }
    int toindex(T v) { return lower_bound(all(values), v) - values.begin(); }
    T fromindex(int i) { return values[i]; }
    int size() { return values.size(); }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    int n, q;
    cin >> n >> q;
    vector<int> p(n);
    vector<Query> queries(q);

    vector<int> values;

    for(int i = 0; i < n; i++)
    {
        cin >> p[i];
        values.pb(p[i]);
    }
    for(int i = 0; i < q; i++)
    {
        cin >> queries[i].op >> queries[i].a >> queries[i].b;
        if(queries[i].op == '?')
            values.pb(queries[i].a);
        values.pb(queries[i].b);
    }

    CoordinateCompression cc(values);
    Fenwick ft(cc.size());
    for(int x : p)
        ft.add(cc.toindex(x), 1);

    for(auto& query : queries)
    {
        if(query.op == '!')
        {
            int k = query.a - 1;
            ft.add(cc.toindex(p[k]), -1);
            p[k] = query.b;
            ft.add(cc.toindex(p[k]), 1);
        }
        else
        {
            cout << ft.query(cc.toindex(query.a), cc.toindex(query.b)) << '\n';
        }
    }
}
