/// Return `a` such that `f(a) <= f(b)`, with integers `l <= a, b < r`.
template<typename Int, class Function>
Int ternary_search_integer(Int l, Int r, Function f) {
	while (r - l >= 3) {
		const Int third = (r - l) / 3, m1 = l + third, m2 = r - third;
		if (f(m1) > f(m2)) {l = m1 + 1;} else {r = m2;}
	}
	if (r - l == 2 && f(l) > f(l + 1)) {++l;}
	return l;
}

/// Return `a` such that `f(a) <= f(b)`, with reals `l <= a, b < r`.
template<typename Real, class Function>
Real ternary_search_real(Real l, Real r, Function f, int iters=256){
	while (iters--) {
		const Real third = (r - l) /3.0, m1 = l + third, m2 = r - third;
		if (f(m1) > f(m2)) {l = m1;} else {r = m2;}
	}
	return l;
}
