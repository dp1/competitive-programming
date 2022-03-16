#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct HashTree
{
    static constexpr ll mod = 1e9+7;
    struct Node
    {
        ll h, p;
        Node(char ch) { h = ch; p = 26; }
        Node() { h = 0; p = 1; }
    };

    Node unit;
    Node merge(Node& a, Node& b)
    {
        Node res;
        res.p = (a.p * b.p) % mod;
        res.h = (a.h * b.p + b.h) % mod;
        return res;
    }

    vector<Node> st;
    int n;

    HashTree(const string& data)
    {
        n = 1;
        while(n < data.size()) n *= 2;
        st.assign(2*n, unit);

        for(int i = 0; i < data.size(); i++) st[n+i] = Node{data[i]};
        for(int i = n-1; i > 0; i--) st[i] = merge(st[2*i], st[2*i+1]);
    }
    Node query(int a, int b)
    {
        Node left = unit, right = unit;
        for(a += n, b += n + 1; a < b; a /= 2, b /= 2)
        {
            if(a&1) left = merge(left, st[a++]);
            if(b&1) right = merge(st[--b], right);
        }
        return merge(left, right);
    }
    void update(int p, char v)
    {
        st[p += n] = Node{v};
        for(p /= 2; p > 0; p /= 2) st[p] = merge(st[2*p], st[2*p+1]);
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;

    HashTree h(s);
    reverse(s.begin(), s.end());
    HashTree hr(s);

    while(m--)
    {
        int t;
        cin >> t;
        if(t == 1)
        {
            int k;
            char x;
            cin >> k >> x;
            k--;
            h.update(k, x);
            hr.update(n-k-1, x);
        }
        else
        {
            int a, b;
            cin >> a >> b;
            a--; b--;

            if(h.query(a, b).h == hr.query(n-b-1, n-a-1).h)
                cout << "YES\n";
            else
                cout << "NO\n";
        }
    }
}
