// https://acm.timus.ru/problem.aspx?num=1562

#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) forr(i, 0, n)
#define forr(i, l, r) for (int i = int(l); i < int(r); ++i)

using dbl = double;

template<class Fun> dbl simpson(Fun f, dbl a, dbl b, int n=1e4) {
	int m = 2 * n; // Integra `f` en `[a, b]` llamandola `2 * n` veces.
	dbl h = (b - a) / m, s = f(a);
	forr(i, 1, m) s += f(a + i * h) * ((i % 2) ? 4 : 2);
	return (s + f(b)) * h / 3;
}

constexpr dbl pi = acos(-1);

void solve() {
	cout<<fixed<<setprecision(6);
	dbl a, b;
	int n;
	cin>>a>>b>>n;
	auto f = [a, b](dbl x) {
		static dbl ha = a / 2, hb = b / 2;
		return pi * ha * ha * (1 - (x * x) / (hb * hb));
	};
	int blocks = 1e6, range = blocks / n;
	dbl start = -b / 2, step = b / n;
	forn(i, n) {
		dbl l = start + i * step, r = l + step;
		cout<<simpson(f, l, r, range)<<'\n';
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	solve();
}
