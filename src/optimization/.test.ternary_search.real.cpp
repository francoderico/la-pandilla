// https://codeforces.com/contest/578/problem/C

#include <bits/stdc++.h>

using namespace std;

#define forr(i,l,r) for(int i=int(l);i<int(r);++i)
#define forn(i,n) forr(i,0,n)
#define sz(c) (int((c).size()))

using ll = long long;

// para error < EPS, usar iters=log((r-l)/EPS)/log(1.618)
template<class Fun>double golden(Fun f, double l, double r, int iters){
	double const ratio = (3-sqrt(5))/2;
	double x1=l+(r-l)*ratio, x2=r-(r-l)*ratio, f1=f(x1), f2=f(x2);
	while (iters--) {
		if (f1 > f2) l=x1, x1=x2, f1=f2, x2=r-(r-l)*ratio, f2=f(x2);
		else         r=x2, x2=x1, f2=f1, x1=l+(r-l)*ratio, f1=f(x1);
	}
	return (l+r)/2;
}

int n;
vector<int> a;

double sum(double m, double sign) {
	vector<double> b(n, sign);
	forn(i, n) b[i] *= double(a[i]) + m;
	double curr = 0, best = 0;
	forn(i, n) {
		curr = max(0.0, curr + b[i]);
		best = max(best, curr);
	}
	return best;
}

void solve() {
	cout<<fixed<<setprecision(DECIMAL_DIG);
	cin>>n;
	a.resize(n);
	forn(i, n) cin>>a[i];
	auto f = [&](double m) {
		return max(sum(m, 1), sum(m, -1));
	};
	double l = -2e9, r = 2e9;
	double x = golden(f, l, r, 128);
	cout<<f(x)<<'\n';
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	solve();
}
