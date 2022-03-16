#include <bits/stdc++.h>
using namespace std;

// Find the smallest rotation of a string, and return the position
// of its first character
int minimal_rotation(const string& t)
{
    string s = t+t;
    int n = s.size(), res = 0, j, k;
    for(int i = 0; i < n/2; )
    {
        for(res = i, j = i+1, k = i; j < n && s[k] <= s[j]; j++)
            if(s[k] < s[j]) k = i;
            else k++;
        while(i <= k) i += j-k;
    }
    return res;
}

int main()
{
    cin.tie(0)->sync_with_stdio(false);

    string s;
    cin >> s;

    rotate(s.begin(), s.begin() + minimal_rotation(s), s.end());
    cout << s << endl;
}
