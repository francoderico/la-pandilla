
struct Lazy {
	// TODO agregar data
};

struct Mono {
	// TODO agregar data
	Lazy lazy;
	static Mono zero() { return ; /* TODO */ }
	bool has_lazy() { return ; /* TODO */ }
	void add_lazy(Lazy l) { /* TODO */ }
	void clear_lazy() { /* TODO */ }
	void apply_lazy(int l, int r) { /* TODO */ }
};

Mono operator+ (Mono a, Mono b) {
	assert(!a.has_lazy());
	assert(!b.has_lazy());
	return ; // TODO
}

struct SegtreeLazy {
	static constexpr int log2n = 17; // TODO
	static constexpr int ln = 1<<log2n;
	static constexpr int sz = ln<<1;

	vector<Mono> data;

	SegtreeLazy() : data(sz) {
	}

	// O(N)
	// inicia la estructura
	void init_all() {
		forn(i, sz) data[i] = Mono::zero();
	}

	// O(1)
	// asigna un valor sin actualizar la estructura
	// se usa con init_inner para hacer O(N) point updates en O(N)
	void assign_unsafe(int i, Mono x) {
		i += ln; data[i] = x;
	}

	// O(N)
	// recalcula todos los nodos internos de la estructura
	// NO TOMA EN CUENTA LAZY UPDATES PENDIENTES
	void init_inner() {
		dforr(i, 1, ln)
			data[i] = data[i*2] + data[i*2+1];
	}

	// O(logN)
	// update en rango
	void update(int l, int r, Lazy x) {
		ql = l; qr = r;
		u_(1, 0, ln, x);
	}

	// O(logN)
	// query en rango
	Mono query(int l, int r) {
		ql = l; qr = r;
		return q_(1, 0, ln);
	}

	private:

	int ql, qr;

	void p_(int i, int l, int r) {
		if (!data[i].has_lazy()) return;
		data[i].apply_lazy(l, r);
		if (i < ln) {
			data[2*i].add_lazy(data[i].lazy);
			data[2*i+1].add_lazy(data[i].lazy);
		}
		data[i].clear_lazy();
	}

	Mono q_(int i, int l, int r) {
		if (l == r) return Mono::zero();
		p_(i,l,r);
		if (r <= ql || qr <= l) return Mono::zero();
		if (ql <= l && r <= qr) return data[i];
		int m = (l+r)/2;
		return q_(i*2,l,m) + q_(i*2+1,m,r);
	}

	void u_(int i, int l, int r, Lazy x) {
		if (l == r) return;
		p_(i,l,r);
		if (r <= ql || qr <= l) return;
		if (ql <= l && r <= qr) {
			data[i].add_lazy(x);
			p_(i,l,r);
			return;
		}
		int m = (l+r)/2;
		u_(i*2,l,m,x); u_(i*2+1,m,r,x);
		data[i] = data[2*i] + data[2*i+1];
	}
};
