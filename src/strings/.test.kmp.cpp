// https://codeforces.com/contest/471/problem/D

#include <bits/stdc++.h>

using namespace std;

#define forr(i,l,r) for(int i=int(l);i<int(r);++i)
#define forn(i,n) forr(i,0,n)
#define sz(c) (int((c).size()))

#include "string_functions.hpp"
#include "kmp.hpp"

vector<int> read(int m) {
	vector<int> v;
	v.reserve(m);
	int last = -1;
	forn(i, m) {
		int curr;
		cin>>curr;
		if (last != -1) {
			int next = last - curr;
			if (next <= 0) {--next;}
			v.push_back(next);
		}
		last = curr;
	}
	v.push_back(0);
	return v;
}

void solve() {
	int n, w;
	cin>>n>>w;
	vector<int> a = read(n), b = read(w);
	vector<int> occs = Kmp<int>(b.data()).matches(a.data());
	cout<<sz(occs)<<'\n';
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	solve();
}
