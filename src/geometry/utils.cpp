
// representamos poligonos con vector<pt>. son siempre contra-reloj.
// pt ("point") es un vector, sc ("scalar") es el tipo de sus componentes
using sc = ll; struct pt { sc x, y; };

// printear con cout / cerr
ostream&operator<<(ostream&o,pt p){return o<<"("<<p.x<<", "<<p.y<<")";}

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

void borrar_consecutivos_colineales(vector<pt>& a) {
	int j = 1;
	forr(i, 1, sz(a))
		if (!en_recta(a[i], a[j-1], a[(i+1)%sz(a)]))
			a[j++] = a[i];
	a.resize(j);
}

vector<pt> right_hull(vector<pt> ps) {
	if (sz(ps) <= 3) return ps;
	sort(all(ps)); int j=2;
	forr(i,2,sz(ps)) {
		while (j>=2 && !ccw(ps[j-2], ps[j-1], ps[i])) j--; // borra colineales
		// while (j>=2 && cw(ps[j-2], ps[j-1], ps[i])) j--; // no borra
		ps[j++] = ps[i];
	} ps.resize(j); return ps;
}

// O(NlogN) -- borra colineales (cambiar right_hull para no borrar)
vector<pt> chull(vector<pt> ps) {
	if (sz(ps) <= 3) return ps;
	auto ls = right_hull(ps); for (auto& p : ps) p = -1 * p;
	auto rs = right_hull(ps); for (auto& p : rs) p = -1 * p;
	ls.pp(); rs.pp(); ls.insert(end(ls), all(rs)); return ls;
}

// check point-in-poly O(logN) -- incluye el borde
// falla si no es convexo o hay 3 puntos colineales
bool poligono_contiene(vector<pt> const& a, pt p) {
	if (cw(a[0], a[1], p) || ccw(a[0], a.back(), p)) return false;
	int lo = 1, hi = sz(a)-1; while (hi - lo > 1) {
	int mi = (hi+lo)/2; if (ccw(a[0], a[mi], p)) lo = mi; else hi = mi; }
	return !cw(a[lo], a[hi], p);
}
