// #pragma GCC target("avx2")

#include <bits/stdc++.h>
using namespace std;

#define ssize(c) static_cast<int>(c.size())

struct Fenwick2D
{
    vector<vector<int>> ft;
    Fenwick2D(int n, int m)
    {
        ft.assign(n+1, vector<int>(m+1, 0));
    }
    void update(int x, int y, int v)
    {
        for(++x; x < ssize(ft); x += x&-x)
            for(int j = y+1; j < ssize(ft[0]); j += j&-j)
                ft[x][j] += v;
    }
    int query(int x, int y)
    {
        int res = 0;
        for(++x; x > 0; x -= x&-x)
            for(int j = y+1; j > 0; j -= j&-j)
                res += ft[x][j];
        return res;
    }
    int query(int x1, int y1, int x2, int y2)
    {
        return query(x2, y2) - query(x1-1, y2) - query(x2, y1-1) + query(x1-1, y1-1);
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(false);

    int n, q;
    cin >> n >> q;
    Fenwick2D ft(n, n);

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            char ch; cin >> ch;
            if(ch == '*')
                ft.update(i, j, 1);
        }
    }

    while(q--)
    {
        int t; cin >> t;
        if(t == 1)
        {
            int x, y; cin >> x >> y;
            x--; y--;

            auto v = ft.query(x, y, x, y);
            if(v)
                ft.update(x, y, -1);
            else
                ft.update(x, y, 1);
        }
        else
        {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            x1--; x2--; y1--; y2--;
            cout << ft.query(x1, y1, x2, y2) << endl;
        }
    }
}
