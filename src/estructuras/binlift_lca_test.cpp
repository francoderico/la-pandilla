// https://www.spoj.com/problems/QTREE2/
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

const ll MAXN = 1e4+100;

const ll INF = 1e18+100;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;
const ld PI = acosl(-1);

int n;

struct hedge {
	int v, id;
};

vector<hedge> g[MAXN];
int edge_cost[MAXN];
ll weighted_depth[MAXN];

void dfs(int u, int p) {
	// ASFDGASDQFJGAFVB SPOJ MALARDO NO TIENE C++17
	for(auto e:g[u]){int v=e.v,id=e.id;if(v!=p){
		weighted_depth[v] = weighted_depth[u] + edge_cost[id];
		dfs(v, u);
	}}
}

// == INICIO LCA =====================

// == INICIO BINARY LIFTING ==========

const ll LOG2N = 14;
int bl[LOG2N][MAXN];

// f es una funcion de [0,n) -> [0,n)
// calcula f^(2^k)(x)
// para todo x:[0,n), k:[0,LOG2N)
void init_blift(int* f, int n) {
	forn(x, n) bl[0][x] = f[x];
	forr(k, 1, LOG2N) {
		forn(x, n) {
			bl[k][x] = bl[k-1][bl[k-1][x]];
		}
	}
}

// calcula f^t(x)
int query_blift(int x, int t) {
	dforn(k, LOG2N) {
		if (t & (1<<k)) {
			x = bl[k][x];
		}
	}
	return x;
}

// == FIN BINARY LIFTING =============

int padre[MAXN]; // padre en el arbol
int depth[MAXN]; // distancia (en #aristas) a la raiz

void dfs_lca(int u) {
	for(auto e:g[u]){int v=e.v;if(v!=padre[u]){
		padre[v] = u;
		depth[v] = depth[u] + 1;
		dfs_lca(v);
	}}
}

void init_lca(int root, int n) {
	depth[root] = 0;
	padre[root] = root;
	dfs_lca(root);
	init_blift(padre, n);
}

int query_lca(int u, int v) {
	int h = min(depth[u], depth[v]);
	u = query_blift(u, depth[u] - h);
	v = query_blift(v, depth[v] - h);
	if (u == v) return u;
	dforn(k, LOG2N) {
		if (bl[k][u] != bl[k][v]) {
			u = bl[k][u];
			v = bl[k][v];
		}
	}
	return bl[0][u];
}

// == FIN LCA ========================

ll dist(int u, int v) {
	int w = query_lca(u, v);
	return (weighted_depth[u] - weighted_depth[w]) + (weighted_depth[v] - weighted_depth[w]);
}

int kth(int u, int v, int k) {
	int w = query_lca(u,v);
	int distuw = depth[u] - depth[w];
	int distvw = depth[v] - depth[w];
	if (k <  distuw) return query_blift(u, k);
	if (k >  distuw) return query_blift(v, distvw-(k-distuw));
	return w;
}

void solve() {
	cin >> n;

	forn(i,n) g[i].clear();

	forn(i,n-1){
		int u,v;
		cin >> u >> v >> edge_cost[i];
		--u; --v;
		g[u].pb({v, i});
		g[v].pb({u, i});
	}

	weighted_depth[0] = 0;
	dfs(0, -1);

	init_lca(0, n);

	// forn(i,n) cerr << "DEPTH " << i << " = " << depth[i] << '\n';
	// forn(i,n) cerr << "WEIGHTED DEPTH " << i << " = " << depth[i] << '\n';

	while (true) {
		string op;
		cin >> op;
		if (op == "KTH") {
			int u, v, k;
			cin >> u >> v >> k;
			--u; --v; --k;
			cout << (kth(u, v, k)+1) << '\n';
		} else if (op == "DIST") {
			int u, v;
			cin >> u >> v;
			--u; --v;
			cout << dist(u,v) << '\n';
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
