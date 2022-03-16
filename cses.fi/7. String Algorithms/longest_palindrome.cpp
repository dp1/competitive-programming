#include <bits/stdc++.h>
using namespace std;

// Returns, for each index, the radius of the longest palindrome
// centered there. For even lengths, the center is the left one of the two.
// p[0][i] -> palindrome is s[i-p[0][i]   ... i+p[0][i]], odd length
// p[1][i] -> palindrome is s[i-p[1][i]+1 ... i+p[1][i]], even length
//
// If needed, define handle_pal and uncomment the lines where it's called.
// It will be called O(N) times on a palindrome [a,b]. It will be called
// on all the distinct palindromes, but potentially more than once with an
// identical string (at different indices) for palindromes that repeat.
// It will not be called on each palindromic substring, that would be quadratic.
array<vector<int>,2> manacher(const string& s)
{
    int n = s.size();
    array<vector<int>,2> p = {vector<int>(n), vector<int>(n)};
    for(int k = 0; k < 2; k++)
    for(int i = 0, l = 0, r = -1; i < n; i++)
    {
        if(i+k <= r) p[k][i] = min(p[k][l+r-i-k], r - i);
        int a = i-p[k][i]-1+k, b = i+p[k][i]+1;
        // if(!k && !p[k][i]) handle_pal(i,i);
        while(a >= 0 && b < n && s[a] == s[b])
        {
            // handle_pal(a,b);
            p[k][i]++, a--, b++;
        }
        if(b-1 > r) l = a+1, r = b-1;
    }
    return p;
}

// int main()
// {
//     string s; cin >> s;

//     auto p = manacher(s);
//     int odd = max_element(p[0].begin(), p[0].end()) - p[0].begin();
//     int even = max_element(p[1].begin(), p[1].end()) - p[1].begin();

//     if(p[0][odd] * 2 + 1 > p[1][even] * 2)
//         cout << s.substr(odd - p[0][odd], p[0][odd] * 2 + 1) << endl;
//     else
//         cout << s.substr(even - p[1][even] + 1, p[1][even] * 2) << endl;
// }

int main()
{
    string s; cin >> s;

    int start = 0, len = 0;
    auto handle_pal = [&](int a, int b)
    {
        if(b-a+1 > len)
        {
            len = b-a+1;
            start = a;
        }
    };

    int n = s.size();
    array<vector<int>,2> p = {vector<int>(n), vector<int>(n)};
    for(int k = 0; k < 2; k++)
    for(int i = 0, l = 0, r = -1; i < n; i++)
    {
        if(i+k <= r) p[k][i] = min(p[k][l+r-i-k], r - i);
        int a = i-p[k][i]-1+k, b = i+p[k][i]+1;
        if(!k && !p[k][i]) handle_pal(i,i);
        while(a >= 0 && b < n && s[a] == s[b])
        {
            handle_pal(a,b);
            p[k][i]++, a--, b++;
        }
        if(b-1 > r) l = a+1, r = b-1;
    }

    cout << s.substr(start, len) << endl;
}
