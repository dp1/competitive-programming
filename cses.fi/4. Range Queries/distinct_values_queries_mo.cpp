#pragma GCC optimize("O3,inline")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define ssize(c) static_cast<int>(c.size())
#define all(c) c.begin(),c.end()

template<typename T>
struct CoordCompression
{
    vector<T> values;
    CoordCompression(const vector<T>& data) : values(data)
    {
        // assert(!data.empty());
        sort(all(values));
        int n = 1;
        for(int i = 1; i < ssize(values); i++)
            if(values[i] != values[i-1])
                values[n++] = values[i];
        values.resize(n);
    }
    int toindex(T v) { return lower_bound(all(values), v) - values.begin(); }
    T fromindex(int i) { return values[i]; }
    int size() { return values.size(); }
};

struct MoQuery
{
    int x, y, idx;
    static const int block_size = 450; // should be ~sqrt(MAXN)
    bool operator<(const MoQuery& rhs) const
    {
        if(x / block_size != rhs.x / block_size)
            return x / block_size < rhs.x / block_size;
        if(x / block_size & 1) return y < rhs.y;
        return y > rhs.y;
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(false);

    int n, q;
    cin >> n >> q;
    vector<int> data(n);
    for(int i = 0; i < n; i++) cin >> data[i];

    CoordCompression<int> cc(data);
    for(int& v : data) v = cc.toindex(v);

    vector<MoQuery> queries;
    for(int i = 0; i < q; i++)
    {
        int a, b;
        cin >> a >> b;
        queries.push_back(MoQuery{a-1, b-1, i});
    }

    int res = 0;
    vector<int> freq(cc.size(), 0);

    auto add = [&](int v)
    {
        if(freq[v] == 0) res++;
        freq[v]++;
    };
    auto remove = [&](int v)
    {
        freq[v]--;
        if(freq[v] == 0) res--;
    };
    auto getresult = [&]()
    {
        return res;
    };

    sort(all(queries));
    int left = 0, right = -1;
    vector<int> result(queries.size());
    for(auto& query : queries)
    {
        while(left > query.x) left--, add(data[left]);
        while(left < query.x) remove(data[left]), left++;
        while(right > query.y) remove(data[right]), right--;
        while(right < query.y) right++, add(data[right]);
        result[query.idx] = getresult();
    }

    for(int r : result)
        cout << r << '\n';
}
