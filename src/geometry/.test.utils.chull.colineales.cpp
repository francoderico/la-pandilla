// https://cses.fi/problemset/task/2195/
#include <bits/stdc++.h>
using namespace std;

#define forr(i,a,b) for(int i=int(a);i<int(b);++i)
#define forn(i,n) forr(i,0,n)
#define sz(v) (int(v.size()))
#define all(v) begin(v), end(v)
#define pp pop_back

typedef long long ll;

const ll MAXN = 2e5+100;

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

// el giro a hacia b con centro en o es contra-reloj
bool ccw(pt o, pt a, pt b) { return det(a-o, b-o) > 0; }
bool cw(pt o, pt a, pt b) { return det(a-o, b-o) < 0; }

vector<pt> right_hull(vector<pt> a) {
	sort(all(a)); int j = 2;
	forr(i, 2, sz(a)) {
		// while (j >= 2 && !ccw(a[j-2], a[j-1], a[i])) j--; // borra colineales
		while (j >= 2 && cw(a[j-2], a[j-1], a[i])) j--; // no borra
		a[j++] = a[i];
	} a.resize(j); return a;
}

vector<pt> chull(vector<pt> a) {
	if (sz(a) < 3) return a;
	auto r = right_hull(a); for (auto& p : a) p = -1 * p;
	auto l = right_hull(a); for (auto& p : l) p = -1 * p;
	r.pp(); l.pp(); r.insert(end(r), all(l)); return r;
}


void solve() {
	int n; cin >> n;
	vector<pt> ps(n); forn(i, n) cin >> ps[i].x >> ps[i].y;
	vector<pt> ch = chull(ps);
	cout << sz(ch) << "\n";
	for (auto p : ch) cout << p.x << " " << p.y << "\n";
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	solve();
}
