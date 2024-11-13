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

char get(char c){
	if (c == 'R') return 'B';
	return 'R';
}

void solve(){
	int N;
	string s;
	cin >> N >> s;
	s = "#" + s + "#";
	for (int i = 1; i <= N; i++){
		if (s[i] != '?') continue;
		int j = i;
		while (j <= N && s[j] == '?') j++;
		char c = 'R';
		string tmp1 = "", tmp2 = "";
		for (int k = 0; k < j - i; k++){
			tmp1 += c;
			c = get(c);
			tmp2 += c;
		}
		int cnt1 = (tmp1[0] == s[i - 1]) + (tmp1.back() == s[j]);
		int cnt2 = (tmp2[0] == s[i - 1]) + (tmp2.back() == s[j]);
		if (cnt2 < cnt1) swap(tmp1, tmp2);
		for (int k = j - 1; k >= i; k--){
			s[k] = tmp1.back();
			tmp1.pop_back();
		}
		i = j - 1;
	}
	for (int i = 1; i <= N; i++) cout << s[i];
	cout << endl;
}

int main(){
    FAST
    #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    #endif
    int tc = 1;
    cin >> tc;
    while (tc--) solve();
    return 0;
}
