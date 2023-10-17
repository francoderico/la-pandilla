// https://www.spoj.com/problems/CIRU/

#include <bits/stdc++.h>

using namespace std;

#define all(c) begin(c), end(c)
#define fore(e, c) for(const auto& e: (c))
#define forn(i, n) forr(i, 0, n)
#define forr(i, l, r) for (int i = int(l); i < int(r); ++i)

#include "simpson.hpp"

struct Circle {
	dbl x, y, r;
	dbl height(dbl px) const {
		dbl b = abs(x - px);
		return sqrt(r * r - b * b);
	}
	bool inside(dbl px) const {return abs(x - px) < r;}
};

void solve() {
	cout<<fixed<<setprecision(3);
	int n;
	cin>>n;
	dbl a = 2e3, b = -2e3;
	vector<Circle> cs(n);
	forn(i, n) {
		cin>>cs[i].x>>cs[i].y>>cs[i].r;
		a = min(a, cs[i].x - cs[i].r);
		b = max(b, cs[i].x + cs[i].r);
	}
	auto cut = [&](dbl x) {
		vector<pair<dbl, dbl>> s;
		forn(i, n) {
			Circle const& c = cs[i];
			if (c.inside(x)) {
				dbl h = c.height(x);
				s.emplace_back(c.y - h, c.y + h);
			}
		}
		sort(all(s));
		dbl y = 0, last = -2e3;
		fore(p, s) {
			auto [bottom, top] = p;
			y += max(0.0, top - max(bottom, last));
			last = max(last, top);
		}
		return y;
	};
	cout<<Simpson<decltype(cut)>(cut, 7.9, 5e-8).integrate(a, b, 4e-4)<<'\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	solve();
}
