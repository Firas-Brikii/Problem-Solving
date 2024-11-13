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

vector<int> adj[N_Max];
int depth[N_Max], sz[N_Max], up[N_Max][LOG];
ll dp[N_Max][205];
int N, M;

void dfs_init(int Node, int par){
	up[Node][0] = par;
	for (int i = 1; i < LOG; i++)
		up[Node][i] = up[up[Node][i - 1]][i - 1];
	sz[Node] = 1;
	for (int child : adj[Node]){
		if (child == par) continue;
		depth[child] = depth[Node] + 1;
		dfs_init(child, Node);
		sz[Node] += sz[child];
	}
}

int get_kth(int u, int x){
	for (int i = LOG - 1; i >= 0; i--)
		if (x & (1 << i)) u = up[u][i];
	return u;
}

void dfs(int Node){
	for (int child : adj[Node]){
		if (child == up[Node][0]) continue;
		for (int x = M; x > 2; x--)
			dp[child][x] += dp[Node][x - 1] - dp[child][x - 2];
		dp[child][2] += (N - sz[child]) * 1LL * (N - sz[child]);
		dp[child][1] = N * 1LL * N;
		dfs(child);
	}
}

void solve(){
	cin >> N >> M;
	for (int i = 1; i < N; i++){
		int u, v;
		cin >> u >> v;
		adj[u].pb(v);
		adj[v].pb(u);
	}
	dfs_init(1, 1);
	for (int i = 1; i <= N; i++){
		for (int k = 1; k <= min(M, depth[i] + 1); k++){
			int u = get_kth(i, k - 1);
			dp[u][k] += sz[i] * 1LL * sz[i];
		}
	}
	for (int i = 1; i <= N; i++){
		dp[i][0] = sz[i] * 1LL * sz[i];
		dp[i][1] = sz[i] * 1LL * sz[i];
	}
	dfs(1);
	ll ans = 0;
	for (int i = 1; i <= N; i++) ans += dp[i][M];
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
