#pragma GCC optimize("O3,inline")
#include <bits/stdc++.h>
using namespace std;

#define ssize(c) static_cast<int>(c.size())

struct SegmentTree
{
    int unit = 0;
    int merge(int a, int b) { return max(a, b); }

    int n;
    vector<int> st;

    SegmentTree(const vector<int>& data)
    {
        n = 1;
        while(n < ssize(data)) n *= 2;
        st.assign(2*n, unit);
        for(int i = 0; i < ssize(data); i++) st[n + i] = data[i];
        for(int i = n-1; i > 0; i--) st[i] = merge(st[2*i], st[2*i+1]);
    }
    void set(int p, int v)
    {
        st[p += n] = v;
        for(p /= 2; p > 0; p /= 2) st[p] = merge(st[2*p], st[2*p+1]);
    }
    int query(int x, int y)
    {
        int left = unit, right = unit;
        for(x += n, y += n + 1; x < y; x /= 2, y /= 2)
        {
            if(x&1) left = merge(left, st[x++]);
            if(y&1) right = merge(st[--y], right);
        }
        return merge(left, right);
    }
    int findpref(int v) // shortest prefix s.t. query(0,x) >= v
    {
        if(st[1] < v) return -1;
        int u = 1;
        for(int pref = unit; u < n; )
        {
            u *= 2;
            if(merge(pref, st[u]) < v)
                pref = merge(pref, st[u]), u++;
        }
        return u - n;
    }
};

int main()
{
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    SegmentTree st(a);

    while(m--)
    {
        int r; cin >> r;
        int pos = st.findpref(r);

        if(pos == -1) cout << 0 << ' ';
        else
        {
            cout << pos + 1 << ' ';
            a[pos] -= r;
            st.set(pos, a[pos]);
        }
    }
    cout << endl;
}
