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
const int N_Max = 3e5 + 7;
const int Nax = 15;
const int LOG = 18;
const int BITS = 30;
const int ALPHA = 26;
ll gcd(ll a , ll b) {return b ? gcd(b , a % b) : a;}
ll lcm(ll a , ll b) {return (a * b) / gcd(a , b);}
ll inv(ll N) {if (N == 1) return 1; return (mod - ((mod / N) * inv(mod % N)) % mod) % mod;}

vector<pair<int, int>> adj[N_Max];
ll st[4 * N_Max], lazy[4 * N_Max];
int tin[N_Max], tout[N_Max];
ll dist[N_Max], ans[N_Max];
int safe[N_Max], sz[N_Max];
vector<pair<ll, int>> vec;
int N, S, timer = 0;

void pushdown(int id, int ns, int ne){
    int mid = ns + (ne - ns) / 2;
    int lc = 2 * id;
    int rc = 2 * id + 1;
    st[lc] += (mid - ns + 1) * 1LL * lazy[id];
    st[rc] += (ne - mid) * 1LL * lazy[id];
    lazy[lc] += lazy[id];
    lazy[rc] += lazy[id];
    lazy[id] = 0;
}

ll query(int id, int ns, int ne, int l, int r){
    if (ns > r || ne < l) return 0;
    if (ns >= l && ne <= r) return st[id];
    pushdown(id, ns, ne);
    int mid = ns + (ne - ns) / 2;
    int lc = 2 * id;
    int rc = 2 * id + 1;
    return query(lc, ns, mid, l, r) + query(rc, mid + 1, ne, l, r);
}

void update(int id, int ns, int ne, int l, int r, int x){
    if (ns > r || ne < l) return;
    if (ns >= l && ne <= r){
        st[id] += (ne - ns + 1) * 1LL * x;
        lazy[id] += x;
        return;
    }
    pushdown(id, ns, ne);
    int mid = ns + (ne - ns) / 2;
    int lc = 2 * id;
    int rc = 2 * id + 1;
    update(lc, ns, mid, l, r, x);
    update(rc, mid + 1, ne, l, r, x);
    st[id] = st[lc] + st[rc];
}

void dfs_init(int Node, int par, ll d){
    sz[Node] = 1;
    tin[Node] = ++timer;
    update(1, 1, N, tin[Node], tin[Node], d);
    for (auto [child, w] : adj[Node]){
        if (child == par) continue;
        dfs_init(child, Node, d + w);
        sz[Node] += sz[child];
    }
    tout[Node] = timer;
}


void dfs(int Node, int par, ll pref){
    vec.push_back({2 * pref, Node});
    int i = upper_bound(vec.begin(), vec.end(), make_pair(pref, (int)2e9)) - vec.begin();
    if (i < (int)vec.size()){
        int u = vec[i].S;
        safe[Node] = sz[u];
        ans[Node] = query(1, 1, N, tin[u], tout[u]);
    }
    for (auto [child, w] : adj[Node]){
        if (child == par) continue;
        update(1, 1, N, 1, N, w);
        update(1, 1, N, tin[child], tout[child], -2 * w);
        dfs(child, Node, pref + w);
        update(1, 1, N, 1, N, -w);
        update(1, 1, N, tin[child], tout[child], 2 * w);
    }
    vec.pop_back();
}

void solve(){
    cin >> N >> S;
    for (int i = 1; i < N; i++){
        int u, v, d;
        cin >> u >> v >> d;
        adj[u].push_back({v, d});
        adj[v].push_back({u, d});
    }
    dfs_init(S, 0, 0);
    dfs(S, 0, 0);
    for (int i = 1; i <= N; i++) cout << safe[i] << " " << ans[i] << endl;
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
