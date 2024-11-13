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

vector<array<int, 3>> color[10];
vector<pair<int, int>> pos[10];
ll dp[105][105][130];
char a[105][105];
int N, M, C, K;

ll dist(int r1, int c1, int r2, int c2){
	return abs(r1 - r2) + abs(c1 - c2);
}

ll work(int r, int c, int mask){
	if (__builtin_popcount(mask) == C) return dist(r, c, N, M);
	ll &ret = dp[r][c][mask];
	if (ret != -1) return ret;
	ret = 1e15;
	for (int col = 0; col < C; col++){
		if (mask & (1 << col)) continue;
		for (auto [c1, c2, t] : color[col]){
			if (mask & (1 << c1) && mask & (1 << c2))
				ret = min(ret, t + work(r, c, mask | (1 << col)));
		}
		for (auto [new_r, new_c] : pos[col])
			ret = min(ret, dist(r, c, new_r, new_c) + work(new_r, new_c, mask | (1 << col)));
	}
	return ret;
}

void solve(){
	cin >> N >> M >> C >> K;
	memset(dp, -1, sizeof(dp));
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++) cin >> a[i][j];
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
			if (a[i][j] != '0') pos[a[i][j] - '0' - 1].push_back({i, j});
	for (int i = 1; i <= K; i++){
		int c1, c2, c3, t;
		cin >> c1 >> c2 >> c3 >> t;
		color[c3 - 1].push_back({c1 - 1, c2 - 1, t});
	}
	ll ans = work(1, 1, 0);
	if (ans < 1e14) cout << ans << endl;
	else cout << -1 << endl;
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
