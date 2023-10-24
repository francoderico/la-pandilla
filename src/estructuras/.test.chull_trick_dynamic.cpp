// https://codeforces.com/gym/104252/problem/B
#include <bits/stdc++.h>
using namespace std;

#define forr(i,a,b) for(int i=int(a);i<int(b);++i)
#define forn(i,n) forr(i,0,n)
#define sz(v) (int(v.size()))
#define all(v) begin(v), end(v)
#define pb push_back
#define fst first
#define snd second

typedef long long ll;
typedef pair<int,int> pii;

const ll MAXN = 2e5+100;
const ll BIG = 1e9+100;

struct Entry {
	using It = set<Entry>::iterator;
	bool is_query;
	ll m, b; mutable It it, end;
	ll x;
};

ll div_ceil(ll a, ll b) {
	if (b<0) { a=-a; b=-b; }
	if (a<0) return a/b;
	else     return (a+b-1)/b;
}

ll div_floor(ll a, ll b) {
	if (b<0) { a=-a; b=-b; }
	if (a<0) return (a-b+1)/b;
	else     return a/b;
}

ll intersect_ceil(Entry const& a, Entry const& b) {
	return div_ceil((b.b-a.b),(a.m-b.m));
}

ll intersect_floor(Entry const& a, Entry const& b) {
	return div_floor((b.b-a.b),(a.m-b.m));
}


bool operator< (Entry const& a, Entry const& b) {
	if (!b.is_query) return a.m < b.m;
	auto ni = next(a.it);
	if (ni == a.end) return false;
	auto const& c = *ni;
	return (c.b-a.b) < b.x * (a.m-c.m);
}
struct ChullTrick {
	using It = Entry::It;
	multiset<Entry> lines;
	bool covered(It it) {
		auto begin = lines.begin(), end = lines.end();
		auto ni = next(it);
		if (it == begin && ni == end) return false;
		if (it == begin) return ni->m==it->m && ni->b>=it->b;
		auto pi = prev(it);
		if (ni == end) return pi->m==it->m && pi->b>=it->b;
		return (it->m-pi->m)*(ni->b-pi->b) >= (pi->b-it->b)*(pi->m-ni->m);
	}
	tuple<bool, ll, ll> add(ll m, ll b) {
		auto it = lines.insert({false, m, b});
		it->it = it; it->end = lines.end();
		if (covered(it)) { lines.erase(it); return {false, 0, 0}; }
		while (next(it) != lines.end() && covered(next(it))) lines.erase(next(it));
		while (it != lines.begin() && covered(prev(it))) lines.erase(prev(it));

		// ESTAS LINEAS SON UN TUNEO PROPIO AL PROBLEMA
		// Devuelvo el intervalo horizontal que cubre esta nueva recta
		ll left = it==lines.begin() ? -BIG : intersect_ceil(*prev(it), *it);
		ll right = next(it)==lines.end() ? BIG : intersect_floor(*it, *next(it));
		return {true, left, right};
	}
	ll eval(ll x) {
		auto l = *lines.lower_bound({true, -1, -1, {}, {}, x});
		return l.m*x+l.b;
	}
};

struct Evt {
	int tipo;
	int id;
	ll x, y;
	ll m, b;
	pii key() const { return {x, tipo}; }
};

bool operator<(Evt const& a, Evt const& b) {
	return a.key() < b.key();
}

struct Line {
	bool is_query;
	ll m, b; int id;
	ll x, y;
};

bool operator<(Line const& a, Line const& b) {
	assert(!a.is_query);
	if (b.is_query) {
		return a.m*b.x+a.b <= b.y;
	} else {
		return a.id < b.id;
	}
}


void solve() {
	int t;
	cin >> t;

	vector<Evt> evts;

	forn(i, t) {
		int x, y;
		cin >> x >> y;
		evts.pb({0, i, x, y});
	}

	ChullTrick cht;

	int p;
	cin >> p;
	forn(i, p) {
		int m, b;
		cin >> m >> b;

		auto [added, left, right] = cht.add(m, b);
		if (!added || right < left) continue;

		evts.pb({-1, i, left,  -1, m, b});
		evts.pb({ 1, i, right, -1, m, b});
	}

	sort(all(evts));

	vector<vector<int>> result(p);
	set<Line> current_lines;
	vector<set<Line>::iterator> iters(p);

	for (auto e : evts) {

		if (e.tipo == -1) {
			iters[e.id] = current_lines.insert({false, e.m, e.b, e.id, -1, -1}).fst;
		}

		if (e.tipo == 0) {
			auto it = current_lines.lower_bound({true, -1, -1, -1, e.x, e.y});
			if (it != current_lines.end()) {
				result[it->id].pb(e.id);
			}
		}

		if (e.tipo == 1) {
			current_lines.erase(iters[e.id]);
		}
	}

	for (auto is : result) {
		cout << sz(is);
		sort(all(is));
		for (auto i : is) {
			cout << ' ' << (i+1);
		}
		cout << '\n';
	}

}

int main() {
	// freopen("input.txt", "r", stdin);
	// freopen("output.txt", "w", stdout);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
}
