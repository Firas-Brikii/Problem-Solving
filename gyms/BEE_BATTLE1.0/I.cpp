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

const int N = 1100 ; 
ll dp[2][4][2*N] ;

void solve(){
	int n , k ; 
	cin >> n >> k ;


	dp[0][0][1] = dp[0][3][1] = 1 ;
	dp[0][1][2] = dp[0][2][2] = 1 ; 


	for(int i=2 ; i<=n ; i++){
		for(int j=0 ; j<4 ; j++){
			for(int p=0 ; p<=2*n ; p++) dp[1][j][p] = 0 ; 
		}
		
		for(int j=0 ; j<4 ; j++){
			for(int r=0 ; r<4 ; r++){
				for(int p=0 ; p<=2*n ; p++){
					int x = 0 ;
					for(int g=0 ; g<2 ; g++) {
						if((1<<g)&j) x++ ;
						if((1<<g)&r) x++ ; 
					}
					int y = 4 - x ;
					int p1 = (((1<<0)&j)>0) , p2 = (((1<<1)&j)>0) , p3 = (((1<<0)&r) > 0) , p4 = (((1<<1)&r)>0) ;  
					
					if(x==4 || y==4){
						dp[1][j][p] = (dp[1][j][p] + dp[0][r][p])%mod ; 
					}
					else if(x==3 || y==3) {
						if( p1==p2 ) dp[1][j][p] = (dp[1][j][p] + dp[0][r][p])%mod ; 
						else dp[1][j][p+1] = (dp[1][j][p+1] + dp[0][r][p])%mod ; 
					}else if(x==2){
						if(p1==p3 || p2==p4){
							dp[1][j][p] = (dp[1][j][p] + dp[0][r][p])%mod ; 
						}else if(p1==p2){
							dp[1][j][p+1] = (dp[1][j][p+1] + dp[0][r][p])%mod ; 
						}else if(p1==p4){
							dp[1][j][p+2] = (dp[1][j][p+2] + dp[0][r][p])%mod ; 
						}
					}
				}
			}
		}
		swap(dp[0] , dp[1]) ; 
	}
	
	ll ans = 0  ;
	for(int i=0 ; i<4 ; i++) ans = (ans + dp[0][i][k])%mod ; 
	cout << ans << endl ; 
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
