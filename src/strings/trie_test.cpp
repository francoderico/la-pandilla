// https://codeforces.com/contest/455/problem/B

#include <bits/stdc++.h>

using namespace std;

#define fore(e,c) for(const auto&e:(c))
#define forr(i,l,r) for(int i=int(l);i<int(r);++i)
#define forn(i,n) forr(i,0,n)
#define sz(c) (int((c).size()))

#include "trie.hpp"

void dfs(
	const vector<map<char, int>>& next,
	vector<bool>& normal,
	vector<bool>& misere,
	int curr=0
) {
	if (next[curr].empty()) {misere[curr] = true;}
	else {
		fore(edge, next[curr]) {
			const int other = edge.second;
			dfs(next, normal, misere, other);
			if (!normal[other]) {normal[curr] = true;}
			if (!misere[other]) {misere[curr] = true;}
		}
	}
}

pair<bool, bool> play(const Trie<char>& t) {
	const int size = sz(t.next);
	vector<bool> normal(size), misere(size);
	dfs(t.next, normal, misere);
	return {normal[0], misere[0]};
}

void solve() {
	int n, k;
	cin>>n>>k;
	Trie t;
	forn(_, n) {
		string s;
		cin>>s;
		t.insert(s);
	}
	const auto [normal, misere] = play(t);
	if (normal && (misere || (k & 1))) {cout<<"First\n";}
	else {cout<<"Second\n";}
}

int main () {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	solve();
}
