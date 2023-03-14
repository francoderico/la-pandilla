// https://www.spoj.com/problems/CIRU/

#include <bits/stdc++.h>

using namespace std;

#define all(c) begin(c),end(c)
#define fore(e,c) for(const auto&e:(c))
#define forn(i,n) forr(i,0,n)
#define forr(i,l,r) for(int i=int(l);i<int(r);++i)

#include "simpson.hpp"

struct Circle {
	double x, y, r;
	double height(const double px) const {
		const double b = abs(x - px);
		return sqrt(r * r - b * b);
	}
	bool inside(const double px) const {return abs(x - px) < r;}
	friend ostream& operator<<(ostream& os, const Circle& c) {
		return os<<c.x<<' '<<c.y<<' '<<c.r;
	}
};

void solve() {
	cout<<fixed<<setprecision(3);
	int n;
	cin>>n;
	double a = 2000.0, b = -2000.0;
	vector<Circle> cs(n);
	forn(i, n) {
		cin>>cs[i].x>>cs[i].y>>cs[i].r;
		a = min(a, cs[i].x - cs[i].r);
		b = max(b, cs[i].x + cs[i].r);
	}
	auto cut=[&](const double x) {
		vector<pair<double, double>> s;
		forn(i, n) {
			const Circle& c = cs[i];
			if (c.inside(x)) {
				const double h = c.height(x);
				s.emplace_back(c.y - h, c.y + h);
			}
		}
		sort(all(s));
		double y = 0.0, last = -2000.0;
		fore(p, s) {
			const auto [bottom, top] = p;
			y += max(0.0, top - max(bottom, last));
			last = max(last, top);
		}
		return y;
	};
	cout<<AdaptiveSimpson<double>(cut, 7.9, 5e-8).integrate(a, b, 4e-4)<<'\n';
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	solve();
}
