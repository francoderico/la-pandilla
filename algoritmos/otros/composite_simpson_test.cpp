// https://acm.timus.ru/problem.aspx?num=1562

#include <bits/stdc++.h>

using namespace std;

#define forn(i,n) forr(i,0,n)
#define forr(i,l,r) for(int i=int(l);i<int(r);++i)

#include "simpson.hpp"

const double pi = acosl(-1);

void solve() {
	cout<<fixed<<setprecision(6);
	const int blocks = 1e6;
	double a, b;
	int n;
	cin>>a>>b>>n;
	const int range = blocks / n;
	const auto ff = [a, b](const double x) {
		static const double ha = a / 2.0;
		static const double hb = b / 2.0;
		return pi * ha * ha * (1.0 - (x * x) / (hb * hb));
	};
	const double start = -b / 2.0;
	const double step = b / n;
	forn(i, n) {
		const double left = start + i * step;
		const double right = left + step;
		cout<<composite_simpson(left, right, ff, range)<<'\n';
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	solve();
}
