// https://cses.fi/problemset/task/2106

#include <bits/stdc++.h>

using namespace std;

#define all(c) begin(c),end(c)
#define forr(i,l,r) for(int i=int(l);i<int(r);++i)
#define fore(e,c) for(const auto&e:(c))
#define sz(c) (int((c).size()))
#define pb push_back
#define fst first
#define snd second

using ll = long long;

#include "suffix_automaton.hpp"

void solve(const SuffixAutomaton<char>& sa) {
	int start = 0, bestlen = -1;
	forr(curr, 1, sa.size) {
		const int len = sa.len[curr];
		if (len > bestlen) {
			if (sa.terminal_paths_from[curr] > 1) {
				start = sa.firstpos[curr] + 1 - (bestlen = len);
			}
		}
	}
	if (bestlen == -1) {cout<<"-1\n";}
	else{cout<<sa.txt.substr(start, bestlen)<<'\n';}
}

void solve() {
	string s;
	cin>>s;
	SuffixAutomaton<char> sa(s);
	solve(sa);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	solve();
}
