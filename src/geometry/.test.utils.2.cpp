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

// representamos poligonos con vector<pt>. son siempre contra-reloj.
// pt ("point") es un vector, sc ("scalar") es el tipo de sus componentes
using sc = ll; struct pt { sc x, y; };

pt girar(pt p) { return {-p.y, p.x}; } // rota 90 grados contra-reloj
pt operator+(pt a, pt b) { return {a.x + b.x, a.y + b.y}; }
pt operator-(pt a, pt b) { return {a.x - b.x, a.y - b.y}; }
pt operator*(sc x, pt p) { return {x * p.x, x * p.y}; }
pair<sc, sc> to_pair(pt p) { return {p.y, p.x}; }
bool operator<(pt a, pt b) { return to_pair(a) < to_pair(b); }
bool operator==(pt a, pt b) { return to_pair(a) == to_pair(b); }
sc det(pt a, pt b) { return a.x*b.y - a.y*b.x; } // determinante
sc dot(pt a, pt b) { return a.x*b.x + a.y*b.y; } // producto escalar
double len(pt p) { return hypot(p.x, p.y); } // modulo
sc len_sq(pt p) { return dot(p, p); } // modulo cuadrado

// el giro a hacia b con centro en o es contra-reloj
bool ccw(pt o, pt a, pt b) { return det(a-o, b-o) > 0; }
bool cw(pt o, pt a, pt b) { return det(a-o, b-o) < 0; }

bool en_recta(pt o, pt a, pt b) { return det(a-o, b-o) == 0; }
bool en_semi(pt o,pt a,pt b){return det(a-o, b-o)==0 && dot(a-o,b-o)>=0;}

// cuadrante del angulo que forma el punto x con la semirrecta ab
int cuadrante(pt a, pt b, pt x) {
	pt d1 = b-a, d2 = x-a;
	sc det12 = det(d1, d2), dot12 = dot(d1, d2);
	if (det12 >= 0 && dot12 > 0) return 1;
	if (det12 > 0 && dot12 <= 0) return 2;
	if (det12 <= 0 && dot12 < 0) return 3;
	if (det12 < 0 && dot12 >= 0) return 4;
	return -1;
}

// comparador que ordena segun angulo alrededor de la recta ab
auto por_angulo(pt a, pt b) {
	return [=](pt x, pt y) {
		int cx = cuadrante(a,b,x), cy = cuadrante(a,b,y);
		if (cx != cy) return cx < cy;
		sc d = det(x-a, y-a);
		return d != 0 ? d > 0 : len_sq(x-a) < len_sq(y-a); // mas corto antes
	};
}

vector<pt> right_hull(vector<pt> a) {
	sort(all(a)); int j = 2;
	forr(i, 2, sz(a)) {
		while (j >= 2 && !ccw(a[j-2], a[j-1], a[i])) j--; // borra colineales
		// while (j >= 2 && cw(a[j-2], a[j-1], a[i])) j--; // no borra
		a[j++] = a[i];
	} a.resize(j); return a;
}

vector<pt> chull(vector<pt> a) {
	if (sz(a) < 3) return a;
	auto r = right_hull(a); for (auto& p : a) p = -1 * p;
	auto l = right_hull(a); for (auto& p : l) p = -1 * p;
	r.pp(); l.pp(); r.insert(end(r), all(l)); return r;
}

int solve_lado(pt q1, pt q2, vector<pt> const& ps) {

	int semip = 0;
	int lado1 = 0;
	int lado2 = 0;

	forn(i, sz(ps)) {
		if (ccw(q2, q1, ps[i])) semip++;
		if (en_semi(q1, q1+(q1-q2), ps[i])) lado1++;
		if (en_semi(q2, q2+(q2-q1), ps[i])) lado2++;
	}

	return max(semip+lado1, semip+lado2);
}

int solve_angulo(pt q1, pt q2, pt q3, vector<pt> ps) {
	auto en_region = [&](pt p) {
		return cw(q2, q3, p)
		    || ccw(q2, q1, p)
		    || en_semi(q2, q2+(q2-q1), p)
		    || en_semi(q2, q2+(q2-q3), p);
	};

	ps.erase(remove_if(all(ps), [&](pt p) { return not en_region(p); }), ps.end());

	sort(all(ps), por_angulo(q2, q1));

	int best = 0;
	int j = 0;
	forn(i,sz(ps)) {
		j = max(j, i+1);
		for (; j < sz(ps); ++j) {
			bool bueno = ccw(q2, ps[i], ps[j])
			          || en_semi(q2, ps[i], ps[j]);
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
			while(j-i < n && j < 3*n && (cw(ps[i], q, ps[j%n]) || en_semi(q, ps[i], ps[j%n]))) {
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

