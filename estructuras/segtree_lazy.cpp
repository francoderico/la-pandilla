struct Lazy {
	// TODO agregar data
	static Lazy zero() { /* TODO */ } // neutro de la suma
	bool is_zero() { /* TODO */ } // moralmente `*this == Lazy::zero()`
};
struct Mono {
	// TODO agregar data
	static Mono zero() { /* TODO */ } // neutro de la suma
	void apply_lazy(Lazy d, int l, int r) { /* TODO */ }
};
Lazy operator+ (Lazy a, Lazy b) { /* TODO */ } // asociativo
Mono operator+ (Mono a, Mono b) { /* TODO */ } // asociativo

struct SegtreeLazy {
	static constexpr int log2n = 17; // TODO
	static constexpr int len = 1<<log2n, sze = 1<<(log2n+1);
	vector<Mono> data; vector<Lazy> lazy;
	SegtreeLazy() : data(sze), lazy(sze) { }
	void init(Mono* a, int n) { // inicia con los valores dados O(n+len)
		forn(i, sze) data[i] = Mono::zero();
		forn(i, sze) lazy[i] = Lazy::zero();
		forn(i, n) data[i+len] = a[i];
		dforr(i, 1, len) data[i] = data[i*2] + data[i*2+1];
	}
	// range update O(log(len))
	void update(int l, int r, Lazy x) { ql = l; qr = r; u_(1, 0, len, x); }
	// range query O(log(len))
	Mono query(int l, int r) { ql = l; qr = r; return q_(1, 0, len); }
private:
	int ql, qr;
	void p_(int i, int l, int r) {
		if (lazy[i].is_zero()) return;
		if (i < len) {
			lazy[2*i] = lazy[2*i] + lazy[i];
			lazy[2*i+1] = lazy[2*i+1] + lazy[i];
		}
		data[i].apply_lazy(lazy[i], l, r);
		lazy[i] = Lazy::zero();
	}
	Mono q_(int i, int l, int r) {
		if (r <= ql || qr <= l) return Mono::zero();
		p_(i,l,r);
		if (ql <= l && r <= qr) return data[i];
		int m = (l+r)/2;
		return q_(i*2,l,m) + q_(i*2+1,m,r);
	}
	void u_(int i, int l, int r, Lazy x) {
		if (l == r) return;
		p_(i,l,r);
		if (r <= ql || qr <= l) return;
		if (ql <= l && r <= qr) {
			lazy[i] = lazy[i] + x;
			p_(i,l,r);
			return;
		}
		int m = (l+r)/2;
		u_(i*2,l,m,x); u_(i*2+1,m,r,x);
		data[i] = data[2*i] + data[2*i+1];
	}
};

