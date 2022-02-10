#pragma GCC target("avx2")

#include <bits/stdc++.h>
using namespace std;

uint64_t a[1000][16];

#define get(x,y) ((a[x][y/64] >> (y & 63)) & 1)

int main()
{
    cin.tie(0)->sync_with_stdio(false);

    int n, q;
    cin >> n >> q;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            char ch; cin >> ch;
            if(ch == '*')
                a[i][j/64] |= 1LL << (j & 63);
        }
    }

    while(q--)
    {
        int t; cin >> t;
        if(t == 1)
        {
            int x, y; cin >> x >> y;
            x--; y--;
            a[x][y/64] ^= 1LL << (y & 63);
        }
        else
        {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            x1--; x2--; y1--; y2--;

            int res = 0;
            for(int i = x1; i <= x2; i++)
            {
                for(int j = y1 & ~63; j <= (y2 | 63); j += 64)
                {
                    uint64_t mask = ~0LL;
                    if(j < y1)
                        mask &= ~((1LL << (y1 - j)) - 1);
                    if(j + 63 > y2)
                        mask &= (1LL << (y2 - j + 1)) - 1;
                    res += __builtin_popcountll(a[i][j/64] & mask);
                }
            }
            cout << res << endl;
        }
    }
}
