#include <bits/stdc++.h>
using namespace std;

vector<int> z_function(string s)
{
    int n = s.size();
    vector<int> z(n, 0);
    for(int i = 1, l = 0, r = 0; i < n; i++)
    {
        if(i <= r) z[i] = min(r-i+1, z[i-l]);
        while(i+z[i] < n && s[i+z[i]] == s[z[i]]) z[i]++;
        if(i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
    return z;
}

int main()
{
    string s;
    cin >> s;

    auto z = z_function(s);

    for(int i = 1; i < s.size(); i++)
        if(z[s.size()-i] == i)
            cout << i << ' ';
    cout << endl;
}
