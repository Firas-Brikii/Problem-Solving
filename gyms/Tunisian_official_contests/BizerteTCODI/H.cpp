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
const ll mod = 1e9;
const int N_Max = 4e5 + 7;
const int Nax = 15;
const int LOG = 18;
const int BITS = 30;
const int ALPHA = 26;
ll gcd(ll a , ll b) {return b ? gcd(b , a % b) : a;}
ll lcm(ll a , ll b) {return (a * b) / gcd(a , b);}
ll inv(ll N) {if (N == 1) return 1; return (mod - ((mod / N) * inv(mod % N)) % mod) % mod;}

int add(int a, int b){return (a + 0LL + b) % mod;}

int sub(int a, int b){return (a - b + 0LL + mod) % mod;}

int mult(int a, int b){return a * 1LL * b % mod;}

int divide(int a, int b){return a * 1LL * inv(b) % mod;}

struct Node{
    int s0, s1;
};

int lazy[4 * N_Max];
Node st[4 * N_Max];
int pref[N_Max];
int fib[N_Max];
int a[N_Max];
int N, Q;

int get(Node curr, int x){
    if (x == 0) return curr.s0;
    if (x == 1) return curr.s1;
    return add(mult(curr.s0, fib[x - 2]), mult(curr.s1, fib[x - 1]));
}

Node merge(Node l, Node r, int ns, int ne){
    int mid = ns + (ne - ns) / 2;
    Node ret;
    ret.s0 = add(l.s0, get(r, mid - ns + 1));
    ret.s1 = add(l.s1, get(r, mid - ns + 2));
    return ret;
}

void build(int id, int ns, int ne){
    if (ns == ne){
        st[id] = {a[ns], a[ns]};
        return;
    }
    int mid = ns + (ne - ns) / 2;
    int lc = 2 * id;
    int rc = 2 * id + 1;
    build(lc, ns, mid);
    build(rc, mid + 1, ne);
    st[id] = merge(st[lc], st[rc], ns, ne);
}

void pushdown(int id, int ns, int ne){
    int mid = ns + (ne - ns) / 2;
    int lc = 2 * id;
    int rc = 2 * id + 1;

    st[lc].s0 = add(st[lc].s0, mult(pref[mid - ns], lazy[id]));
    st[lc].s1 = add(st[lc].s1, mult(sub(pref[mid - ns + 1], pref[0]), lazy[id]));
    lazy[lc] = add(lazy[lc], lazy[id]);

    st[rc].s0 = add(st[rc].s0, mult(pref[ne - mid - 1], lazy[id]));
    st[rc].s1 = add(st[rc].s1, mult(sub(pref[ne - mid], pref[0]), lazy[id]));
    lazy[rc] = add(lazy[rc], lazy[id]);

    lazy[id] = 0;
}

void update_set(int id, int ns, int ne, int ind, int x){
    if (ind < ns || ind > ne) return;
    if (ns == ne){
        st[id] = {x, x};
        return;
    }
    pushdown(id, ns, ne);
    int mid = ns + (ne - ns) / 2;
    int lc = 2 * id;
    int rc = 2 * id + 1;
    update_set(lc, ns, mid, ind, x);
    update_set(rc, mid + 1, ne, ind, x);
    st[id] = merge(st[lc], st[rc], ns, ne);
}

void update_add(int id, int ns, int ne, int l, int r, int x){
    if (ns > r || ne < l) return;
    if (ns >= l && ne <= r){
        lazy[id] = add(lazy[id], x);
        st[id].s0 = add(st[id].s0, mult(pref[ns - ne], x));
        st[id].s1 = add(st[id].s1, mult(sub(pref[ne - ns + 1], pref[0]), x));
        return;
    }
    pushdown(id, ns, ne);
    int mid = ns + (ne - ns) / 2;
    int lc = 2 * id;
    int rc = 2 * id + 1;
    update_add(lc, ns, mid, l, r, x);
    update_add(rc, mid + 1, ne, l, r, x);
    st[id] = merge(st[lc], st[rc], ns, ne);
}

int query(int id, int ns, int ne, int l, int r){
    if (ns > r || ne < l) return 0;
    if (ns >= l && ne <= r) return get(st[id], ns - l);
    pushdown(id, ns, ne);
    int mid = ns + (ne - ns) / 2;
    int lc = 2 * id;
    int rc = 2 * id + 1;
    return add(query(lc, ns, mid, l, r), query(rc, mid + 1, ne, l, r));
}

void solve(){
    cin >> N >> Q;
    for (int i = 1; i <= N; i++) cin >> a[i];
    build(1, 1, N);
    for (int q = 1; q <= Q; q++){
        int t;
        cin >> t;
        if (t == 1){
            int ind, x;
            cin >> ind >> x;
            update_set(1, 1, N, ind, x);
        }
        else if (t == 2){
            int l, r;
            cin >> l >> r;
            cout << query(1, 1, N, l, r) << endl;
        }
        else{
            int l, r, x;
            cin >> l >> r >> x;
            update_add(1, 1, N, l, r, x);
        }
    }
}

int main(){
    FAST
    #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    #endif
    fib[0] = fib[1] = 1;
    for (int i = 2; i < N_Max; i++) fib[i] = add(fib[i - 1], fib[i - 2]);
    pref[0] = 1;
    for (int i = 1; i < N_Max; i++) pref[i] = add(pref[i - 1], fib[i]);
    int tc = 1;
    // cin >> tc;
    while (tc--) solve();
    return 0;
}
