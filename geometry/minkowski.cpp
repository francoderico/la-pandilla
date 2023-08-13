
auto orden_radial = por_angulo(pt{0,0}, pt{1,0});

vector<pt> offsets(vector<pt> const& a) {
	vector<pt> da(sz(a));
	forn(i, sz(a)-1) da[i] = a[i+1] - a[i];
	da.back() = a[0] - a.back();
	rotate(begin(da), min_element(all(da), orden_radial), end(da));
	return da;
}

// Minkowski-sum of convex polygons
vector<pt> minkowski(vector<pt> const& a, vector<pt> const& b) {

	vector<pt> da = offsets(a), db = offsets(b);
	vector<pt> dc(sz(da)+sz(db));
	merge(all(da), all(db), begin(dc), orden_radial);

	vector<pt> c(sz(dc));
	c[0] = *min_element(all(a)) + *min_element(all(b));
	forn(i, sz(c)-1) c[i+1] = c[i] + dc[i];

	borrar_colineales(c);

	return c;
}
