// https://cses.fi/problemset/task/2107

#include <bits/stdc++.h>

using namespace std;

#define forr(i,l,r) for(int i=int(l);i<int(r);++i)
#define forn(i,n) forr(i,0,n)
#define sz(c) (int((c).size()))

#include "string_functions.hpp"

template<typename Type>
ostream& operator<<(ostream& os, const vector<Type>& v) {
	const int n = sz(v);
	forn(i, n) {
		os<<v[i];
		if(i != n - 1) {os<<' ';}
	}
	return os;
}

void solve() {
	string s;
	cin>>s;
	cout<<z_function(s)<<'\n';
	cout<<prefix_function(s)<<'\n';
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	solve();
}
