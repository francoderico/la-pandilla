// Minimo de `f` en `(l,r)`.
template<class Fun>ll ternary(Fun f, ll l, ll r) {
	for (ll d = r-l; d > 2; d = r-l) {
		ll a = l + d/3, b = r - d/3;
		if (f(a) > f(b)) l = a; else r = b;
	}
	return l + 1;
}
template<class Fun>double ternary(Fun f, double l, double r, int iters){
	while (iters--) {
		double d = r-l, a = l + d/3, b = r - d/3;
		if (f(a) > f(b)) l = a; else r = b;
	}
	return (l+r)/2;
}
