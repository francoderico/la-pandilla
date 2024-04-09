// https://codeforces.com/contest/963/problem/D

#include <bits/stdc++.h>

using namespace std;

#define fore(e,c) for(const auto&e:(c))
#define forr(i,l,r) for(int i=int(l);i<int(r);++i)
#define forn(i,n) forr(i,0,n)
#define sz(c) (int((c).size()))
#define pb push_back
#define fst first
#define snd second

#include "aho_corasick.hpp"

void solve() {
	string s;
	cin>>s;
	int q;
	cin>>q;
	AhoCorasick<char>t;
	vector<pair<int,string>> queries(q);
	forn(i, q) {
		cin>>queries[i].fst>>queries[i].snd;
		t.insert(queries[i].snd);
	}
	t.compute();
	vector<vector<int>> matches = t.match(s);
	forn(i, q) {
		const auto& [k, p] = queries[i];
		const auto occs = matches[i];
		if (sz(occs) < k) {cout<<"-1\n";}
		else {
			int l = 0, r = k - 1;
			int ans = occs[r] - occs[l];
			while ((++l, ++r) < sz(occs)) {ans = min(ans, occs[r] - occs[l]);}
			ans += sz(p);
			cout<<ans<<'\n';
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	solve();
}
