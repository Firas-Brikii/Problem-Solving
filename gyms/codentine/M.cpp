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

vector<int> adj[N_Max];
int freq[N_Max], occ[N_Max];
int a[N_Max];
int N, K;

void dfs(int Node, int par){
	for (int child : adj[Node]){
		if (child == par) continue;
		freq[a[Node]]++;
		dfs(child, Node);
	}
}

void solve(){
	cin >> N >> K;
	int mx = 0;
	for (int i = 1; i <= N; i++){
		cin >> a[i];
		mx = max(mx, a[i]);
	}
	for (int i = 1; i < N; i++){
		int u, v;
		cin >> u >> v;
		adj[u].pb(v);
		adj[v].pb(u);
		int g = gcd(a[u], a[v]);
		occ[g]++;
	}
	dfs(1, 0);
	for (int i = 1; i <= K; i++){
		int ans = 1;
		for (int j = i; j <= mx; j += i){
			ans += freq[j];
			ans -= occ[j];
		}
		if (a[1] % i == 0) ans--;
		cout << ans << " ";
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