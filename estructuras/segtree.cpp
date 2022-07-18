template<typename Monoid>
struct Segtree {
	int const log2n, ln, sz;
	vector<Monoid> data;

	Segtree(int log2n)
		:log2n{log2n}
		,ln{1 << log2n}
		,sz{1 << (log2n+1)}
		,data(1 << (log2n+1))
		{}

	// O(N)
	// inicia la estructura
	void init() {
		forn(i, sz) data[i] = Monoid::zero();
	}

	// O(1)
	// asigna un valor sin actualizar la estructura
	// se usa con update_all para hacer O(N) point updates en O(N)
	void assign_no_update(int i, Monoid x) {
		i += ln; data[i] = x;
	}

	// O(N)
	// recalcula todos los nodos internos de la estructura
	void update_all() {
		for (int i = ln; --i;)
			data[i] = data[i*2] + data[i*2+1];
	}

	// O(logN)
	// update en punto
	void update(int i, Monoid x) {
		i += ln; data[i] = x;
		while (i /= 2)
			data[i] = data[i*2] + data[i*2+1];
	}

	// O(logN)
	// query en rango
	Monoid query(int l, int r) {
		ql = l; qr = r;
		return query_(1, 0, ln);
	}

private:
	int ql, qr;
	Monoid query_(int i, int l, int r) {
		if (ql <= l && r <= qr) return data[i];
		if (r <= ql || qr <= l) return Monoid::zero();
		int m = (l+r)/2;
		return query_(i*2,l,m) + query_(i*2+1,m,r);
	}
};
