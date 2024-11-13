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
#define int ll
ll gcd(ll a , ll b) {return b ? gcd(b , a % b) : a;}
ll lcm(ll a , ll b) {return (a * b) / gcd(a , b);}
ll inv(ll N) {if (N == 1) return 1; return (mod - ((mod / N) * inv(mod % N)) % mod) % mod;}

const int N = 500100 ; 
map<int,int> f;
ll occ[N] ;
ll dp[2][N] , p[N]; 

void solve(){
	int n ;
	cin >> n ;
	p[0] = 1 ; 
	for(int i = 1 ; i <= n ; i++) p[i] = p[i - 1] * 2 % mod;
	vector<array<int,2>> g ; 
	for(int i = 1 ; i <= n ;i++){
		int x ;
		cin >> x ; 
		f[x]++ ; 
	}
	for(auto x : f) occ[x.S]++ ;
	g.push_back({0 , 0}) ;
	for(int i = 1 ; i <= n ; i++) {
		if(occ[i] > 0) g.push_back({i , occ[i]}) ; 
	}  
	dp[0][0] = 1;
	int sz = g.size() ;
	for(int i = 1 ; i < sz ; i++){
		for(int x = 0 ; x <= 3*n ; x++)
			dp[1][x] = dp[0][x] * p[g[i][1] - 1] % mod  ;	
		for(int x = 0 ; x <= 3*n ; x++)
			dp[1][(x ^ g[i][0])] = (dp[1][(x ^ g[i][0])] + dp[0][x] * p[g[i][1] - 1] % mod ) % mod ; 
		swap(dp[0] , dp[1]) ; 
	}
	cout << dp[0][0] << endl; 
}

int32_t main(){
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
