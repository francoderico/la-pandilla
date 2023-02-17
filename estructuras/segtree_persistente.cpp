#include<bits/stdc++.h>

const int LOG2N  = 19; // ceil(log2(MAXN))
const int STLEN = 1<<LOG2N;

struct Mono {
	// TODO agregar data
	static Mono zero() { /* TODO */ } // neutro de la suma
};
Mono operator+ (Mono a, Mono b) { /* TODO */ } // asociativo

struct N {
	N(Mono x_, N* l_, N* r_)
	: x{x_}, l{l_}, r{r_} {}
	Mono x; N* l; N* r;
};
N empty_node(Mono::zero(), &empty_node, &empty_node);

// optimizacion: >30% mas rapido que 'new N(x,l,r)'
deque<N> st_alloc;
N* make_node(Mono x, N* l, N* r) {
	st_alloc.emplace_back(x, l, r);
	return &st_alloc.back();
}

N* u_(N* t, int l, int r, int i, Mono x) {
	if (i+1 <= l || r <= i) return t;
	if (r-l == 1) return make_node(x, nullptr, nullptr);
	int m = (l+r)/2;
	auto lt = u_(t->l, l, m, i, x);
	auto rt = u_(t->r, m, r, i, x);
	return make_node(lt->x + rt->x, lt, rt);
}

int ql, qr;
Mono q_(N* t, int l, int r) {
	if (qr <= l || r <= ql) return Mono::zero();
	if (l <= ql && qr <= r) return t->x;
	int m = (l+r)/2;
	return q_(t->l, l, m) + q_(t->r, m, r);
}

// suma en rango:  t[l,r)
Mono query(N* t, int l, int r) { ql = l; qr = r; return q_(t, 0, STLEN); }

// asignacion en punto:  t[i]=x
N* update(N* t, int i, Mono x) { return u_(t, 0, STLEN, i, x); }

/* uso:
auto t = &empty_node;
t = update(t, 0, Mono{10});
t = update(t, 5, Mono{5});
auto x = query(t, 0, 5); // devuelve Mono{10}
auto y = query(t, 0, 6); // devuelve Mono{10} + Mono{5}
auto z = query(t, 1, 6); // devuelve Mono{5}
*/
