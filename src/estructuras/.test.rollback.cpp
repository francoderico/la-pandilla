// https://www.codechef.com/problems/GERALD07

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

// Permite hacer CTRL+Z hasta el estado en que se toma el snapshot
// Uso: int tiempo = snapshot(); ...; restore(tiempo);
vector<pair<int&, int>> changes;
int snapshot() { return sz(changes); }
void restore(int snap) {
	while (sz(changes) > snap) {
		auto [l, r] = changes.back(); changes.pp();
		l = r;
	}
}
int assign(int& l, int r) { // Reemplazar los a=b de la struct por assign(a, b)
	changes.pb({l, l});
	return l = r;
}


int uf[MAXN];
void uf_init(){ memset(uf, -1, sizeof(uf)); }
int uf_find(int x){ return uf[x]<0 ? x : uf_find(uf[x]); }
bool uf_join(int x, int y){
	// notar que los assign no se hacen en variables de scope local
	x = uf_find(x); y = uf_find(y);
	if(x == y) return false;
	if(uf[x] > uf[y]) swap(x, y);
	assign(uf[x], uf[x]+uf[y]); assign(uf[y], x);
	return true;
}


struct Range{
	int l, r, idx;
};

const int MO = 450;
bool cmp(Range a, Range b){
	if(a.l / MO == b.l / MO) return a.r < b.r;
	return a.l < b.l;
}

vector<pii> edges;
vector<Range> queries;
vector<int> rta;

void solve(){
	int n, m, q; cin >> n >> m >> q;
	edges.clear();
	queries.clear();
	rta.resize(q);
	forn(_, m){
		int u, v; cin >> u >> v; u --, v --;
		edges.pb({u, v});
	}
	forn(i, q){
		int l, r; cin >> l >> r; l --;
		queries.pb({l, r, i});
	}

	sort(all(queries), cmp);

	int ans;
	int block = -1;
	int l = 0, r = 0;
	int d;
	forn(i, q){
		auto [a, b, idx] = queries[i];

		int new_block = a / MO;
		if(new_block != block){
			uf_init();
			changes.clear();
			ans = n;
			block = new_block;
			d = (block+1)*MO;
			r = d;
		}
		
		l = min(d, b);

		while(r < b){
			auto [u, v] = edges[r++];
			ans -= uf_join(u, v);
		}
		int t = snapshot();{
			while(l > a){
				auto [u, v] = edges[--l];
				assign(ans, ans-uf_join(u, v));
			}

			rta[idx] = ans;
		}
		restore(t);
	}

	forn(i, q) cout << rta[i] << ' ', nn;
}

int main(){
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int t; cin >> t; while(t--)
	solve();
}