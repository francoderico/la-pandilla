// https://www.spoj.com/problems/QTREE/
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

const ll MAXN = 2e4+100;

const ll INF = 1e18+100;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;
const ld PI = acosl(-1);

vector<int> g[MAXN];

struct Mono {
	int x;
	static Mono zero() { return {INT_MIN}; }
};
Mono operator+ (Mono a, Mono b) {
	return {max(a.x, b.x)};
}

struct Segtree {
	static constexpr int log2n = 15;
	static constexpr int len = 1<<log2n, sze = 1<<(log2n+1);
	vector<Mono> data;
	Segtree() : data(sze) { }

	// inicia con los valores dados O(n+len)
	void init(Mono* a, int n) {
		forn(i, sze) data[i] = Mono::zero();
		forn(i, n) data[i+len] = a[i];
		dforr(i, 1, len) data[i] = data[i*2] + data[i*2+1];
	}

	// point update O(log(len))
	void update(int i, Mono x) {
		i += len; data[i] = x;
		while (i /= 2) data[i] = data[i*2] + data[i*2+1];
	}

	// range query O(log(len))
	Mono query(int l, int r) { ql = l; qr = r; return q_(1, 0, len); }

private:
	int ql, qr;
	Mono q_(int i, int l, int r) {
		if (r <= ql || qr <= l) return Mono::zero();
		if (ql <= l && r <= qr) return data[i];
		int m = (l+r)/2;
		return q_(i*2,l,m) + q_(i*2+1,m,r);
	}
};

#include "hld.cpp"

Hld hld;

void update(int u, int x) { hld.update(u, {x}); }
int query(int u, int v) { return hld.query(u,v).x; }


void solve() {
	int n;
	cin >> n;

	int nodes = n+(n-1);
	forn(i,nodes) g[i].clear();

	vector<Mono> data(nodes, Mono::zero());

	forn(i, n-1){
		int u,v,cost;
		cin >> u >> v >> cost;
		--u; --v;

		int w = n+i;

		data[w] = {cost};

		g[u].pb(w);
		g[w].pb(u);

		g[v].pb(w);
		g[w].pb(v);
	}

	hld.init(0, &data[0], nodes);

	while (true) {
		string op;
		cin >> op;
		if (op == "CHANGE") {
			int id, cost;
			cin >> id >> cost;
			id--;
			int w = n+id;
			update(w, cost);
		} else if (op == "QUERY") {
			int u, v;
			cin >> u >> v;
			--u; --v;
			cout << query(u,v) << '\n';
		} else {
			assert(op == "DONE");
			break;
		}
	}

}

int main(){
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

	int t; cin >> t;
	forn(_,t) solve();
    
    return 0;
}
