
// representamos poligonos con vector<pt>
// los poligonos son siempre contra-reloj

using Sc = ll; // scalar, asi se puede cambiar por double u otra cosa si hace falta
struct pt { Sc x, y; };

// rota un punto 90 grados contra-reloj respecto al origen
pt girar(pt p) { return {-p.y, p.x}; }

pt operator+ (pt const& a, pt const& b) { return {a.x + b.x, a.y + b.y}; } // suma
pt operator- (pt const& a, pt const& b) { return {a.x - b.x, a.y - b.y}; } // diferencia
pt operator* (Sc const& x, pt const& p) { return {x * p.x, x * p.y}; } // producto por un escalar
bool operator<(pt const& a, pt const& b) { return a.y != b.y ? a.y < b.y : a.x < b.x; } // ordena por y, desempata en x
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
// responde si el punto o pertence a la semirrecta ab
bool en_semirrecta(pt const& o, pt const& a, pt const& b) { return det(a-o, b-o) == 0 && dot(a-o, b-o) >= 0; }

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

// printear con cout / cerr
template<typename T> T& operator << (T& o, pt const& p) {
	return o << "(" << p.x << ", " << p.y << ")";
}

// recta definida por los x tal que dot(x,perp)==valor
// osea perp es perpendicular a la recta
struct linea {
	pt perp; ll valor;
	pt tang() const { return girar(perp); } // vector tangente
	bool contiene(pt p) { return dot(perp, p) == valor; }
};

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
		while (j >= 2 && not ccw(ps[j-2], ps[j-1], ps[i])) j--;
		ps[j++] = ps[i];
	}
	ps.resize(j);
	return ps;
}
