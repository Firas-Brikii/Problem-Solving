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
#define int ll
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

int n , d ; 	
vector<int> v ;

bool verif (int x){
	multiset<int> s ;
	for (int i= 0 ; i<x; i++)s.insert(v[i]);
	int indx = x ;
	while (!s.empty()){
		int rass = *s.begin();
		int ins = (indx < n ? v[indx] : 0)+rass;
		s.erase(s.find(rass));
		if (ins>d)return false;
		if (indx < n) s.insert(ins);
		indx++;
	}
	return true;
}

void solve(){
	cin >> n >> d ; 
	v.resize(n);
	for (auto &x: v) cin >> x;
	int l = 1, r = n , ans =-1 ;

	while (l<=r){
		int md = l + (r-l)/2 ;
		if (verif(md)){
			r= md -1 ; 
			ans =  md ;
		}else l= md +1 ;
	}

	cout << ans << endl;
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
