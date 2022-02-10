#include <bits/stdc++.h>
using namespace std;

#define ssize(c) static_cast<int>(c.size())
using ll = long long;

struct LazySegmentTree
{
    using Node = ll;
    struct Update
    {
        ll add = 0, set = 0;
        Update(ll a, ll s) { add = a; set = s; }
    };

    Node unit = Node(0); // s.t. for every x merge(x, unit) = x
    Update no_update = Update(0,0);

    Node merge(Node a, Node b) { return a + b; }
    void update_node(Node& a, Update upd, int k) // k - size of this node's interval
    {
        if(upd.set != 0) a = k * upd.set;
        else a += k * upd.add;
    }
    Update combine_updates(Update prev, Update upd, int k)
    {
        Update res(0,0);
        if(upd.set != 0) res.set = upd.set;
        else if(prev.set != 0) res.set = prev.set + upd.add;
        else res.add = prev.add + upd.add;
        return res;
    }

    int n, h;
    vector<Node> st;
    vector<Update> lz;

    LazySegmentTree(const vector<int>& data)
    {
        n = 1;
        h = 1;
        while(n < ssize(data)) n *= 2, h++;
        st.assign(2 * n, unit);
        lz.assign(n, no_update);
        for(int i = 0; i < ssize(data); i++) st[i + n] = Node{data[i]};
        for(int i = n-1; i > 0; i--) st[i] = merge(st[2*i], st[2*i+1]);
    }
    void apply(int u, Update upd, int k)
    {
        update_node(st[u], upd, k);
        if(u < n)
            lz[u] = combine_updates(lz[u], upd, k);
    }
    void push(int u)
    {
        u += n;
        int k = 1 << (h-2);
        for(int s = h-1; s > 0; --s, k /= 2)
        {
            int i = u >> s;
            apply(2*i, lz[i], k);
            apply(2*i+1, lz[i], k);
            lz[i] = no_update;
        }
    }
    void pull(int u)
    {
        u += n;
        int k = 2;
        for(u /= 2; u > 0; u /= 2, k *= 2)
        {
            st[u] = merge(st[2*u], st[2*u+1]);
            update_node(st[u], lz[u], k);
        }
    }
    Node query(int x, int y) // [x, y]
    {
        push(x); push(y);
        Node left = unit, right = unit;
        for(x += n, y += n + 1; x < y; x /= 2, y /= 2)
        {
            if(x&1) left = merge(left, st[x++]);
            if(y&1) right = merge(st[--y], right);
        }
        return merge(left, right);
    }
    void update(int x, int y, Update val) // [x, y]
    {
        push(x); push(y);
        int x0 = x, y0 = y, k = 1;
        for(x += n, y += n + 1; x < y; x /= 2, y /= 2, k *= 2)
        {
            if(x&1) apply(x++, val, k);
            if(y&1) apply(--y, val, k);
        }
        pull(x0); pull(y0);
    }
};

int main()
{
    int n, q;
    cin >> n >> q;
    vector<int> arr(n);
    for(int i = 0; i < n; i++) cin >> arr[i];
    LazySegmentTree st(arr);

    while(q--)
    {
        int t, a, b, x;
        cin >> t >> a >> b;
        a--; b--;

        if(t == 1)
        {
            cin >> x;
            st.update(a, b, LazySegmentTree::Update(x, 0));
        }
        else if(t == 2)
        {
            cin >> x;
            st.update(a, b, LazySegmentTree::Update(0, x));
        }
        else
        {
            cout << st.query(a, b) << endl;
        }
    }
}
