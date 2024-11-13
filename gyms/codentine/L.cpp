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
const ll mod = 998244353;
const int N_Max = 2e5 + 7;
const int Nax = 15;
const int LOG = 18;
const int BITS = 30;
const int ALPHA = 26;
ll gcd(ll a , ll b) {return b ? gcd(b , a % b) : a;}
ll lcm(ll a , ll b) {return (a * b) / gcd(a , b);}
ll inv(ll N) {if (N == 1) return 1; return (mod - ((mod / N) * inv(mod % N)) % mod) % mod;}

vector<vector<ll>> mul(vector<vector<ll>> a, vector<vector<ll>> b, int K){
	vector<vector<ll>> ret(K + 2, vector<ll>(K + 2));
	for (int i = 0; i < K + 2; i++){
		for (int j = 0; j < K + 2; j++){
			ret[i][j] = 0;
			for (int p = 0; p < K + 2; p++)
				ret[i][j] = (ret[i][j] + a[i][p] * b[p][j] % mod) % mod;
		}
	}
	return ret;
}

vector<vector<ll>> binpow(vector<vector<ll>> a, ll b, int K){
	vector<vector<ll>> ret(K + 2, vector<ll>(K + 2));
    for (int i = 0; i < K + 2; i++) ret[i][i] = 1;
    while (b > 0) {
        if (b & 1)
            ret = mul(ret, a, K);
        a = mul(a, a, K);
        b >>= 1;
    }
    return ret;
}

void solve(){
	ll L;
	int K;
	cin >> L >> K;
	vector<vector<ll>> transition(K + 2, vector<ll>(K + 2));
	transition[0][0] = 1;
	for (int i = 0; i < K + 2; i++) transition[K + 1][i] = transition[K][i] = 1;
	transition[K][K + 1] = 0;
	for (int i = 1; i < K; i++) transition[i][i + 1] = 1;
	transition = binpow(transition, L, K);
	// dbg(transition);
	cout << transition[K + 1][0] << endl;
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
