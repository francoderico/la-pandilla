/// Solves the system of inequalities determined by `a*x <= b` and `x >= 0`
/// with a solution that maximizes the objective function `c*x`.
///
/// More precisely, returns a pair `{z, s}` such that `z = c*s` is the biggest
/// possible value the objective function can reach with an input such that
/// `a*s <= b` and `s >= 0`, if such solution exists. If no solution exists,
/// returns `{nan, {}}`. If the objective function can get infintely big,
/// returns `{inf, {}}`.
template<typename Real=double>
pair<Real, vector<Real>> simplex(
	vector<vector<Real>>a, vector<Real>b, vector<Real>c, const Real eps=EPS
) {
	const int n = sz(b), m = sz(c);
	vector<int> xs(m), ys(n);
	iota(all(xs), 0), iota(all(ys), m);
	Real z = 0.0;
	const auto pivot = [&] (const int x, const int y) {
		swap(xs[y], ys[x]);
		b[x] /= a[x][y];
		forn(i, m) {if (i != y) {a[x][i] /= a[x][y];}}
		a[x][y] = 1 / a[x][y];
		forn(i, n) {
			if (i != x && abs(a[i][y]) > eps) {
				b[i] -= a[i][y] * b[x];
				forn(j, m) {if (j != y) {a[i][j] -= a[i][y] * a[x][j];}}
				a[i][y] *= -a[x][y];
			}
		}
		z += c[y] * b[x];
		forn(i, m) {if (i != y) {c[i] -= c[y] * a[x][i];}}
		c[y] = -c[y] * a[x][y];
	};
	while (true) {
		auto it = min_element(all(b));
		if (*it >= -eps) {break;}
		const int x = int(it - b.begin());
		it = find_if(all(a[x]), [&](const Real val) {return val < -eps;});
		const int y = int(it - a[x].begin());
		if (y == m) {return {numeric_limits<Real>::quiet_NaN(), {}};}
		pivot(x, y);
	}
	while (true) {
		auto it = max_element(all(c));
		if (*it <= eps) {break;}
		const int y = int(it - c.begin());
		int x = -1;
		forn(i, n) {
			if (a[i][y] > eps && (x == -1 || b[i] * a[x][y] < b[x] * a[i][y])) {
				x = i;
			}
		}
		if (x == -1) {return {numeric_limits<Real>::infinity(), {}};}
		pivot(x, y);
	}
	vector<Real> sol(m);
	forn(i, n) {if (ys[i] < m) {sol[ys[i]] = b[i];}}
	return {z, sol};
}
