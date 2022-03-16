#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// Resistant to birthday paradox, returns (hash,startindex) pairs
vector<pair<ll,int>> substring_hashes(const string& s, int len)
{
    if(s.size() < len) return {};
    const ll b = 26, mx = 1000000007, my = 1000000009;
    ll x = 0, y = 0, px = 1, py = 1;

    for(int i = 0; i < len; i++)
    {
        x = (x * b + s[i]) % mx;
        y = (y * b + s[i]) % my;
        px = (px * b) % mx;
        py = (py * b) % my;
    }
    vector<pair<ll,int>> res = {{(x<<32)+y, 0}};
    for(int i = len; i < s.size(); i++)
    {
        x = (x * b + s[i]) % mx;
        y = (y * b + s[i]) % my;
        x = ((x - s[i-len] * px) % mx + mx) % mx;
        y = ((y - s[i-len] * py) % my + my) % my;
        res.push_back({(x<<32)+y, i-len+1});
    }
    return res;
}
ll string_hash(const string& s) { return substring_hashes(s, s.size())[0].first; }

int main()
{
    string s, p;
    cin >> s >> p;

    int res = 0;
    auto ph = string_hash(p);
    for(auto h : substring_hashes(s, p.size()))
        if(h.first == ph)
            res++;

    cout << res << endl;
}
