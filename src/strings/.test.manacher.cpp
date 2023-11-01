// https://cses.fi/problemset/task/1111

#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) forr(i, 0, n)
#define forr(i, l, r) for (int i = int(l); i < int(r); ++i)
#define sz(c) (int((c).size()))

using pii = pair<int, int>;

#include "manacher.hpp"

void solve() {
	string s;
	cin>>s;
	Manacher pals{s};
	int n = sz(s), m = 2*n+1;
	pair<int, int> best;
	forn(i, m) {
		auto curr = pals.at(i);
		if (best.second < curr.second) best = curr;
	}
	cout<<s.substr(best.first, best.second)<<'\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	solve();
}
