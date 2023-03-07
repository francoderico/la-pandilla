// https://matcomgrader.com/problem/9553/looking-for-the-risk-factor/
#include<bits/stdc++.h>
using namespace std;

#define forr(i,a,b) for(int i = int(a);i<int(b);++i)
#define forn(i,n) forr(i,0,n)
#define dforr(i,a,b) for(int i=int(b)-1;i>=int(a);--i)
#define dforn(i,n) dforr(i,0,n)
#define fore(e,c) for(const auto&e : (c))
#define db(v) cerr<<#v<<" = "<<(v)<<'\n'
#define nn cout<<'\n'
#define sz(v) (int(v.size()))
#define all(v) begin(v), end(v)
#define pb push_back
#define pp pop_back
#define fst first
#define snd second

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

const ll MAXN = 1e5+100;
const ll INF = 1e18+100;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;
const ld PI = acosl(-1);

int criba[MAXN];

void crear_criba()
{
    forr(i, 2, MAXN) if(not criba[i]) for(ll j = 1LL*i*i; j < MAXN; j += i) criba[j] = i;
}

int max_p(int n)
{
    int ans = 0;

    while(criba[n]) ans = max(ans, criba[n]), n /= criba[n];
    if(n > 1) ans = max(ans, n);

    return ans;
}

#define oper(a, b) a+b
#define NEUT 0


const int LOG2N  = 17; // ceil(log2(MAXN))
const int STLEN = 1<<LOG2N;

struct Mono {
	int x;
	static Mono zero() { return {0}; } // neutro de la suma
};
Mono operator+ (Mono a, Mono b) { return {a.x+b.x}; } // asociativo

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
	if (ql <= l && r <= qr) return t->x;
	int m = (l+r)/2;
	return q_(t->l, l, m) + q_(t->r, m, r);
}

// suma en rango:  t[l,r)
Mono query(N* t, int l, int r) { ql = l; qr = r; return q_(t, 0, STLEN); }

// asignacion en punto:  t[i]=x
N* update(N* t, int i, Mono x) { return u_(t, 0, STLEN, i, x); }


N* node[MAXN];

void solve() {
    crear_criba();

    node[1] = &empty_node;

    forr(i, 2, MAXN)
    {
        int idx = max_p(i);
        int prev_val = query(node[i-1], idx, idx+1).x;
        node[i] = update(node[i-1], idx, {prev_val+1});
    }

    int q; cin >> q;
    forn(_, q)
    {
        int n, k; cin >> n >> k;

        cout << query(node[n], 0, k+1).x, nn;
    }
}


int main() {
	// freopen("input.txt", "r", stdin);
	// freopen("output.txt", "w", stdout);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
}
