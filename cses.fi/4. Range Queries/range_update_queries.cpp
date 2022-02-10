#include <bits/stdc++.h>
using namespace std;

#define ssize(c) static_cast<int>(c.size())
using ll = long long;

struct SegmentTree
{
    using Node = ll;
    Node unit = Node(0);
    Node merge(Node a, Node b) { return a + b; }

    int n;
    vector<Node> st;

    SegmentTree(const vector<int>& data)
    {
        n = 1;
        while(n < ssize(data)) n *= 2;
        st.assign(2*n, unit);
        for(int i = 0; i < ssize(data); i++) st[i+n] = Node{data[i]};
        for(int i = n - 1; i > 0; i--) st[i] = merge(st[2*i], st[2*i+1]);
    }
    void update(int u, int l, int r, int p, int v)
    {
        if(r < p || l > p) return;
        if(l == r) st[u] += v;
        else
        {
            update(2*u, l, (l+r)/2, p, v);
            update(2*u+1, (l+r)/2+1, r, p, v);
            st[u] = merge(st[2*u], st[2*u+1]);
        }
    }
    Node query(int u, int l, int r, int x, int y)
    {
        if(r < x || l > y) return unit;
        if(l >= x && r <= y) return st[u];
        return merge(
            query(2*u, l, (l+r)/2, x, y),
            query(2*u+1, (l+r)/2+1, r, x, y)
        );
    }
    void update(int p, int v) { update(1, 0, n-1, p, v); }
    Node query(int x, int y) { return query(1, 0, n-1, x, y); }
};

int main()
{
    int n, q;
    cin >> n >> q;
    vector<int> v(n);
    for(int i = 0; i < n; i++) cin >> v[i];
    SegmentTree st(vector<int>(n, 0));

    while(q--)
    {
        int t;
        cin >> t;
        if(t == 1)
        {
            int a, b, u;
            cin >> a >> b >> u;
            a--; b--;
            st.update(a, u);
            if(b + 1 < n)
                st.update(b+1, -u);
        }
        else
        {
            int k;
            cin >> k;
            k--;
            cout << v[k] + st.query(0, k) << endl;
        }
    }
}
