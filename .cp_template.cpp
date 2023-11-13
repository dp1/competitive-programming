#pragma GCC optimize("O3,inline")
#pragma GCC target("avx2")
#include <bits/stdc++.h>
using namespace std;

#define all(c) begin(c),end(c)
#define ssize(c) static_cast<int>(c.size())

using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;  using vvi = vector<vector<int>>;
using vb = vector<bool>; using vvb = vector<vector<bool>>;
using vll = vector<ll>;  using vvll = vector<vector<ll>>;

constexpr ll INF = 1e18;

template<typename A, typename B> istream& operator>>(istream& s, pair<A,B>& p) { s >> p.first >> p.second; return s; }
template<typename A, typename B> ostream& operator<<(ostream& s, const pair<A,B>& p) { s << "(" << p.first << "," << p.second << ")"; return s; }
template<typename Iterable, typename Begin = decltype(std::begin(std::declval<Iterable>())), typename NotString = typename std::enable_if<!std::is_same<Iterable, string>::value, void>::type>
istream& operator>>(istream& s, Iterable& it) { for(auto& x : it) s >> x; return s; }
template<typename Iterable, typename Begin = decltype(std::begin(std::declval<Iterable>())), typename NotString = typename std::enable_if<!std::is_same<Iterable, string>::value, void>::type>
ostream& operator<<(ostream& s, const Iterable& it) {
    if(&s == &std::cerr) { s << "["; auto delim = ""; for(const auto& x : it) { s << delim << x; delim = ", "; } s << "]"; }
    else { auto delim = ""; for(const auto& x : it) { s << delim << x; delim = " "; } }
    return s;
}
template<typename ReverseIterator> auto to_fwd_iterator(const ReverseIterator& it) { return std::next(it).base(); }

void yesno(bool a) { cout << (a ? "YES\n" : "NO\n"); }
void possible(bool a) { cout << (a ? "Possible\n" : "Impossible\n"); }
auto micros() { return chrono::steady_clock::now().time_since_epoch() / chrono::microseconds{1}; }

// ====================================================== //

void solve() {
}

// ====================================================== //

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cout << fixed << setprecision(12);

    int T = 1;
    cin >> T;

    for(int t = 0; t < T; t++) {
        //cout << "Case #" << (t+1) << ": ";
        solve();
    }
}
