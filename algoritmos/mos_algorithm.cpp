
struct Query {
	int l,r;
	int idx;
	// ll ord; // para usar con el hilbert
};


// ordena las queries para responder en O((N+Q)*sqrt(N))
void sort_queries_classic(vector<Query>& qs, int n) {
	int const MO = int(sqrt(ld(n)))+1;
	sort(all(qs), [MO](Query const& a, Query const& b) {
		int ba=a.l/MO, bb=b.l/MO;
		if (ba!=bb) return ba<bb;
		return ba&1 ? a.r<b.r : a.r>b.r;
		// return a.r < b.r; // peor constante
	});
}


ll inv_hilbert(int x, int y, int mid) {
	ll acc = 0;
	auto step = [&](int x_, int y_, ll k) {
		x = x_; y = y_; acc += k * mid * mid; mid /= 2;
	};
	while (1) {
		if (mid == 0) return acc;
		if (x <  mid && y <  mid) { step(y, x, 0); continue; }
		if (x <  mid && y >= mid) { step(x, y-mid, 1); continue; }
		if (x >= mid && y >= mid) { step(x-mid, y-mid, 2); continue; }
		if (x >= mid && y <  mid) { step(mid-1-y, 2*mid-1-x, 3); continue; }
	}
}
// ordena las queries para responder en O(N*sqrt(Q))
void sort_queries_hilbert(vector<Query>& qs, int n) {
	int lg = __lg(2*n-1)-1; // esto es techo(log2(n))-1
	forn(i, sz(qs)) qs[i].ord = inv_hilbert(qs[i].l, qs[i].r, 1<<lg);
	sort(all(qs), [](Query const& a, Query const& b) { return a.ord < b.ord; });
}


void answer_queries(vector<Query> const& qs) {
	// TODO iniciar estado
	int l=0, r=0;
	forn(i, sz(qs)) {
		while (l > qs[i].l) { /* TODO expandir izq */ --l; }
		while (r < qs[i].r) { /* TODO expandir der */ ++r; }
		while (l < qs[i].l) { /* TODO reducir izq */ ++l; }
		while (r > qs[i].r) { /* TODO reducir der */ --r; }
		// TODO guardar resultado
		// p.ej: ans[qs[i].idx] = estado_actual
	}
}
