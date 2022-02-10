#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define ssize(c) static_cast<int>(c.size())

struct SparseTable
{
    vector<vector<int>> tab;
    SparseTable(const vector<int>& data)
    {
        tab.push_back(vector<int>(data));
        for(int p = 0; (2<<p) <= ssize(data); ++p)
        {
            tab.push_back(vector<int>(data.size() - (2<<p) + 1, 0));
            for(int i = 0; i + (2<<p) <= ssize(data); i++)
                tab[p+1][i] = min(tab[p][i], tab[p][i + (1<<p)]);
        }
    }
    int query(int a, int b) // [a, b]
    {
        int p = sizeof(int) * 8 - __builtin_clz(b-a+1) - 1;
        return min(tab[p][a], tab[p][b - (1<<p) + 1]);
    }
};

int main()
{
    int n, q;
    cin >> n >> q;
    vector<int> v(n);
    for(int i = 0; i < n ; i++) cin >> v[i];
    SparseTable st(v);

    while(q--)
    {
        int a, b;
        cin >> a >> b;
        cout << st.query(a-1, b-1) << endl;
    }
}
