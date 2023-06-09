// https://codeforces.com/contest/439/problem/D

#include <bits/stdc++.h>

using namespace std;

#define all(c) begin(c),end(c)
#define forr(i,l,r) for(int i=int(l);i<int(r);++i)
#define forn(i,n) forr(i,0,n)

using ll = long long;

#include "ternary_search.hpp"

void solve() {
	int n, m;
	cin>>n>>m;
	vector<ll> a(n), b(m);
	forn(i, n) {cin>>a[i];}
	forn(j, m) {cin>>b[j];}
	const ll l = 0, r = 1'000'000'001;
	const auto f = [&](const ll k) {
		ll ans = 0;
		forn(i, n) {ans += max(0LL, k - a[i]);}
		forn(j, m) {ans += max(0LL, b[j] - k);}
		return ans;
	};
	const ll k = ternary_search_integer(l, r, f);
	cout<<f(k)<<'\n';
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	solve();
}
