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
const int N_Max = 1e6 + 7;
const int Nax = 15;
const int LOG = 18;
const int BITS = 30;
const int ALPHA = 26;
ll gcd(ll a , ll b) {return b ? gcd(b , a % b) : a;}
ll lcm(ll a , ll b) {return (a * b) / gcd(a , b);}
ll inv(ll N) {if (N == 1) return 1; return (mod - ((mod / N) * inv(mod % N)) % mod) % mod;}

int N, a, b, K;
int occ[N_Max];
int vis[N_Max];
vector<int> vec;

int work(){
	int sz = (int)vec.size() - 1;
	vector<vector<int>> dp(sz + 1);
	dp[1].resize(occ[vec[1]] + 1);
	int ret = 0;
	for (int i = 2; i <= sz; i++){
		int x = vec[i];
		dp[i].resize(occ[x] + 1);
		dp[i][0] = dp[i - 1][occ[vec[i - 1]]];
		for (int j = 1; j <= occ[x]; j++){
			int need = j / b, pre = vec[i - 1];
			int rem = occ[pre] - need * a;
			dp[i][j] = dp[i][j - 1];
			if (rem >= 0){
				dp[i][j] = max(dp[i][j], need + dp[i - 1][rem]);
			}
			ret = max(ret, dp[i][j]);
		}
	}
	return ret;
}

void solve(){
	cin >> N >> a >> b >> K;
	for (int i = 1; i <= N; i++){
		int x;
		cin >> x;
		occ[x]++;
	}
	int ans = 0;
	for (int i = 1; i <= 1e6; i++){
		if (vis[i]) continue;
		vec.clear();
		vec.pb(0);
		int j = i;
		while (j <= 1e6 && occ[j]){
			vec.pb(j);
			vis[j]++;
			j *= K;
		}
		if ((int)vec.size() >= 2){
			ans += work();
		}
	}
	cout << ans << endl;
}

int main(){
    FAST
    #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    #endif
    int tc = 1;
    // cin >> tc;
    while (tc--) solve();
    return 0;
}
