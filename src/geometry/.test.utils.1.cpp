// https://codeforces.com/gym/104114/problem/F
#include <bits/stdc++.h>
using namespace std;

#define forr(i,a,b) for(int i=int(a);i<int(b);++i)
#define forn(i,n) forr(i,0,n)
#define dforr(i,a,b) for(int i=int(b)-1;i>=int(a);--i)
#define dforn(i,n) dforr(i,0,n)
#define db(v) cerr<<#v" = "<<(v)<<'\n'
#define vecp(v) cerr<<#v<<" = "; for(auto ee:v)cerr<<ee<<' '; cerr<<'\n'
#define nn cout<<'\n'
#define sz(v) (int(v.size()))
#define all(v) v.begin(), v.end()
#define pb push_back
#define pp pop_back
#define fst first
#define snd second

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<ll> vll;

const ll MAXN = 1e5+100;
const ll INF = 1e18+100;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;
const ld PI = acosl(-1);

using Sc = ll; // scalar, asi se puede cambiar por double u otra cosa si hace falta
struct pt { Sc x, y; };

pt girar(pt p ) { return {-p.y, p.x}; }

pt operator+ (pt const& a, pt const& b) { return {a.x + b.x, a.y + b.y}; } // suma
pt operator- (pt const& a, pt const& b) { return {a.x - b.x, a.y - b.y}; } // diferencia
pt operator* (Sc const& x, pt const& p) { return {x * p.x, x * p.y}; } // producto por un escalar
bool operator<(pt const& a, pt const& b) { return a.x != b.x ? a.x < b.x : a.y < b.y; }
bool operator==(pt const& a, pt const& b) { return a.x == b.x && a.y == b.y; }

Sc det(pt const& a, pt const& b) { return a.x*b.y - a.y*b.x; } // determinante
Sc dot(pt const& a, pt const& b) { return a.x*b.x + a.y*b.y; } // producto escalar
double len(pt const& p) { return hypot(p.x, p.y); } // modulo
Sc len_sq(pt const& p) { return dot(p, p); } // modulo cuadrado

bool ccw(pt const& o, pt const& a, pt const& b) { return det(a - o, b - o) > 0; } // responde si, centrado en o, ir de a hacia b es un giro contra-reloj
bool cw(pt const& o, pt const& a, pt const& b) { return det(a - o, b - o) < 0; } // responde si, centrado en o, ir de a hacia b es un giro como el reloj

template<typename T> T& operator << (T& o, pt const& p) { return o << "(" << p.x << ", " << p.y << ")"; } // printear con cout / cerr

struct linea {
	pt perp;
	ll valor;

	pt tang() const { return girar(perp); }
	bool contiene(pt p) { return dot(perp, p) == valor; }
};


int ft[MAXN+1]; // for more dimensions, make ft multi-dimensional
void upd(int i0, int v){ // add v to i0th element (0-based)
	// add extra fors for more dimensions
	for(int i=i0+1;i<=MAXN;i+=i&-i)ft[i]+=v;
}

int get(int i0){ // get sum of range [0,i0)
	int r=0;
	// add extra fors for more dimensions
	for(int i=i0;i;i-=i&-i)r+=ft[i];
	return r;
}

int get_sum(int i0, int i1){ // get sum of range [i0,i1) (0-based)
	return get(i1)-get(i0);
}

ll run(vector<pt> ps, pt s, pt e) {
	memset(ft, 0, sizeof(ft));

	int const n = sz(ps);

	vector<int> perm1(n), perm2(n);
	forn(i,n) perm1[i] = perm2[i] = i;

	auto by_angle1 = [&ps](pt center) {
		return [center, &ps](int a, int b) {
			pt a_ = ps[a];
			pt b_ = ps[b];
			ll d = det(a_ - center, b_ - center);
			if (d == 0) {
				return len_sq(a_ - center) < len_sq(b_ - center);
			} else {
				bool cw = d < 0;
				return cw;
			}
		};
	};
	sort(all(perm1), by_angle1(e));


	auto by_angle2 = [&ps](pt center) {
		return [center, &ps](int a, int b) {
			pt a_ = ps[a];
			pt b_ = ps[b];
			ll d = det(a_ - center, b_ - center);
			if (d == 0) {
				return len_sq(a_ - center) > len_sq(b_ - center);
			} else {
				bool cw = d < 0;
				return cw;
			}
		};
	};
	sort(all(perm2), by_angle2(s));

	vector<int> iperm1(n), iperm2(n);
	forn(i,n) iperm1[perm1[i]] = i;
	forn(i,n) iperm2[perm2[i]] = i;

	ll res = 0;

	for (int i : perm1) {
		pt p = ps[i];
		int j = iperm2[i];
		res += get_sum(j+1, n);
		upd(j, 1);
	}

	return res;
}

void solve() {
	pt s;
	cin >> s.x >> s.y;

	pt e;
	cin >> e.x >> e.y;

	int n;
	cin >> n;

	vector<pt> ps(n);
	forn(i,n) cin >> ps[i].x >> ps[i].y;

	vector<pt> arriba;
	vector<pt> abajo;

	ll cant_izq = 0;
	ll cant_der = 0;

	forn(i, n) {
		ll d = det(ps[i] - s, e - s);
		if (d < 0) arriba.pb(ps[i]);
		if (d > 0) abajo.pb(ps[i]);
		if (d == 0) {
			ll x = dot(ps[i] - s, e-s);
			if (x < 0) cant_izq++;
			if (x > 0) cant_der++;
		}
	}

	ll result = 0;
	result += run(arriba, s, e);
	result += run(abajo,  e, s);
	result += (cant_izq-1) * cant_izq / 2;
	result += (cant_der-1) * cant_der / 2;

	cout << result << '\n';

}

int main(){
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();

	return 0;
}
 
