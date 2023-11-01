// https://cses.fi/problemset/task/1110

#include <bits/stdc++.h>

using namespace std;

#define fore(e, c) for(auto const& e : (c))
#define sz(c) (int((c).size()))
#define fst first

using pii = pair<int, int>;

#include "lyndon.hpp"

void solve() {
	string s;
	cin>>s;
	int start = minrot(s);
	auto rot = s.substr(start) + s.substr(0, start);
	cout<<rot<<'\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	solve();
}
