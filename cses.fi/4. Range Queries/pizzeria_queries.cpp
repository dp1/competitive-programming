#include <bits/stdc++.h>
using namespace std;

#define ssize(c) static_cast<int>(c.size())

struct SegmentTree
{
    using Node = int;
    Node unit = Node(1000000000);
    Node merge(Node a, Node b) { return min(a, b); }

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
        st[p += n] = v;
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

    for(int i = 0; i < n; i++) a[i] += i;
    SegmentTree first(a);
    for(int i = 0; i < n; i++) a[i] -= 2*i;
    SegmentTree second(a);

    while(q--)
    {
        int t, k, x;
        cin >> t >> k;
        k--;
        if(t == 1)
        {
            cin >> x;
            first.update(k, x + k);
            second.update(k, x - k);
        }
        else
        {
            cout << min(first.query(k, n-1) - k, second.query(0, k) + k) << endl;
        }
    }
}
