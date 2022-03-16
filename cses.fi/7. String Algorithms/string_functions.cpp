#include <bits/stdc++.h>
using namespace std;

// z[0] = 0
// z[i] = length of the longest substring starting at i that is a prefix of s
// z[i] = max len s.t. s[0..len-1] == s[i..i+len-1]
vector<int> z_function(string s)
{
    int n = s.size();
    vector<int> z(n, 0);
    for(int i = 1, l = 0, r = 0; i < n; i++)
    {
        if(i <= r) z[i] = min(r-i+1, z[i-l]);
        while(i+z[i] < n && s[i+z[i]] == s[z[i]]) z[i]++;
        if(i+z[i]-1 > r) l = i, r = i + z[i] - 1;
    }
    return z;
}

// pi[0] = 0
// pi[i] = length of the longest proper suffix of [0..i] that is a prefix of s
// pi[i] = max len<i s.t. s[0..len-1] == s[i-len+1..i]
vector<int> pi_function(string s)
{
    int n = s.size();
    vector<int> pi(n, 0);
    for(int i = 1, j = 0; i < n; i++)
    {
        while(j > 0 && s[i] != s[j]) j = pi[j-1];
        if(s[i] == s[j]) pi[i] = ++j;
    }
    return pi;
}

int main()
{
    string s;
    cin >> s;

    for(int x : z_function(s)) cout << x << ' ';
    cout << endl;
    for(int x : pi_function(s)) cout << x << ' ';
    cout << endl;
}
