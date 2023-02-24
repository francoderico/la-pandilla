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

// edge data
int edge_cost[MAXN];  // cost of this edge
int edge_owner[MAXN]; // which vertex owns this edge

// vertex data
int padre[MAXN];
int depth[MAXN];
int owned_edge[MAXN]; // which edge this vertex owns
int vertex_cost(int v) {
	if (owned_edge[v] == -1) return INT_MAX; // TODO: elemento neutro
	return edge_cost[owned_edge[v]];
}

void root(int u, int p) {
	for (auto [v,id] : g[u]) if (v!=p) {
		padre[v] = u;
		depth[v] = depth[u]+1;
		owned_edge[v] = id;
		edge_owner[id] = v;
		root(v, u);
	}
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
	return u;
}

// == FIN BINARY LIFTING =============

void init_lca(int* padre, int n) {
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

// datos por heavy path
int hroot[MAXN]; // raiz de cada heavy path

// datos por vertice
int hid[MAXN]; // id del heavy path

struct Segtree {};
Segtree ds[MAXN];

void init_hp(int id, int u) {
	hroot[id] = u;

	int v = u;
	while (heavy_child(v) != -1)
		v = heavy_child(v);

	int len = depth[v] - depth[u];
	vector<int> costos(len);

	v = u;
	forn(i, len) {
		hid[v] = id;
		costos[i] = vertex_cost(v);
		v = heavy_child(v);
	}

	init_ds(id, &costos[0], len);
}

int query_ds(int id, int l, int r) {
	return -1;
}

int pos_in_path(int id, int u) {
	return depth[u] - depth[hroot[id]];
}

int query_hpath(int id, int u, int v) { assert(depth[u] < depth[v]);
	query_ds(id, pos_in_path(id, u), pos_in_path(id, v)+1);
}

void init_hld(int u) {
	depth[u] = 0;
	padre[u] = u;
	owned_edge[u] = -1;
	root(u, -1);
	init_lca(padre, n);
}

int query_upwards(int u, int w) { assert(depth[w] < depth[u]);
	int result = 0;
	while (hid[u] != hid[w]) {
		result += query_hpath(hid[u], hroot[hid[u]], u);
		u = padre[hroot[hid[u]]];
	}
	result += query_hpath(hid[u], w, u);
	return result;
}

int query_hld(int u, int v) {
	int w = query_lca(u, v);
	if (u == w) return query_upwards(v, u);
	if (v == w) return query_upwards(u, v);
	int uw = query_blift(u, depth[u] - depth[w] - 1);
	int vw = query_blift(v, depth[v] - depth[w] - 1);
	return query_upwards(u, uw) + vertex_cost(w) + query_upwards(v, vw);
}

















int query(int u, int v) {
	if (u == v) return INT_MAX; // TODO: elemento neutro
	int w = query_lca(u, v);
	if (w == v) swap(u, v);
	if (w == u) {
		assert(depth[v] - depth[u] >= 1);
		return query_hld(v, query_blift(v, depth[v]-depth[u]-1));
	}
	return query_hld(v, u);
}

void update(int id, int cost) {
}

void solve() {
	cin >> n;

	forn(i,n-1){
		int u,v,cost;
		cin >> u >> v >> cost;
		--u; --v;
		edge_cost[i] = cost;
		g[u].pb({v, i});
		g[v].pb({u, i});
	}

	init_hld(0);

	while (true) {
		string op;
		cin >> op;
		if (op == "CHANGE") {
			int id, cost;
			cin >> id >> cost;
			id--;
			edge_cost[id] = cost;
			update(id, cost);
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
