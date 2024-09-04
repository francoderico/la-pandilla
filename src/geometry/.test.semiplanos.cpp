#include <bits/stdc++.h>
using namespace std;

#define forr(i,a,b) for(int i = int(a); i <int(b); ++i)
#define forn(i,n) forr(i,0,n)
#define dforr(i,a,b) for(int i = int(b)-1; i >= int(a); --i)
#define dforn(i,n) dforr(i,0,n)
#define fore(e,c) for(auto const& e :(c))
#define db(v) cerr<<#v " = "<<(v)<<"\n"
#define nn cout<<"\n"
#define sz(v) (int((v).size()))
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

const ll MAXN  =-1;
const ll INF = 1e18+100;
const ll MOD =1e9+7;
const double EPS = 1e-9;
const double PI =acos(-1);
const double DINF = 1e9;

using sc = double; struct pt { sc x, y; };

pt operator+(pt a, pt b) { return {a.x + b.x, a.y + b.y}; }
pt operator-(pt a, pt b) { return {a.x - b.x, a.y - b.y}; }
pt operator*(sc x, pt p) { return {x * p.x, x * p.y}; }
sc det(pt a, pt b) { return a.x*b.y - a.y*b.x; } // determinante
sc dot(pt a, pt b) { return a.x*b.x + a.y*b.y; } // producto escalar
sc len_sq(pt p) { return dot(p, p); } // modulo cuadrado
double len(pt p) { return sqrt(len_sq(p)); } // modulo
pt unit(pt p) { return (1/len(p)) * p; } // versor asociado

struct line {
	pt p, pq;
	line(pt p_, pt q_):p(p_),pq(q_-p_){}
	line() {}
};
bool parallel(line a, line b) {
	return abs(det(unit(a.pq),unit(b.pq)))<=EPS; // <=0 for int
}
pt intersect(line& a, line& b) {
	if(parallel(a, b))return {DINF, DINF};
	pt r = b.p+(det(a.p-b.p,a.pq)/det(b.pq,a.pq))*b.pq;
	return r;
}

struct halfplane : public line {
	double angle;
	halfplane(){}
	halfplane(pt a, pt b){p=a; pq=b-a; angle=atan2(pq.y,pq.x);}
	bool operator<(halfplane b)const{return angle<b.angle;}
	bool out(pt q){return det(pq,q-p)<-EPS;}
};
vector<pt> intersect(vector<halfplane> b) {
	vector<pt>bx={{DINF,DINF},{-DINF,DINF},{-DINF,-DINF},{DINF,-DINF}};
	forn(i,4) b.pb(halfplane(bx[i],bx[(i+1)%4]));
	sort(all(b));
	int n=sz(b),q=1,h=0;
	vector<halfplane> c(sz(b)+10);
	forn(i,n) {
		while(q<h&&b[i].out(intersect(c[h],c[h-1]))) h--;
		while(q<h&&b[i].out(intersect(c[q],c[q+1]))) q++;
		c[++h]=b[i];
		if(q<h&&abs(det(c[h].pq,c[h-1].pq))<EPS){
			if(dot(c[h].pq,c[h-1].pq)<=0) return {};
			h--;
			if(b[i].out(c[h].p)) c[h]=b[i];
		}
	}
	while (q<h-1&&c[q].out(intersect(c[h],c[h-1])))h--;
	while (q<h-1&&c[h].out(intersect(c[q],c[q+1])))q++;
	if (h-q<=1)return{};
	c[h+1] = c[q];
	vector<pt> s;
	forr(i,q,h+1) s.pb(intersect(c[i],c[i+1]));
	return s;
}

double area(vector<pt> pg) {
	double ans = 0;
	int const n = sz(pg);
	forn(i, n) {
		ans += det(pg[i], pg[(i+1)%n]);
	}
	return abs(ans / 2);
}

void solve() {

	double dx, dy; int n;
	cin >> dx >> dy >> n;

	vector<pt> a(n);
	forn(i, n) cin >> a[i].x >> a[i].y;

	vector<int> b(n);
	forn(i, n) cin >> b[i], --b[i];

	vector<halfplane> planes;
	planes.pb(halfplane({0,0}, {dx,0}));
	planes.pb(halfplane({dx,0}, {dx,dy}));
	planes.pb(halfplane({dx,dy}, {0,dy}));
	planes.pb(halfplane({0,dy}, {0,0}));
	forn(i, n) {
		forn(j, i) {
			pt u = a[b[i]];
			pt v = a[b[j]];
			// u a la izq de j
			planes.pb(halfplane(u, v));
		}
	}

	auto pg = intersect(planes);
	cout << fixed << setprecision(4) << area(pg) << "\n";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	solve();
}

