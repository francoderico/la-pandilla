// https://codeforces.com/group/XrhoJtxCjm/contest/422671/problem/H
#include<bits/stdc++.h>

using namespace std;

#define forr(i,a,b)for(int i=int(a);i<int(b);++i)
#define forn(i,n)forr(i,0,n)
#define dforr(i,a,b)for(int i=int(b)-1;i>=int(a);--i)
#define dforn(i,n)dforr(i,0,n)
#define db(v)(cerr<<#v" = "<<v<<'\n')
#define nn cout<<'\n'
#define sz(v)(int((v).size()))
#define all(v)(v).begin(),(v).end()
#define pb push_back
#define pp pop_back
#define fst first
#define snd second

using ll=long long;
using ull=unsigned long long;
using ld=long double;
using pii=pair<int,int>;
using pll=pair<ll,ll>;

const int INF=1e9+100;
const ll MOD=1e9+7;
const ld EPS=1e-9;
const ld PI=acosl(-1);

const int BITCOUNT = 19;
const int MAXBIT = BITCOUNT-1;
const int MAXVAL = 1<<BITCOUNT;
const int MAXN = 5e5+100;

const int LOG2N  = BITCOUNT;
const int STLEN = 1<<LOG2N;

struct Mono {
	int x;
	static Mono zero() { return {0}; } // neutro de la suma
};
Mono operator+ (Mono a, Mono b) { return {a.x + b.x}; } // asociativo

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
	if (r-l == 1) return make_node(t->x + x, nullptr, nullptr);
	int m = (l+r)/2;
	auto lt = u_(t->l, l, m, i, x);
	auto rt = u_(t->r, m, r, i, x);
	return make_node(lt->x + rt->x, lt, rt);
}

int ql, qr;
Mono q_(N* t, int l, int r) {
	if (qr <= l || r <= ql) return Mono::zero();
	if (ql <= l && r <= qr) return t->x;
	int m = (l+r)/2;
	return q_(t->l, l, m) + q_(t->r, m, r);
}

// suma en rango:  t[l,r)
Mono query(N* t, int l, int r) { ql = l; qr = r; return q_(t, 0, STLEN); }

// asignacion en punto:  t[i]=x
N* update(N* t, int i, Mono x) { return u_(t, 0, STLEN, i, x); }



int query(N const* a, N const* b, int l, int r, int x, int bit) {
	assert(b->x.x - a->x.x > 0);
	if (r-l == 1) return l;
	int m = (l+r)/2;
	assert(bit >= 0);
	if (x&(1<<bit))
		if (b->l->x.x - a->l->x.x > 0)
			return query(a->l, b->l, l, m, x, bit-1);
		else
			return query(a->r, b->r, m, r, x, bit-1);
	else
		if (b->r->x.x - a->r->x.x > 0)
			return query(a->r, b->r, m, r, x, bit-1);
		else
			return query(a->l, b->l, l, m, x, bit-1);
}

int vidx = 0;
N* version[MAXN];

void op0(int x) {
	assert(x < STLEN);
	version[vidx+1] = update(version[vidx], x, {1});
	vidx+=1;
}

int op1(int l, int r, int x) {
	assert((x>>BITCOUNT) == 0);
	assert(r <= vidx);
	return query(version[l], version[r], 0, STLEN, x, BITCOUNT-1);
}

void op2(int k) {
	assert(k <= vidx);
	vidx -= k;
}

void solve(){
	int m;
	cin >> m;

	version[0] = &empty_node;

	forn(_, m) {
		int t; cin >> t;
		if (t == 0) {
			int x;cin>>x;
			op0(x);
		}
		if (t == 1) {
			int l,r,x;cin>>l>>r>>x;
			--l;
			cout << op1(l,r,x) << '\n';
		}
		if (t == 2) {
			int k;cin>>k;
			op2(k);
		}
	}

}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
