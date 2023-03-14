// https://cses.fi/problemset/task/2108

#include <bits/stdc++.h>

using namespace std;

#define all(c) begin(c),end(c)
#define fore(e,c) for(const auto&e:(c))
#define sz(c) (int((c).size()))
#define fst first
#define snd second

using ll = long long;

#include "suffix_automaton.hpp"

void solve() {
	string s;
	cin>>s;
	ll k;
	cin>>k,--k;
	cout<<SuffixAutomaton<char>(s).kth_distinct_substring(k).fst<<'\n';
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	solve();
}
