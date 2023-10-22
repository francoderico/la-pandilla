// https://cses.fi/problemset/task/1753/

#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) forr(i, 0, n)
#define forr(i, l, r) for (int i = int(l); i < int(r); ++i)
#define sz(c) (int((c).size()))

using ll = long long;

#include "hashing.cpp"

void solve() {
	string t, p;
	cin>>t>>p;
	int n = sz(t), m = sz(p);
	StrHash ht{t}, hp{p};
	ll h = hp.get(0, m);
	int count = 0;
	forn(i, n-m+1) if (ht.get(i, m) == h) ++count;
	cout<<count<<'\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	solve();
}
