// https://cses.fi/problemset/task/1111

#include <bits/stdc++.h>

using namespace std;

#define forr(i,l,r) for(int i=int(l);i<int(r);++i)
#define forn(i,n) forr(i,0,n)
#define sz(c) (int((c).size()))

#include "manacher.hpp"

void solve() {
	string s;
	cin>>s;
	const int n = sz(s);
	const auto [odd, even] = manacher<char>(s);
	int idx = 0, len = 0;
	forn(i, n) {
		const int curr = odd[i] * 2 - 1;
		if (curr > len) {len = curr, idx = i - odd[i] + 1;}
	}
	forn(i, n - 1) {
		const int curr = even[i] * 2;
		if (curr > len) {len = curr, idx = i - even[i] + 1;}
	}
	cout<<s.substr(idx, len)<<'\n';
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	solve();
}
