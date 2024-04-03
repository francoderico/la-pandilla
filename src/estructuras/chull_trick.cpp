struct line { int a, b; }; // y = ax + b
vector<line> cht(vector<line> a) {
	sort(all(a), [](line x, line y) {
		return make_pair(x.a, x.b) < make_pair(y.a, y.b); });
	vector<line> b = {a[0]};
	forr(i, 1, sz(a)) { line z = a[i];
		if (b.back().a == z.a) b.pp();
		while (sz(b) >= 2) { line x = b[sz(b)-2], y = b[sz(b)-1];
			if (ll(x.b-y.b)*(z.a-x.a) < ll(x.b-z.b)*(y.a-x.a)) break;
			b.pp();
		}
		b.pb(z);
	}
	return b;
}
