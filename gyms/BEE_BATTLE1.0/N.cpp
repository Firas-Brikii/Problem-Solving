#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
using namespace std;
using namespace __gnu_pbds;
#ifndef ONLINE_JUDGE
#include "debug.cpp"
#else
#define dbg(...)
#endif
#define endl "\n"
#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL);
#define ll long long
#define pb(n) push_back(n)
#define F first
#define S second
#define mp(x, y) make_pair(x, y)
#define yes cout << "YES" << endl;
#define no cout << "NO" << endl;
#define nop cout << -1 << endl;
#define ordered_set tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update>
const ll sup = 1e18;
const ll inf = -1e18;
const ll mod = 1e9 + 7;
const int N_Max = 2e5 + 7;
const int Nax = 15;
const int LOG = 18;
const int BITS = 30;
const int ALPHA = 26;
ll gcd(ll a , ll b) {return b ? gcd(b , a % b) : a;}
ll lcm(ll a , ll b) {return (a * b) / gcd(a , b);}
ll inv(ll N) {if (N == 1) return 1; return (mod - ((mod / N) * inv(mod % N)) % mod) % mod;}


void solve(){
	int N;
	cin >> N;
	vector<vector<int>> a(N + 1, vector<int>(5));
	for (int i = 1; i <= N; i++)
		for (int j = 0; j < 5; j++) cin >> a[i][j];
	for (int d1 = 0; d1 < 5; d1++){
		for (int d2 = d1 + 1; d2 < 5; d2++){
			int cnt1 = 0, cnt2 = 0, both = 0;
			for (int i = 1; i <= N; i++){
				if (a[i][d1] == 1 && a[i][d2] == 1) both++;
				else if (a[i][d1] == 1) cnt1++;
				else if (a[i][d2] == 1) cnt2++;
			}
			int rem1 = max(0, N / 2 - cnt1), rem2 = max(0, N / 2 - cnt2);
			if (rem1 + rem2 <= both){
				cout << "YES" << endl;
				return;
			}
		}
	}
	cout << "NO" << endl;
}

int main(){
    FAST
    #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    #endif
    int tc = 1;
    cin >> tc;
    while (tc--) solve();
    return 0;
}
