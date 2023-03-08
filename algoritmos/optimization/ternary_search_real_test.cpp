// https://codeforces.com/contest/578/problem/C

#include <bits/stdc++.h>

using namespace std;

#define forr(i,l,r) for(int i=int(l);i<int(r);++i)
#define forn(i,n) forr(i,0,n)
#define sz(c) (int((c).size()))

using ll = long long;

#include "ternary_search.hpp"

double get_sum(const vector<int>& a, const double m, const double sign) {
	const int n = sz(a);
	vector<double> b(n, sign);
	forn(i, n) {b[i] *= static_cast<double>(a[i]) + m;}
	double curr = 0.0, best = 0.0;
	forn(i, n) {
		curr = max(0.0, curr + b[i]);
		best = max(best, curr);
	}
	return best;
}

void solve() {
	cout<<fixed<<setprecision(numeric_limits<double>::max_digits10);
	int n;
	cin>>n;
	vector<int> a(n);
	forn(i, n) {cin>>a[i];}
	const double l = -2e9, r = 2e9;
	const auto f = [&](const double m) {
		return max(get_sum(a, m, 1), get_sum(a, m, -1));
	};
	const double x = ternary_search_real(l, r, f, 128);
	cout<<f(x)<<'\n';
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	solve();
}
