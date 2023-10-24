struct Entry {
	using It = set<Entry>::iterator;
	bool is_query;
	ll m, b; mutable It it, end;
	ll x;
};
bool operator< (Entry const& a, Entry const& b) {
	if (!b.is_query) return a.m < b.m;
	auto ni = next(a.it);
	if (ni == a.end) return false;
	auto const& c = *ni;
	return (c.b-a.b) < b.x * (a.m-c.m);
}
struct ChullTrick {
	using It = Entry::It;
	multiset<Entry> lines;
	bool covered(It it) {
		auto begin = lines.begin(), end = lines.end();
		auto ni = next(it);
		if (it == begin && ni == end) return false;
		if (it == begin) return ni->m==it->m && ni->b>=it->b;
		auto pi = prev(it);
		if (ni == end) return pi->m==it->m && pi->b>=it->b;
		return (it->m-pi->m)*(ni->b-pi->b) >= (pi->b-it->b)*(pi->m-ni->m);
	}
	bool add(ll m, ll b) {
		auto it = lines.insert(false);
		it->it = it; it->end = lines.end();
		if (covered(it)) { lines.erase(it); return false; }
		while (next(it) != lines.end() && covered(next(it))) lines.erase(next(it));
		while (it != lines.begin() && covered(prev(it))) lines.erase(prev(it));
		return true;
	}
	ll eval(ll x) {
		auto l = *lines.lower_bound({true, -1, -1, {}, {}, x});
		return l.m*x+l.b;
	}
};