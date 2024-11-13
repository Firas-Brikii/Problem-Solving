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
const int N_Max = 1e5 + 7;
const int Nax = 15;
const int LOG = 18;
const int BITS = 30;
const int ALPHA = 26;
ll gcd(ll a , ll b) {return b ? gcd(b , a % b) : a;}
ll lcm(ll a , ll b) {return (a * b) / gcd(a , b);}
ll inv(ll N) {if (N == 1) return 1; return (mod - ((mod / N) * inv(mod % N)) % mod) % mod;}

vector<int> adj[N_Max];
int dp1[N_Max], dp2[N_Max], mx[N_Max];
int a[N_Max];
int N, Q;

void dfs_init(int Node, int par){
	vector<int> vec, pref, suff;
	mx[Node] = a[Node];
	for (int child : adj[Node]){
		if (child == par) continue;
		dfs_init(child, Node);
		vec.pb(mx[child]);
		mx[Node] = max(mx[Node], mx[child] + a[Node]);
	}
	int sz = (int)vec.size();
	pref.resize(sz);
	suff.resize(sz);
	for (int i = 0; i < sz; i++) pref[i] = max((i > 0 ? pref[i - 1] : 0), vec[i]);
	for (int i = sz - 1; i >= 0; i--) suff[i] = max((i + 1 < sz ? suff[i + 1] : 0), vec[i]);
	dp1[Node] = a[Node];
	for (int i = 0; i < sz; i++){
		int best = max((i > 0 ? pref[i - 1] : 0), (i + 1 < sz ? suff[i + 1] : 0));
		dp1[Node] = max(dp1[Node], best + vec[i] + a[Node]);
	}
}

void dfs(int Node, int par){
	vector<int> vec, pref, suff;
	for (int child : adj[Node]){
		if (child == par) continue;
		vec.pb(mx[child]);
	}
	int sz = (int)vec.size();
	pref.resize(sz);
	suff.resize(sz);
	for (int i = 0; i < sz; i++) pref[i] = max((i > 0 ? pref[i - 1] : 0), vec[i]);
	for (int i = sz - 1; i >= 0; i--) suff[i] = max((i + 1 < sz ? suff[i + 1] : 0), vec[i]);
	int i = 0;
	for (int child : adj[Node]){
		if (child == par) continue;
		dp2[child] = max(a[child], dp2[Node] + a[child]);
		int best = max((i > 0 ? pref[i - 1] : 0), (i + 1 < sz ? suff[i + 1] : 0));
		dp2[child] = max(dp2[child], best + a[Node] + a[child]);
		dfs(child, Node);
		i++;
	}
}

void solve(){
	cin >> N >> Q;
	for (int i = 1; i <= N; i++) cin >> a[i];
	for (int i = 1; i < N; i++){
		int u, v;
		cin >> u >> v;
		adj[u].pb(v);
		adj[v].pb(u);
	}
	dfs_init(1, 0);
	dp2[1] = 0;
	dfs(1, 0);
	for (int q = 1; q <= Q; q++){
		int u;
		cin >> u;
		ll ans = max(dp1[u], dp2[u] + mx[u] - a[u]);
		cout << ans << endl;
	}
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
