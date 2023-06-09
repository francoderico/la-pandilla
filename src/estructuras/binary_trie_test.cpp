// https://codeforces.com/contest/842/problem/D

#include <bits/stdc++.h>

using namespace std;

#define fore(e,c) for(const auto&e:(c))
#define forr(i,l,r) for(int i=int(l);i<int(r);++i)
#define forn(i,n) forr(i,0,n)
#define dforr(i,l,r) for(int i=int(r)-1;i>=int(l);--i)
#define dforn(i,n) dforr(i,0,n)
#define sz(c) (int((c).size()))
#define fst first
#define snd second

#include "binary_trie.hpp"

void solve() {
	const unsigned nums = 524'288;
	int n, m;
	cin>>n>>m;
	vector<unsigned> a(n);
	forn(i, n) {cin>>a[i];}
	BinaryTrie<19U> t;
	forn(i, nums) {t.insert(i);}
	fore(e, a) {t.erase(e);}
	unsigned x = 0;
	forn(i, m) {
		unsigned y;
		cin>>y;
		x ^= y;
		cout<<t.min_max_xor(x).fst.to_ullong()<<'\n';
	}
}

int main () {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	solve();
}
