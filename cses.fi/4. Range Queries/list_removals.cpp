#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;

template<typename K, typename V>
using ordered_map = tree<K, V, less<int>, rb_tree_tag, tree_order_statistics_node_update>;

int main()
{
    int n; cin >> n;
    ordered_map<int, int> mp;
    for(int i = 0; i < n; i++)
    {
        int x; cin >> x;
        mp[i] = x;
    }

    for(int i = 0; i < n; i++)
    {
        int p; cin >> p; p--;
        auto it = mp.find_by_order(p);
        cout << it->second << ' ';
        mp.erase(it);
    }
    cout << endl;
}
