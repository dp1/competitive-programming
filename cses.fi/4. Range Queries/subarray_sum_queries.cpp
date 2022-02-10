#include <bits/stdc++.h>
using namespace std;

#define ssize(c) static_cast<int>(c.size())
using ll = long long;

struct SegmentTree
{
    struct Node
    {
        ll sum, pref, suff, res;
        Node(int v)
        {
            sum = v;
            pref = suff = res = max(0, v);
        }
    };

    Node merge(Node a, Node b)
    {
        Node res(0);
        res.sum = a.sum + b.sum;
        res.pref = max(a.pref, a.sum + b.pref);
        res.suff = max(b.suff, b.sum + a.suff);
        res.res = max({a.res, b.res, a.suff + b.pref});
        return res;
    }

    Node unit = Node(0);

    int n;
    vector<Node> st;

    SegmentTree(const vector<int>& data)
    {
        n = 1;
        while(n < ssize(data)) n *= 2;
        st.assign(2*n, unit);
        for(int i = 0; i < ssize(data); i++) st[i+n] = Node{data[i]};
        for(int i = n-1; i > 0; i--) st[i] = merge(st[2*i], st[2*i+1]);
    }
    void update(int p, int v)
    {
        st[p += n] = Node{v};
        for(p /= 2; p > 0; p /= 2) st[p] = merge(st[2*p], st[2*p+1]);
    }
    Node query(int x, int y)
    {
        Node left = unit, right = unit;
        for(x += n, y += n + 1; x < y; x /= 2, y /= 2)
        {
            if(x&1) left = merge(left, st[x++]);
            if(y&1) right = merge(st[--y], right);
        }
        return merge(left, right);
    }
};

int main()
{
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    SegmentTree st(a);

    while(q--)
    {
        int k, x;
        cin >> k >> x;
        st.update(k-1, x);
        cout << st.query(0, n-1).res << endl;
    }
}
