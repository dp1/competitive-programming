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

int check(string& s, int len)
{
    auto vals = substring_hashes(s, len);
    sort(vals.begin(), vals.end());
    for(int i = 0; i < vals.size() - 1; i++)
        if(vals[i].first == vals[i+1].first)
            return vals[i].second;
    return -1;
}

int main()
{
    string s;
    cin >> s;

    int lo = 1, hi = s.size();
    while(lo < hi)
    {
        int mid = (lo+hi+1)/2;
        if(check(s, mid) != -1) lo = mid;
        else hi = mid-1;
    }

    int pos = check(s, lo);
    if(pos == -1) cout << -1 << endl;
    else cout << s.substr(pos, lo) << endl;
}
