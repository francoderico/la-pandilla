// https://codeforces.com/gym/101845/problem/D
#include <bits/stdc++.h>
using namespace std;

#define forr(i,a,b) for(int i=(a);i<int(b); ++i)
#define forn(i,n) forr(i,0,n)
#define dforr(i,a,b) for(int i =(b)-1; i>=int(a);--i)
#define dforn(i,n) dforr(i,0,n)
#define db(v) cerr<<#v"= " << (v)<<'\n'

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

const ll MAXN = 2e5+100;
const ll MAXM = 2e5+100;
const ll INF = 1e18 + 100;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;
const ld PI = acosl(-1);


struct Query {
	int l,r;
	int idx;
	ll ord; // para usar con el hilbert
};

struct pt{
	ld x,y;
	pt&operator-=(const pt&t){
		x-=t.x;
		y-=t.y;
		return *this;
	}
	pt operator-(const pt&t)const{
		return pt(*this)-=t;
	}
};

int n,m;
pt ps[MAXN];

ld cross(pt a,pt b){
	return a.x*b.y-a.y*b.x;
}

ld signed_area_par(pt p1,pt p2,pt p3){
	return cross(p2-p1,p3-p2);
}

ld triang(pt p1,pt p2,pt p3){
	return abs(signed_area_par(p1,p2,p3))/2.0;
}




void sort_queries_classic(vector<Query>& qs, int n) {
	int const MO = int(sqrt(ld(n)))+1;
	sort(all(qs), [MO](Query const& a, Query const& b) {
		int ba=a.l/MO, bb=b.l/MO;
		if (ba!=bb) return ba<bb;
		return ba&1 ? a.r<b.r : a.r>b.r;
		// return a.r < b.r; // peor constante
	});
}





ll inv_hilbert(int x, int y, int mid) {
	ll acc = 0;
	auto step = [&](int x_, int y_, ll k) {
		x = x_; y = y_; acc += k * mid * mid; mid /= 2;
	};
	while (1) {
		if (mid == 0) return acc;
		if (x <  mid && y <  mid) { step(y, x, 0); continue; }
		if (x <  mid && y >= mid) { step(x, y-mid, 1); continue; }
		if (x >= mid && y >= mid) { step(x-mid, y-mid, 2); continue; }
		if (x >= mid && y <  mid) { step(mid-1-y, 2*mid-1-x, 3); continue; }
	}
}
// ordena las queries para responder en O(N*sqrt(Q))
void sort_queries_hilbert(vector<Query>& qs, int n) {
	int lg = __lg(2*n-1)-1; // esto es techo(log2(n))-1
	forn(i, sz(qs)) qs[i].ord = inv_hilbert(qs[i].l, qs[i].r, 1<<lg);
	sort(all(qs), [](Query const& a, Query const& b) { return a.ord < b.ord; });
}




void answer_queries(vector<Query> const& qs) {

	ld area_total = 0;
	forr(i,2,n) area_total += triang(ps[0], ps[i-1], ps[i]);

	ld best = 0;
	ld area = 0;

	int l=0, r=1;
	forn(i, sz(qs)) {
		while (l > qs[i].l) { area+=triang(ps[l-1],ps[l],ps[r]); --l; }
		while (r < qs[i].r) { area+=triang(ps[l],ps[r],ps[r+1]); ++r; }
		while (l < qs[i].l) { area-=triang(ps[l],ps[l+1],ps[r]); ++l; }
		while (r > qs[i].r) { area-=triang(ps[l],ps[r-1],ps[r]); --r; }

		ld gano = min(area, area_total-area);
		best = max(best, gano);
	}

	cout<<fixed<<setprecision(9)<<best<<'\n';
}





int main() {

	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cin>>n>>m;
	forn(i,n) cin>>ps[i].x>>ps[i].y;

	vector<Query> qs(m);
	forn(i,m){
		auto& l = qs[i].l;	auto& r = qs[i].r;
		cin>>l>>r; l--; r--;
		if (l > r) swap(l, r);
	}

	sort_queries_classic(qs, n);
	// sort_queries_hilbert(qs, n);

	answer_queries(qs);
}
