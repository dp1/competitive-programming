#pragma GCC optimize("O3,inline")
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define all(c) begin(c),end(c)
#define ssize(c) static_cast<int>(c.size())
#define rep(var,start,end) for(int var = (start); var < (end); var++)

using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vb = vector<bool>;
using vll = vector<long long>;
using vvi = vector<vector<int>>;

template<typename A, typename B> istream& operator>>(istream& s, pair<A,B>& p) { s >> p.first >> p.second; return s; }
template<typename A, typename B> ostream& operator<<(ostream& s, const pair<A,B>& p) { s << "(" << p.first << "," << p.second << ")"; return s; }
template<typename Iterable, typename Begin = decltype(std::begin(std::declval<Iterable>())), typename NotString = typename std::enable_if<!std::is_same<Iterable, string>::value, void>::type>
istream& operator>>(istream& s, Iterable& it) { for(auto& x : it) s >> x; return s; }
template<typename Iterable, typename Begin = decltype(std::begin(std::declval<Iterable>())), typename NotString = typename std::enable_if<!std::is_same<Iterable, string>::value, void>::type>
ostream& operator<<(ostream& s, const Iterable& it)
{
    if(&s == &std::cerr) { s << "["; auto delim = ""; for(const auto& x : it) { s << delim << x; delim = ", "; } s << "]"; }
    else { auto delim = ""; for(const auto& x : it) { s << delim << x; delim = " "; } }
    return s;
}

void yesno(bool a) { cout << (a ? "YES\n" : "NO\n"); }
auto micros() { return chrono::steady_clock::now().time_since_epoch() / chrono::microseconds{1}; }

// ====================================================== //

void solve()
{
}

// ====================================================== //

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int T = 1;
    cin >> T;

    for(int t = 0; t < T; t++)
    {
        //cout << "Case #" << (t+1) << ": ";
        solve();
    }
}
