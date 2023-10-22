// https://open.kattis.com/problems/privatespace

#include <bits/stdc++.h>

using namespace std;

#define fore(e,c) for(const auto&e:(c))
#define forr(i,l,r) for(int i=int(l);i<int(r);++i)
#define forn(i,n) forr(i,0,n)
#define sz(c) (int((c).size()))

#include "simulated_annealing.hpp"

void solve() {
	int n;
	cin>>n;
	vector<int> order;
	forn(i, n) {
		const int size = i + 1;
		int num;
		cin>>num;
		while (num--) order.push_back(size);
	}
	const int groups = sz(order);
	int l, r;
	auto see = [&] {
		l = rng.integer(groups);
		r = rng.integer(groups);
		int len = 1, last = len;
		swap(order[l], order[r]);
		fore(curr, order){
			while (len < curr) len = ++last;
			len -= curr;
			if (len) --len;
		}
		swap(order[l], order[r]);
		return last;
	};
	auto upd = [&] {swap(order[l], order[r]);};
	Annealing sa{see, upd};
	sa.simulate(0.95);
	const int rows = sa.low;
	if (rows <= 12) cout<<rows<<'\n';
	else cout<<"impossible\n";
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	solve();
}
