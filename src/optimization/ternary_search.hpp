/// Return `a` such that `f(a) <= f(b)`, with integers `l <= a, b < r`.
template<class Function>
ll ternary_search_integer(ll l, ll r, Function f) {
	while (r - l >= 3) {
		const ll third = (r - l) / 3, m1 = l + third, m2 = r - third;
		if (f(m1) > f(m2)) {l = m1 + 1;} else {r = m2;}
	}
	if (r - l == 2 && f(l) > f(l + 1)) {++l;}
	return l;
}

/// Return `a` such that `f(a) <= f(b)`, with reals `l <= a, b < r`.
template<class Function>
double ternary_search_real(double l, double r, Function f, int iters=256){
	while (iters--) {
		const double third = (r - l) / 3.0, m1 = l + third, m2 = r - third;
		if (f(m1) > f(m2)) {l = m1;} else {r = m2;}
	}
	return l;
}
