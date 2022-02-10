#include <bits/stdc++.h>
using namespace std;

#define ssize(c) static_cast<int>(c.size())

struct SegmentTree
{
    using Node = int;
    Node unit{1000000000}; // s.t. for every x merge(x, unit) = x
    Node merge(Node a, Node b) { return min(a, b); }

    int n_po2;
    vector<Node> st;

    SegmentTree(const vector<int>& data)
    {
        n_po2 = 1;
        while(n_po2 < ssize(data)) n_po2 *= 2;
        st.assign(2 * n_po2, unit);

        for(int i = 0; i < ssize(data); i++) st[i + n_po2] = Node{data[i]};
        for(int i = n_po2 - 1; i > 0; i--) st[i] = merge(st[2*i], st[2*i+1]);
    }
    Node query(int x, int y) // [x, y]
    {
        Node left = unit, right = unit;
        for(x += n_po2, y += n_po2 + 1; x < y; x /= 2, y /= 2)
        {
            if(x&1) left = merge(left, st[x++]);
            if(y&1) right = merge(st[--y], right);
        }
        return merge(left, right);
    }
    void update(int p, int v)
    {
        st[p += n_po2] = Node{v};
        for(p /= 2; p > 0; p /= 2) st[p] = merge(st[2*p], st[2*p+1]);
    }
};

int main()
{
    int n, q;
    cin >> n >> q;
    vector<int> x(n);
    for(int i = 0; i < n; i++) cin >> x[i];
    SegmentTree st(x);

    while(q--)
    {
        int t, a, b;
        cin >> t >> a >> b;

        if(t == 1)
        {
            st.update(a-1, b);
        }
        else
        {
            cout << st.query(a-1, b-1) << endl;
        }
    }
}
