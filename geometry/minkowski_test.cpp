#include <bits/stdc++.h>
using namespace std;

#define forr(i,a,b) for(int i=int(a);i<int(b);++i)
#define forn(i,n) forr(i,0,n)
#define sz(v) (int(v.size()))
#define all(v) begin(v), end(v)

typedef long long ll;

// representamos poligonos con vector<pt>
// los poligonos son siempre contra-reloj

using Sc = ll; // scalar, asi se puede cambiar por double u otra cosa si hace falta
struct pt { Sc x, y; };

pt operator+ (pt const& a, pt const& b) { return {a.x + b.x, a.y + b.y}; } // suma
pt operator- (pt const& a, pt const& b) { return {a.x - b.x, a.y - b.y}; } // diferencia
pt operator* (Sc const& x, pt const& p) { return {x * p.x, x * p.y}; } // producto por un escalar
bool operator<(pt const& a, pt const& b) { return a.y != b.y ? a.y < b.y : a.x < b.x; }
bool operator==(pt const& a, pt const& b) { return a.x == b.x && a.y == b.y; }

Sc det(pt const& a, pt const& b) { return a.x*b.y - a.y*b.x; } // determinante
Sc dot(pt const& a, pt const& b) { return a.x*b.x + a.y*b.y; } // producto escalar
double len(pt const& p) { return hypot(p.x, p.y); } // modulo
Sc len_sq(pt const& p) { return dot(p, p); } // modulo cuadrado

// responde si, centrado en o, ir de a hacia b es un giro contra-reloj
bool ccw(pt const& o, pt const& a, pt const& b) { return det(a - o, b - o) > 0; }
// responde si, centrado en o, ir de a hacia b es un giro como el reloj
bool cw(pt const& o, pt const& a, pt const& b) { return det(a - o, b - o) < 0; }
// responde si el punto o pertence a la recta ab
bool en_recta(pt const& o, pt const& a, pt const& b) { return det(a-o, b-o) == 0; }

// devuelve el cuadrante del angulo que
// forma el punto x con la semirrecta ab
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

// devuelve un comparador que ordena segun angulo
// alrededor de la recta ab
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

// Borra puntos consecutivos colineales
void borrar_colineales(vector<pt>& a) {
	int j = 1;
	forr(i, 1, sz(a))
		if (!en_recta(a[i], a[j-1], a[(i+1)%sz(a)]))
			a[j++] = a[i];
	a.resize(j);
}

auto orden_radial = por_angulo(pt{0,0}, pt{1,0});

vector<pt> offsets(vector<pt> const& a) {
	vector<pt> da(sz(a));
	forn(i, sz(a)-1) da[i] = a[i+1] - a[i];
	da.back() = a[0] - a.back();
	rotate(begin(da), min_element(all(da), orden_radial), end(da));
	return da;
}

// Minkowski-sum of convex polygons
vector<pt> minkowski(vector<pt> const& a, vector<pt> const& b) {

	vector<pt> da = offsets(a), db = offsets(b);
	vector<pt> dc(sz(da)+sz(db));
	merge(all(da), all(db), begin(dc), orden_radial);

	vector<pt> c(sz(dc));
	c[0] = *min_element(all(a)) + *min_element(all(b));
	forn(i, sz(c)-1) c[i+1] = c[i] + dc[i];

	borrar_colineales(c);

	return c;
}

vector<pt> twice(vector<pt> a) {
	for (auto& p : a) p = 2*p;
	return a;
}

vector<pt> flip(vector<pt> a) {
	for (auto& p : a) p = (-1)*p;
	return a;
}

bool poly_contains(vector<pt> const& a, pt p) {
	if (cw(a[0], a[1], p)) return false;
	if (ccw(a[0], a.back(), p)) return false;
	int lo = 1;
	int hi = sz(a)-1;
	while (hi - lo > 1) {
		int mi = (hi+lo)/2;
		if (!cw(a[0], a[mi], p)) lo = mi;
		else                     hi = mi;
	}
	return !cw(a[lo], a[hi], p);
}

void solve() {
	int m1; cin >> m1;
	vector<pt> a(m1); forn(i, m1) cin >> a[i].x >> a[i].y;

	int m2; cin >> m2;
	vector<pt> b(m2); forn(i, m2) cin >> b[i].x >> b[i].y;

	int n; cin >> n;
	vector<pt> c(n); forn(i, n) cin >> c[i].x >> c[i].y;

	auto case1 = minkowski(twice(a), flip(b)); // middle a -> a = (b+c)/2 -> 2a = b+c -> 2a-b = c
	auto case2 = minkowski(twice(b), flip(a)); // middle b -> b = (a+c)/2 -> 2b = a+c -> 2b-a = c
	auto case3 = minkowski(a, b); // middle c -> c = (a+b)/2 -> 2c = a+b

	string ans(n, 'N');
	forn(i, n) {
		if (poly_contains(case1, c[i]) || poly_contains(case2, c[i]) || poly_contains(case3, 2*c[i])) {
			ans[i] = 'Y';
		}
	}

	cout << ans << "\n";
}

int main(){
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
}
