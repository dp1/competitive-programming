#include <bits/stdc++.h>
using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(false);

    int n, q;
    cin >> n >> q;
    vector<vector<int>> a(n, vector<int>(n, 0));

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            char ch; cin >> ch;
            if(ch == '*')
                a[i][j] = 1;
        }
    }

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(i > 0) a[i][j] += a[i-1][j];
            if(j > 0) a[i][j] += a[i][j-1];
            if(i > 0 && j > 0) a[i][j] -= a[i-1][j-1];
        }
    }

    while(q--)
    {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        x1--; x2--; y1--; y2--;

        int res = a[x2][y2];
        if(x1 > 0) res -= a[x1-1][y2];
        if(y1 > 0) res -= a[x2][y1-1];
        if(x1 > 0 && y1 > 0) res += a[x1-1][y1-1];

        cout << res << endl;
    }
}
