// https://www.spoj.com/problems/SUBST1/
#include <bits/stdc++.h>
using namespace std;

#define forr(i,a,b) for(int i=int(a);i<int(b);++i)
#define forn(i,n) forr(i,0,n)
#define sz(v) (int(v.size()))
#define all(v) begin(v), end(v)

using ll = long long;

#include "suffix_array.hpp"

void solve(){
	string s;
	cin >> s;
	int n = sz(s);
	auto sa = compute_sa(s);
	auto lcp = compute_lcp(s, sa);
	ll r = ll(n) * (n+1) / 2;
	for(auto x : lcp) r -= x;
	cout << r << '\n';
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int _t_;
	cin >> _t_;
	while(_t_--) solve();
}
