// CODEFORCES 102346F

#include <bits/stdc++.h>
using namespace std;

#define forr(i,a,b) for(int i =(a);i<int(b); ++i)
#define forn(i,n) forr(i,0,n)
#define dforr(i,a,b) for(int i =(b)-1;i>=int(a);--i)
#define dforn(i,n) dforr(i,0,n)
#define db(v) cerr << #v << " = " << (v) << "\n";
#define nn cout << "\n"
#define sz(v) (int((v).size()))
#define all(v) (v).begin(), (v).end()
#define pb push_back
#define pp pop_back
#define fst first
#define snd second

using ll = long long;
using ull = unsigned ll;
using ld = long double;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using vll = vector<ll>;

const ll MAXN = 2e5+100;
const ll INF = 1e18 +100;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;
const ld PI = acosl(-1);




struct Lazy {
	ll x;
	static Lazy zero() { return {0}; } // neutro de la suma
	bool is_zero() { return x == 0; } // moralmente `*this == Lazy::zero()`
};

struct Mono {
	ll x, c;
	static Mono zero() { return {INT_MAX, 0}; } // neutro de la suma
	void apply_lazy(Lazy d, int l, int r) { x += d.x; }
};

Lazy operator+ (Lazy a, Lazy b) { return {a.x + b.x}; } // asociativo
Mono operator+ (Mono a, Mono b) {
	if (a.x < b.x) return a;
	if (b.x < a.x) return b;
	return {a.x, a.c+b.c};
}


struct SegtreeLazy {
	static constexpr int log2n = 17;
	static constexpr int ln = 1<<log2n;
	static constexpr int sz = ln<<1;

	vector<Mono> data; vector<Lazy> lazy;
	SegtreeLazy() : data(sz), lazy(sz) { }

	// O(N)
	// inicia la estructura
	void init_all() {
		forn(i, sz) data[i] = Mono::zero();
		forn(i, sz) lazy[i] = Lazy::zero();
	}

	// O(1)
	// asigna un valor sin actualizar la estructura
	// se usa con init_inner para hacer O(N) point updates en O(N)
	// NO TOMA EN CUENTA LAZY UPDATES PENDIENTES
	void assign_unsafe(int i, Mono x) {
		i += ln; data[i] = x;
	}

	// O(N)
	// recalcula todos los nodos internos de la estructura
	// NO TOMA EN CUENTA LAZY UPDATES PENDIENTES
	void init_inner() {
		dforr(i, 1, ln)
			data[i] = data[i*2] + data[i*2+1];
	}

	// O(logN)
	// update en rango
	void update(int l, int r, Lazy x) {
		ql = l; qr = r;
		u_(1, 0, ln, x);
	}

	// O(logN)
	// query en rango
	Mono query(int l, int r) {
		ql = l; qr = r;
		return q_(1, 0, ln);
	}

	private:

	int ql, qr;

	void p_(int i, int l, int r) {
		if (lazy[i].is_zero()) return;
		if (i < ln) {
			lazy[2*i] = lazy[2*i] + lazy[i];
			lazy[2*i+1] = lazy[2*i+1] + lazy[i];
		}
		data[i].apply_lazy(lazy[i], l, r);
		lazy[i] = Lazy::zero();
	}

	Mono q_(int i, int l, int r) {
		if (l == r) return Mono::zero();
		p_(i,l,r);
		if (r <= ql || qr <= l) return Mono::zero();
		if (ql <= l && r <= qr) return data[i];
		int m = (l+r)/2;
		return q_(i*2,l,m) + q_(i*2+1,m,r);
	}

	void u_(int i, int l, int r, Lazy x) {
		if (l == r) return;
		p_(i,l,r);
		if (r <= ql || qr <= l) return;
		if (ql <= l && r <= qr) {
			lazy[i] = lazy[i] + x;
			p_(i,l,r);
			return;
		}
		int m = (l+r)/2;
		u_(i*2,l,m,x); u_(i*2+1,m,r,x);
		data[i] = data[2*i] + data[2*i+1];
	}
};




SegtreeLazy st;



struct rect { ll x0, y0, x1, y1; };

struct sweep { ll x0, x1, y, v; };

ll cant_ceros(int l, int r) {
	Mono res = st.query(l, r);
	if (res.x != 0) return 0;
	return res.c;
}

ll area_union(vector<rect> const& rects) {

	st.init_all();
	forn(i, st.ln) st.assign_unsafe(i, {0, 1});
	st.init_inner();

	vector<sweep> lines;

	for (rect r : rects) {
		lines.pb({r.x0, r.x1, r.y0, 1});
		lines.pb({r.x0, r.x1, r.y1, -1});
	}

	sort(all(lines), [](sweep a, sweep b){ return a.y < b.y; });

	assert(lines.back().v == -1);
 	assert(lines[0].v     ==  1);

	ll result = 0;
	forn(i, sz(lines)-1) {
		sweep s = lines[i];

		st.update(s.x0, s.x1, {s.v});

		ll c0 = cant_ceros(0, 1e5);
		ll ocupado = 100000ll - c0;

		ll y0 = lines[i].y;
		ll y1 = lines[i+1].y;
		ll dy = y1 - y0;

		result += ocupado * dy;
	}

	return result;
}

ll area(rect r)
{
    return llabs(ll(r.x1-r.x0) * ll(r.y1-r.y0));
}

int n;
vector<rect> rio;
int p; 
rect total;
ll t;


rect trim(rect r)
{
    rect ans;
    ans.x0 = max(r.x0, total.x0);
    ans.y0 = max(r.y0, total.y0);
    ans.x1 = min(r.x1, total.x1); 
    ans.y1 = min(r.y1, total.y1);
    
    return ans; 
}

bool anda(ll m)
{
    vector<rect> r;
    forn(i, n) r.pb(trim({rio[i].x0-m, rio[i].y0-m, rio[i].x1+m, rio[i].y1+m}));
    
    return area_union(r)*100 >= p*t;
}


int main() {
	// freopen("in.txt", "r", stdin);
	// freopen("out.txt", "w", stdout);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	// vector<rect> rectangulos = {
	// 	{0,0,   20,10},
	// 	{12,5,  18,15},
	// 	{11,9,  13,11},
	// };
	// db(area_union(rectangulos));
    
    cin >> n;
    rio.resize(n);
    forn(i, n)
    {
        cin >> rio[i].x0 >> rio[i].y0 >> rio[i].x1 >> rio[i].y1;
        
        if(rio[i].x0 > rio[i].x1 or rio[i].y0 > rio[i].y1)
        {
            swap(rio[i].x0, rio[i].x1);
            swap(rio[i].y0, rio[i].y1);
        }
    }
    
    cin >> p;
    cin >> total.x0 >> total.y0 >> total.x1 >> total.y1;
    t = area(total);
    
    ll a = 0, b = t;
    
    //FFFFFTTTT
    while(b-a > 1)
    {
        ll m = (a+b) / 2;
        
        if(anda(m)) b = m;
        else        a = m;
    }
    
    cout << b, nn;  //last T

	return 0;
}
