// https://cses.fi/problemset/task/1110

#include <bits/stdc++.h>

using namespace std;

#define sz(c) (int((c).size()))

#include "lyndon_factorization.hpp"

void solve() {
	string s;
	cin>>s;
	cout<<smallest_cyclic_shift(s).first<<'\n';
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	solve();
}
