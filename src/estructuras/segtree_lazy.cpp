struct Lazy { /* TODO */
	static Lazy zero() { /* TODO */ }
	bool is_zero() { /* TODO */ } };
struct Mono { /* TODO */
	static Mono zero() { /* TODO */ }
	void apply_lazy(Lazy d, int l, int r) { /* TODO */ } };
Lazy operator+ (Lazy a, Lazy b) { /* TODO */ }
Mono operator+ (Mono a, Mono b) { /* TODO */ }
struct SegtreeLazy {
	int len; vector<Mono> data; vector<Lazy> lazy;
	void init(Mono* a, int n) { assert(n>0); // O(n+len)
		len=1<<(31-__builtin_clz(2*n-1));
		data.assign(2*len, Mono::zero());
		lazy.assign(2*len, Lazy::zero());
		if (a) forn(i, n) data[i+len] = a[i];
		dforr(i, 1, len) data[i] = data[i*2] + data[i*2+1];
	}
	void update(int l, int r, Lazy x) { ql = l; qr = r; u_(1, 0, len, x); }
	Mono query(int l, int r) { ql = l; qr = r; return q_(1, 0, len); }
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
