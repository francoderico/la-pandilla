/// Integrate `f` in the real interval `[a, b]` by dividing the integration
/// range into `n` equal subdivisions and approximating the integrand in each
/// of them with a parabola that passes through its endpoints and midpoint.
template<typename Real, class Function>
Real composite_simpson(
	const Real a, const Real b, Function f, const int n=1e4
) {
	const int m = 2 * n;
	const Real h = (b - a) / m;
	Real s = f(a);
	forr(i, 1, m) {s += f(a + i * h) * ((i & 1) ? 4.0 : 2.0);}
	return (s + f(b)) * h / 3.0;
}

/// Alternative integration method where the integration range is divided into
/// unequal subdivisions depending on some input parameters, which may result
/// in a faster and/or more precise approximation of the integral than the
/// simpler composite method as it uses fewer function evaluations in places
/// where the function is well approximated by a cubic function.
template<typename Real=double>
class AdaptativeSimpson {
	using function_type = function<Real(Real)>;
	// Function to integrate.
	function_type f;
	// Minimum necessary width where we can stop subdiving the integration range
	// if the error is small enough.
	const Real min_width;
	// Minimum acceptable tolerance. We need to provide it as the actual tolerance
	// we use gets divided in two every time the integration range is subdivided,
	// which may end up underflowing without a lower bound.
	const Real min_eps;
	/// Integrate `f` in `[a, b]` by approximating the integrand with a parabola.
	tuple<Real, Real, Real> simpson(
		const Real a, const Real b, const Real fa, const Real fb
	) const {
		const Real m = (a + b) / 2.0, fm = f(m);
		return {m, fm, (b - a) / 6.0 * (fa + 4.0 * fm + fb)};
	}
	/// Integrate `f` in `[a, b]` by subdiving the range into two half ranges if
	/// the range width or error are too big.
	///
	/// It retains the function values at the start, middle, and end of the
	/// intervals so as to not evaluate them again.
	Real quadrature(
		const Real a,
		const Real m,
		const Real b,
		const Real fa,
		const Real fm,
		const Real fb,
		const Real s,
		const Real eps
	) const {
		const auto [lm, flm, sl] = simpson(a, m, fa, fm);
		const auto [rm, frm, sr] = simpson(m, b, fm, fb);
		const Real width = abs(b - a), delta = sl + sr - s;
		if (width <= min_width && abs(delta) <= 15.0 * eps) {
			return sl + sr + delta / 15.0;
		}
		const Real next_eps = max(eps / 2.0, min_eps);
		return(
			quadrature(a, lm, m, fa, flm, fm, sl, next_eps)+
			quadrature(m, rm, b, fm, frm, fb, sr, next_eps)
		);
	}
public:
	AdaptativeSimpson(
		function_type _f,
		const Real _min_width=std::numeric_limits<Real>::infinity(),
		const Real _min_eps=1e-19
	): f(_f), min_width(_min_width), min_eps(_min_eps) {}
	/// Integrate `f` in the real interval `[a, b]` with a tolerance of `eps`.
	Real integrate(const Real a, const Real b, const Real eps=1e-10) const {
		const Real fa = f(a), fb = f(b);
		const auto [m, fm, s] = simpson(a, b, fa, fb);
		return quadrature(a, m, b, fa, fm, fb, s, max(eps,min_eps));
	}
};
