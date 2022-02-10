#pragma GCC optimize("O3,inline")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define ssize(c) static_cast<int>(c.size())
#define all(c) c.begin(),c.end()

struct SegmentTree
{
    struct Node
    {
        vector<ll> data, prefsum;
        ll cost = 0;
        Node(int v)
        {
            data.push_back(v);
            prefsum.push_back(v);
            cost = 0;
        }
        Node() { cost = 0; }
    };
    Node unit = Node(); // s.t. for every x merge(x, unit) = x
    Node merge(Node a, Node b)
    {
        Node res;
        res.data.assign(all(a.data));
        res.data.insert(res.data.end(), all(b.data));
        res.cost = a.cost + b.cost;

        res.prefsum.assign(all(res.data));
        for(int i = 1; i < ssize(res.data); i++)
        {
            if(res.data[i] < res.data[i-1])
            {
                res.cost += res.data[i-1] - res.data[i];
                res.data[i] = res.data[i-1];
            }

            res.prefsum[i] = res.prefsum[i-1] + res.data[i];
        }
        return res;
    }

    int n;
    vector<Node> st;

    SegmentTree(const vector<int>& data) // O(NlogN)
    {
        n = 1;
        while(n < ssize(data)) n *= 2;
        st.assign(2*n, unit);
        for(int i = 0; i < ssize(data); i++) st[i+n] = Node{data[i]};
        for(int i = n-1; i > 0; i--) st[i] = merge(st[2*i], st[2*i+1]);
    }
    ll query(int x, int y) // [x, y], O(log^2N)
    {
        vector<int> left, right;
        for(x += n, y += n + 1; x < y; x /= 2, y /= 2)
        {
            if(x&1) left.push_back(x++);
            if(y&1) right.push_back(--y);
        }

        ll res = 0, highest = 0;
        auto merge_result = [&](int u)
        {
            int lo = 0, hi = st[u].data.size() - 1;
            while(lo < hi)
            {
                int mid = (lo + hi + 1) / 2;
                if(st[u].data[mid] < highest) lo = mid;
                else hi = mid - 1;
            }

            res += st[u].cost;
            if(st[u].data[lo] < highest)
                res += highest * (lo+1) - st[u].prefsum[lo];

            highest = max(highest, st[u].data.back());
        };

        for(int i = 0; i < ssize(left); i++) merge_result(left[i]);
        for(int i = right.size()-1; i >= 0; i--) merge_result(right[i]);
        return res;
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(false);

    int n, q;
    cin >> n >> q;
    vector<int> x(n);
    for(int i = 0; i < n; i++) cin >> x[i];
    SegmentTree st(x);

    while(q--)
    {
        int a, b;
        cin >> a >> b;
        a--; b--;
        cout << st.query(a, b) << '\n';
    }
}
