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
const int N_Max = 2e6 + 7;
const int Nax = 15;
const int LOG = 18;
const int BITS = 30;
const int ALPHA = 26;
ll gcd(ll a , ll b) {return b ? gcd(b , a % b) : a;}
ll lcm(ll a , ll b) {return (a * b) / gcd(a , b);}
ll inv(ll N) {if (N == 1) return 1; return (mod - ((mod / N) * inv(mod % N)) % mod) % mod;}

template<class T> struct Seg { // comb(ID,b) = b
    const T ID = 0;    ll n; vector<T> seg;
    T comb(T a, T b) { return  a + b; }
    void init(ll _n) { n = _n; seg.assign(2*n,ID); }
    void pull(ll p) { seg[p] = comb(seg[2*p],seg[2*p+1]); }
    void upd(ll p, T val) { // set val at position p
        seg[p += n] += val; for (p /= 2; p; p /= 2) pull(p); }
    T query(ll l, ll r) {   // sum on llerval [l, r]
        T ra = ID, rb = ID;
        for (l += n, r += n+1; l < r; l /= 2, r /= 2) {
            if (l&1) ra = comb(ra,seg[l++]);
            if (r&1) rb = comb(seg[--r],rb);
        }return comb(ra,rb);
    }
};

vector<pair<int, int>> qry[N_Max];
vector<int> adj[N_Max];
int tin[N_Max], tout[N_Max];
int depth[N_Max], sz[N_Max];
int bchild[N_Max], tour[N_Max];
ll ans[N_Max];
Seg<int> st;
int N, Q, timer = 0;

void dfs_init(int Node, int par){
	tour[++timer] = Node;
	tin[Node] = timer;
	bchild[Node] = -1;
	sz[Node] = 1;
	for (int child : adj[Node]){
		if (child == par) continue;
		depth[child] = depth[Node] + 1;
		dfs_init(child, Node);
		sz[Node] += sz[child];
		if (bchild[Node] == -1 || sz[child] > sz[bchild[Node]]) bchild[Node] = child;
	}
	tout[Node] = timer;
}

void dfs(int Node, int par, bool keep){
	for (int child : adj[Node]){
		if (child == par || child == bchild[Node]) continue;
		dfs(child, Node, false);
	}
	if (bchild[Node] != -1) dfs(bchild[Node], Node, true);
	for (int child : adj[Node]){
		if (child == par || child == bchild[Node]) continue;
		for (int i = tin[child]; i <= tout[child]; i++){
			int u = tour[i];
			for (auto [k, id] : qry[Node])
				ans[id] += st.query(max(0, k + 2 * depth[Node] - depth[u]), N);
		}
		for (int i = tin[child]; i <= tout[child]; i++)
			st.upd(depth[tour[i]], 1);
	}
	for (auto [k, id] : qry[Node])
		ans[id] += st.query(min(N, depth[Node] + k), N);
	st.upd(depth[Node], 1);
	if (keep) return;
	for (int i = tin[Node]; i <= tout[Node]; i++)
		st.upd(depth[tour[i]], -1);
}

void solve(){
	cin >> N >> Q;
	st.init(N + 5);
	for (int i = 1; i < N; i++){
		int u, v;
		cin >> u >> v;
		adj[u].pb(v);
		adj[v].pb(u);
	}
	dfs_init(1, 0);
	for (int i = 1; i <= Q; i++){
		int u, k;
		cin >> u >> k;
		qry[u].push_back({k, i});
	}
	dfs(1, 0, false);
	for (int i = 1; i <= Q; i++) cout << ans[i] << endl;
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
