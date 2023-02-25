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
	vector<int>order;
	forn(i, n) {
		const int size = i + 1;
		int num;
		cin>>num;
		while (num--) {order.push_back(size);}
	}
	const int groups = sz(order);
	int l, r;
	auto stir = [&] {
		l = rng.random_int(groups);
		r = rng.random_int(groups);
		int len = 1, last = len;
		swap(order[l], order[r]);
		fore(curr, order){
			while (len < curr) {len = ++last;}
			len -= curr;
			if (len) {--len;}
		}
		swap(order[l], order[r]);
		return last;
	};
	auto save = [&] {swap(order[l], order[r]);};
	simulated_annealing<int> sa(stir, save);
	const int rows = sa.simulate(0.95).peek_lowest_energy();
	if (rows <= 12) {cout<<rows<<'\n';}
	else {cout<<"impossible\n";}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	solve();
}
