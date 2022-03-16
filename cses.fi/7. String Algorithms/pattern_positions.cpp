#include <bits/stdc++.h>
using namespace std;

struct SuffixArray
{
    vector<int> sa, rank, lcp;
    SuffixArray(const string& s)
    {
        int n = s.size() + 1, cl = 256;
        vector<int> c(n), cn(n), pn(n), cnt(max(n,cl));
        iota(pn.begin(), pn.end(), 0);
        sa = rank = c;
        for(int i = 0; i < n-1; i++) c[i] = s[i];

        for(int k = 0; k <= n; k = k ? 2*k : 1)
        {
            if(k) for(int i = 0; i < n; i++) pn[i] = (sa[i]-k+n)%n;
            for(int i = 0; i < cl; i++) cnt[i] = 0;
            for(int i = 0; i < n; i++) cnt[c[pn[i]]]++;
            for(int i = 1; i < cl; i++) cnt[i] += cnt[i-1];
            for(int i = n-1; i >= 0; i--) sa[--cnt[c[pn[i]]]] = pn[i];

            cn[sa[0]] = 0; cl = 1;
            for(int i = 1; i < n; i++)
            {
                if(c[sa[i]] != c[sa[i-1]] || c[(sa[i]+k)%n] != c[(sa[i-1]+k)%n])
                    cl++;
                cn[sa[i]] = cl - 1;
            }
            if(cl == n) break;
            c.swap(cn);
        }
        lcp.assign(n-1, 0);
        for(int i = 0; i < n; i++) rank[sa[i]] = i;
        for(int i = 0, k = 0; i < n-1; i++, k = max(0, k-1))
        {
            int j = sa[rank[i]-1];
            while(s[i+k] == s[j+k]) k++;
            lcp[rank[i]-1] = k;
        }
    }
};

struct SparseTable
{
    int op(int a, int b) { return min(a, b); }

    vector<vector<int>> tab;
    SparseTable(const vector<int>& data)
    {
        tab.push_back(vector<int>(data));
        for(int p = 0; (2<<p) <= data.size(); ++p)
        {
            tab.emplace_back(data.size() - (2<<p) + 1, 0);
            for(int i = 0; i + (2<<p) <= data.size(); i++)
                tab[p+1][i] = op(tab[p][i], tab[p][i + (1<<p)]);
        }
    }
    int query(int a, int b) // [a, b]
    {
        // assert(a <= b);
        int p = __builtin_clz(1) - __builtin_clz(b-a+1);
        return op(tab[p][a], tab[p][b - (1<<p) + 1]);
    }
};

int main()
{
    string s;
    cin >> s;
    int k;
    cin >> k;

    auto sa = SuffixArray(s);
    SparseTable st(sa.sa);

    while(k--)
    {
        string t;
        cin >> t;

        int lo = 1, hi = sa.sa.size();
        while(lo < hi)
        {
            int mid = (lo+hi) / 2;
            if(s.substr(sa.sa[mid], t.size()) > t) hi = mid;
            else lo = mid + 1;
        }
        int ub = lo;
        lo = 1, hi = sa.sa.size() - 1;
        while(lo < hi)
        {
            int mid = (lo+hi) / 2;
            if(s.substr(sa.sa[mid], t.size()) >= t) hi = mid;
            else lo = mid + 1;
        }

        if(lo < ub)
            cout << st.query(lo, ub-1) + 1 << '\n';
        else
            cout << "-1\n";
    }
}
