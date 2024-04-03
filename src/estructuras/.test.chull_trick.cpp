// https://codeforces.com/gym/105053/problem/A
#include <bits/stdc++.h>
using namespace std;
#define forr(i,a,b) for(int i=int(a);i<int(b);++i)
#define forn(i,n) forr(i,0,n)
#define dforr(i,a,b) for(int i=int(b)-1;i>=int(a);--i)
#define dforn(i,n) dforr(i,0,n)
#define fore(e,c) for(const auto &e : (c))
#define db(v) cerr<<#v" = "<<(v)<<'\n'
#define sz(v) (int(v.size()))
#define all(v) begin(v), end(v)
#define pb push_back
#define pp pop_back
#define fst first
#define snd second
using ll = long long;
using ull = unsigned ll;
using ld = long double;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using veci = vector<int>;
using vecll = vector<ll>;
using vecb = vector<bool>;
using vecveci = vector<veci>;
template<class T>ostream&operator<<(ostream&o,vector<T>const&v){o<<"[ ";for(auto const&x:v)o<<x<<" ";return o<<"]";}
template<class T,class U>ostream&operator<<(ostream&o,pair<T,U>const&p){return o<<"("<<p.fst<<", "<<p.snd<<")";}
template<class T>void maxa(T&x,T const&y){  x=max(x,y);  }
template<class T>void mina(T&x,T const&y){  x=min(x,y);  }
template<class T>void sort2(T&x,T&y){  if(y<x)swap(x,y);  }
template<class T>void sort3(T&x,T&y,T&z){  sort2(x,y);sort2(y,z);sort2(x,y);  }

void solve();
void global_init();

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t = 1;
	global_init();
	forn(_,t) solve();
}


const ll MAXN = -1;
const ll INF = 1e18+100;
const ll MOD = 1000000007; /* NTT prime: 998244353 */
const ld EPS = 1e-9;
const ld PI = acosl(-1);

struct line { int a, b; }; // y = ax + b

vector<line> cht(vector<line> a) {
	sort(all(a), [](line x, line y) {
		return make_pair(x.a, x.b) < make_pair(y.a, y.b); });
	vector<line> b = {a[0]};
	forr(i, 1, sz(a)) { line z = a[i];
		if (b.back().a == z.a) b.pp();
		while (sz(b) >= 2) { line x = b[sz(b)-2], y = b[sz(b)-1];
			if (ll(x.b-y.b)*(z.a-x.a) < ll(x.b-z.b)*(y.a-x.a)) break;
			b.pp();
		}
		b.pb(z);
	}
	return b;
}

double intersect(line x, line y) {
	return double(x.b-y.b) / double(y.a-x.a);
}

vector<double> points(vector<line> const& a) {
	vector<double> b;
	forr(i,1,sz(a)) b.pb(intersect(a[i-1], a[i]));
	return b;
}

double eval(line a, double x) {
	return a.a * x + a.b;
}

double eval(vector<line> const& a, double x) {
	int lo = 0, hi = sz(a);
	while (hi - lo > 1) {
		int mi = (hi + lo) / 2;
		if (intersect(a[mi-1], a[mi]) < x) {
			lo = mi;
		} else {
			hi = mi;
		}
	}
	return eval(a[lo], x);
}

void global_init() {

}

void solve() {

	int n;
	cin >> n;

	vector<line> top, bottom, left, right;

	forn(i, n) {
		int x, y, vx, vy;
		cin >> x >> y >> vx >> vy;
		right .pb({ vx, x});
		left  .pb({-vx,-x});
		top   .pb({ vy, y});
		bottom.pb({-vy,-y});
	}

	right  = cht(right);
	left   = cht(left);
	top    = cht(top);
	bottom = cht(bottom);

	auto calc = [&](double t) {
		double w = eval(right, t) - (-eval(left,   t));
		double h = eval(top,   t) - (-eval(bottom, t));
		return w * h;
	};

	double ans = calc(0);

	for (auto c : {right, left, top, bottom}) {
		for (double t : points(c)) {
			if (t <= 0) continue;
			ans = min(ans, calc(t));
		}
	}

	cout << setprecision(10) << fixed << ans << "\n";

}

// ¿What is CROTOLAMO? -----> https://codeforces.com/blog/entry/114028
