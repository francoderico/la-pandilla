struct Mono { /* TODO */ static Mono zero() { /* TODO */ } };
Mono operator+ (Mono a, Mono b) { /* TODO */ }
struct Segtree {
	int len; vector<Mono> data;
	void init(Mono* a, int n) { assert(n>0); // O(n+len)
		len=1<<(31-__builtin_clz(2*n-1));
		data.assign(len*2, Mono::zero());
		if (a) forn(i, n) data[i+len] = a[i];
		dforr(i, 1, len) data[i] = data[i*2] + data[i*2+1];
	}
	void update(int i, Mono x) {
		i += len; data[i] = x;
		while (i /= 2) data[i] = data[i*2] + data[i*2+1];
	}
	Mono query(int l, int r) { ql = l; qr = r; return q_(1, 0, len); }
	int ql, qr;
	Mono q_(int i, int l, int r) {
		if (r <= ql || qr <= l) return Mono::zero();
		if (ql <= l && r <= qr) return data[i];
		int m = (l+r)/2;
		return q_(i*2,l,m) + q_(i*2+1,m,r);
	}
};
