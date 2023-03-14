// https://codeforces.com/gym/104114/problem/B
#include <bits/stdc++.h>
using namespace std;

#define forr(i,a,b) for(int i = int(a); i < int(b); ++i)
#define forn(i,n) forr(i,0,n)
#define dforr(i,a,b) for(int i = int(b)-1; i>=int(a); --i)
#define dforn(i,n) dforr(i,0,n)
#define db(v) cerr << #v " = " << (v) << '\n'
#define vecp(v) cerr << #v " = "; for (auto ee:v) cerr  << (ee) << ' '; cerr << '\n'
#define nn cout << '\n'
#define sz(v) (int(v.size()))
#define all(v) (v).begin(), (v).end()
#define pb push_back
#define pp pop_back
#define fst first
#define snd second

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<ll> vll;

const ll MAXN = 2e5 + 100;
const ll INF = 1e18 + 100;
const ll MOD = 1e9 + 7;
const ld EPS = 1e-9;
const ld PI = acosl(-1);

using Sc = ll;

struct pt { Sc x, y; };

ostream& operator<<(ostream& o, pt const& p) {
	return o << "[" << p.x << " " << p.y << "]";
}

pt operator+(pt const& a, pt const& b) { return {a.x+b.x, a.y+b.y}; }
pt operator-(pt const& a, pt const& b) { return {a.x-b.x, a.y-b.y}; }
pt operator*(Sc const& x, pt const& p) { return {x*p.x, x*p.y}; }
bool operator<(pt const& a, pt const& b) { return a.x!=b.x ? a.x<b.x : a.y<b.y; }

Sc dot(pt const& a, pt const& b) { return a.x*b.x + a.y*b.y; }
Sc det(pt const& a, pt const& b) { return a.x*b.y - a.y*b.x; }
Sc len_sq(pt const& p) { return dot(p, p); }

bool ccw(pt const& o, pt const& a, pt const& b) { return det(a-o, b-o) > 0; }
bool  cw(pt const& o, pt const& a, pt const& b) { return det(a-o, b-o) < 0; }
bool en_recta(pt const& o, pt const& a, pt const& b) { return det(a-o, b-o) == 0; }
bool en_semirrecta(pt const& o, pt const& a, pt const& b) { return det(a-o, b-o) == 0 && dot(a-o, b-o) >= 0; }

int cuadrante(pt const& a, pt const& b, pt const& x) {
	pt d1 = b-a, d2 = x-a;
	Sc det12 = det(d1, d2);
	Sc dot12 = dot(d1, d2);
	if (det12 >= 0 && dot12 > 0) return 1;
	if (det12 > 0 && dot12 <= 0) return 2;
	if (det12 <= 0 && dot12 < 0) return 3;
	if (det12 < 0 && dot12 >= 0) return 4;
	return -1;
}

auto por_angulo(pt const& a, pt const& b) {
	return [=](pt const& x, pt const& y) {
		int cx = cuadrante(a,b,x);
		int cy = cuadrante(a,b,y);
		if (cx != cy) return cx < cy;
		Sc d = det(x-a, y-a);
		if (d != 0) return d > 0;
		return len_sq(x-a) < len_sq(y-a); // el mas corto primero
	};
}

vector<pt> chull(vector<pt> ps) {
	auto it = min_element(all(ps));
	iter_swap(it, ps.begin());
	auto o = ps[0];
	sort(ps.begin()+1, ps.end(), [&](pt const& a, pt const& b) {
		if (det(a-o, b-o) == 0) return len_sq(a-o) < len_sq(b-o); // el mas corto primero
		return ccw(o, a, b);
	});
	int j = 2;
	forr(i,2,sz(ps)) {
		while (j >= 2 && not ccw(ps[j-2], ps[j-1], ps[i])) {
			j--;
		}
		ps[j++] = ps[i];
	}
	ps.resize(j);
	return ps;
}

int solve_lado(pt q1, pt q2, vector<pt> const& ps) {

	int semip = 0;
	int lado1 = 0;
	int lado2 = 0;

	forn(i, sz(ps)) {
		if (ccw(q2, q1, ps[i])) semip++;
		if (en_semirrecta(q1, q1+(q1-q2), ps[i])) lado1++;
		if (en_semirrecta(q2, q2+(q2-q1), ps[i])) lado2++;
	}

	return max(semip+lado1, semip+lado2);
}

int solve_angulo(pt q1, pt q2, pt q3, vector<pt> ps) {
	auto en_region = [&](pt p) {
		return cw(q2, q3, p)
		    || ccw(q2, q1, p)
		    || en_semirrecta(q2, q2+(q2-q1), p)
		    || en_semirrecta(q2, q2+(q2-q3), p);
	};

	ps.erase(remove_if(all(ps), [&](pt p) { return not en_region(p); }), ps.end());

	sort(all(ps), por_angulo(q2, q1));

	int best = 0;
	int j = 0;
	forn(i,sz(ps)) {
		j = max(j, i+1);
		for (; j < sz(ps); ++j) {
			bool bueno = ccw(q2, ps[i], ps[j])
			          || en_semirrecta(q2, ps[i], ps[j]);
			if (!bueno) break;
		}

		int cant = j-i;
		best = max(best, cant);
	}

	return best;
}

void solve() {
	int n, m;
	cin >> n >> m;


	vector<pt> ps(n), qs(m);

	forn(i,n){
		double x,y;cin>>x>>y;
		ps[i] = {ll(x*1e6+0.5), ll(y*1e6+0.5)};
	}

	forn(i,m){
		double x,y;cin>>x>>y;
		qs[i] = {ll(x*1e6+0.5), ll(y*1e6+0.5)};
	}

	int best = 0;

	if (m == 1) {

		pt q = qs[0];

		sort(all(ps), por_angulo(q, q+pt{1,0}));

		int j = 0;
		forn(i, sz(ps)) {
			j = max(j, i+1);
			while(j-i < n && j < 3*n && (cw(ps[i], q, ps[j%n]) || en_semirrecta(q, ps[i], ps[j%n]))) {
				j++;
			}
			int cant = j-i;
			best = max(best, cant);
		}

	} else {
		auto c = chull(qs);
		int w = sz(c);

		forn(k, w) {
			auto q1 = c[k];
			auto q2 = c[(k+1)%w];
			best = max(best, solve_lado(q1, q2, ps));
		}

		forn(k, w) {
			auto q1 = c[k];
			auto q2 = c[(k+1)%w];
			auto q3 = c[(k+2)%w];
			best = max(best, solve_angulo(q1, q2, q3, ps));
		}
	}

	cout << best << '\n';
}

int main () {
	// freopen("input.txt", "r", stdin);
	// freopen("output.txt", "w", stdout);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();

	return 0;
}
