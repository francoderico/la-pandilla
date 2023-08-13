#include <bits/stdc++.h>
using namespace std;

#define forr(i,a,b) for(int i=int(a);i<int(b);++i)
#define forn(i,n) forr(i,0,n)
#define dforr(i,a,b) for(int i=int(b)-1;i>=int(a);--i)
#define dforn(i,n) dforr(i,0,n)
#define fore(e,c) for(const auto &e : (c))
#define db(v) cerr<<#v" = "<<(v)<<'\n'
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

const ll MAXN = 2e5+100;
const ll INF = 1e18+100;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;
const ld PI = acosl(-1);

template<typename T>
ostream& operator<<(ostream& o, vector<T> const& v) {
	o << "[ ";
	for (auto const& x : v)
		o << x << " ";
	return o << "]";
}

template<typename T, typename U>
ostream& operator<<(ostream& o, pair<T, U> const& p) {
	return o
	<< "("
	<< p.fst
	<< ","
	<< " "
	<< p.snd
	<< ")"
	;
}

#include "utils.cpp"
#include "minkowski.cpp"

vector<pt> twice(vector<pt> a) {
	for (auto& p : a) p = 2*p;
	return a;
}

vector<pt> flip(vector<pt> a) {
	for (auto& p : a) p = (-1)*p;
	return a;
}

bool poly_contains(vector<pt> const& a, pt p) {
	if (cw(a[0], a[1], p)) return false;
	if (ccw(a[0], a.back(), p)) return false;
	int lo = 1;
	int hi = sz(a)-1;
	while (hi - lo > 1) {
		int mi = (hi+lo)/2;
		if (ccw(a[0], a[mi], p)) lo = mi;
		else                     hi = mi;
	}
	return !cw(a[lo], a[hi], p);
}

void solve() {
	int m1; cin >> m1;
	vector<pt> a(m1); forn(i, m1) cin >> a[i].x >> a[i].y;

	int m2; cin >> m2;
	vector<pt> b(m2); forn(i, m2) cin >> b[i].x >> b[i].y;

	int n; cin >> n;
	vector<pt> c(n); forn(i, n) cin >> c[i].x >> c[i].y;

	auto case1 = minkowski(twice(a), flip(b)); // middle a -> a = (b+c)/2 -> 2a = b+c -> 2a-b = c
	auto case2 = minkowski(twice(b), flip(a)); // middle b -> b = (a+c)/2 -> 2b = a+c -> 2b-a = c
	auto case3 = minkowski(a, b); // middle c -> c = (a+b)/2 -> 2c = a+b

	db(case3);

	string ans(n, 'N');
	forn(i, n) {
		if (poly_contains(case1, c[i]) || poly_contains(case2, c[i]) || poly_contains(case3, 2*c[i])) {
			ans[i] = 'Y';
		}
	}

	cout << ans << "\n";
}

int main(){
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
}
