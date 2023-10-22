using dbl = double;

template<class Fun> dbl simpson(Fun f, dbl a, dbl b, int n=1e4) {
	int m = 2 * n; // Integra `f` en `[a, b]` llamandola `2 * n` veces.
	dbl h = (b - a) / m, s = f(a);
	forr(i, 1, m) s += f(a + i * h) * ((i % 2) ? 4 : 2);
	return (s + f(b)) * h / 3;
}

template<class Fun> class Simpson {
	Fun f; // Integra `f` en `[a, b]` recursivamente hasta que la aprox es buena.
	dbl mw, meps; // Mayor ancho donde parar y menor epsilon posible.
	tuple<dbl, dbl, dbl> simpson(dbl a, dbl b, dbl fa, dbl fb) const {
		dbl m = (a + b) / 2, fm = f(m);
		return {m, fm, (b - a) / 6 * (fa + 4 * fm + fb)};
	}
	dbl quad(dbl a, dbl m, dbl b, dbl fa, dbl fm, dbl fb, dbl s, dbl eps) const {
		auto [lm, flm, sl] = simpson(a, m, fa, fm);
		auto [rm, frm, sr] = simpson(m, b, fm, fb);
		dbl w = abs(b - a), delta = sl + sr - s;
		if (w <= mw && abs(delta) <= 15 * eps) return sl + sr + delta / 15;
		eps = max(eps / 2, meps);
		return (
			quad(a, lm, m, fa, flm, fm, sl, eps) +
			quad(m, rm, b, fm, frm, fb, sr, eps)
		);
	}
public:
	Simpson(Fun _f, dbl min_width=1e18, dbl min_eps=1e-19):
		f{_f}, mw{min_width}, meps{min_eps} {}
	dbl integrate(dbl a, dbl b, dbl eps=1e-10) const {
		dbl fa = f(a), fb = f(b);
		auto [m, fm, s] = simpson(a, b, fa, fb);
		return quad(a, m, b, fa, fm, fb, s, max(eps, meps));
	}
};
