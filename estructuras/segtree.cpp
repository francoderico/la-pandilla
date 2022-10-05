struct Mono {
	// TODO agregar data
	static Mono zero() { /* TODO */ } // neutro de la suma
};
Mono operator+ (Mono a, Mono b) { /* TODO */ } // asociativo

struct Segtree {
	static constexpr int log2n = 17; // TODO
	static constexpr int len = 1<<log2n, sze = 1<<(log2n+1);
	vector<Mono> data;
	Segtree() : data(sze) { }

	// inicia con los valores dados O(n+len)
	void init(Mono* a, int n) {
		forn(i, sze) data[i] = Mono::zero();
		forn(i, n) data[i+len] = a[i];
		dforr(i, 1, len) data[i] = data[i*2] + data[i*2+1];
	}

	// point update O(log(len))
	void update(int i, Mono x) {
		i += len; data[i] = x;
		while (i /= 2) data[i] = data[i*2] + data[i*2+1];
	}

	// range query O(log(len))
	Mono query(int l, int r) { ql = l; qr = r; return q_(1, 0, len); }

private:
	int ql, qr;
	Mono q_(int i, int l, int r) {
		if (r <= ql || qr <= l) return Mono::zero();
		if (ql <= l && r <= qr) return data[i];
		int m = (l+r)/2;
		return q_(i*2,l,m) + q_(i*2+1,m,r);
	}
};
