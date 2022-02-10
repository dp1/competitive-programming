#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, q;
    cin >> n >> q;
    vector<int> v(n);
    for(int i = 0; i < n; i++)
    {
        cin >> v[i];
        if(i) v[i] ^= v[i-1];
    }

    while(q--)
    {
        int a, b;
        cin >> a >> b;
        a--; b--;
        cout << (v[b] ^ (a > 0 ? v[a-1] : 0)) << endl;
    }
}
