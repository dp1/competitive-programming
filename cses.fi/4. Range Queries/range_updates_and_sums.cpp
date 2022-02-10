#include <bits/stdc++.h>
using namespace std;

#define ssize(c) static_cast<int>(c.size())
using ll = long long;

struct LazyST
{
    using Node = ll;
    struct Update
    {
        ll add, set;
        Update(ll a, ll s) { add = a; set = s; }
        bool operator!=(const Update& other)
        {
            return add != other.add || set != other.set;
        }
    };

    Node unit = Node(0);
    Update no_update = Update(0,0);

    Node merge(Node a, Node b) { return a + b; }
    void update_node(Node& a, Update upd, int l, int r)
    {
        if(upd.add) a += upd.add * (r - l + 1);
        if(upd.set) a = upd.set * (r - l + 1);
    }
    Update combine_updates(Update prev, Update upd)
    {
        Update res(0,0);
        if(prev.set != 0)
        {
            if(upd.set != 0) res.set = upd.set;
            else res.set = prev.set + upd.add;
        }
        else
        {
            if(upd.set != 0) res.set = upd.set;
            else res.add = prev.add + upd.add;
        }
        return res;
    }

    int n;
    vector<Node> st;
    vector<Update> lz;

    LazyST(const vector<int>& data)
    {
        n = 1;
        while(n < ssize(data)) n *= 2;
        st.assign(2*n, unit);
        lz.assign(n, no_update);

        for(int i = 0; i < ssize(data); i++) st[i+n] = Node{data[i]};
        for(int i = n-1; i > 0; i--) st[i] = merge(st[2*i], st[2*i+1]);
    }

    void push(int u, int l, int r)
    {
        if(u >= n) return;
        if(lz[u] != no_update)
        {
            update_node(st[2*u], lz[u], l, (l+r)/2);
            update_node(st[2*u+1], lz[u], (l+r)/2+1, r);
            if(2*u < n)
            {
                lz[2*u] = combine_updates(lz[2*u], lz[u]);
                lz[2*u+1] = combine_updates(lz[2*u+1], lz[u]);
            }
            lz[u] = no_update;
        }
    }

    Node query(int u, int l, int r, int x, int y)
    {
        if(r < x || l > y) return unit;
        if(l >= x && r <= y) return st[u];
        push(u, l, r);
        return merge(
            query(2*u, l, (l+r)/2, x, y),
            query(2*u+1, (l+r)/2+1, r, x, y)
        );
    }
    void update(int u, int l, int r, int x, int y, Update v)
    {
        if(r < x || l > y) return;
        if(l >= x && r <= y)
        {
            update_node(st[u], v, l, r);
            if(u < n)
                lz[u] = combine_updates(lz[u], v);
        }
        else
        {
            push(u, l, r);
            update(2*u, l, (l+r)/2, x, y, v);
            update(2*u+1, (l+r)/2+1, r, x, y, v);
            st[u] = merge(st[2*u], st[2*u+1]);
            update_node(st[u], lz[u], l, r);
        }
    }
    Node query(int x, int y) { return query(1, 0, n-1, x, y); }
    void update(int x, int y, Update v) { return update(1, 0, n-1, x, y, v); }
};

int main()
{
    int n, q;
    cin >> n >> q;
    vector<int> v(n);
    for(int i = 0; i < n; i++) cin >> v[i];

    LazyST st(v);

    while(q--)
    {
        int t, a, b, x;
        cin >> t >> a >> b;
        a--; b--;

        if(t == 1)
        {
            cin >> x;
            st.update(a, b, LazyST::Update(x, 0));
        }
        else if(t == 2)
        {
            cin >> x;
            st.update(a, b, LazyST::Update(0, x));
        }
        else
            cout << st.query(a, b) << endl;
    }
}
