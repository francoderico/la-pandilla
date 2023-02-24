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

// datos por vertice
int hi[MAXN]; // id del heavy path
int hr[MAXN]; // raiz del heavy path

// datos por heavy-path
struct Segtree {};
Segtree hp[MAXN];
int hp_count = 0;

void init_hld(int u) {
	depth[u] = 0;
	padre[u] = u;
	owned_edge[u] = -1;
	root(u, -1);

	// TODO
	// para cada nodo u
	// si es raiz de un heavy path
	// init_hp(hp_count++, u)
}

int query_hld(int u, int v) {
	int result = 0;
	while (hi[u] != hi[v]) {
		if (depth[hr[u]] < depth[hr[v]]) swap(u, v);
		result += query_hp(hr[u], u);
		u = padre[hr[u]];
	}
	if (depth[v] < depth[u]) swap(u, v);
	result += query_hp(u, v);
	return result;
}

// TODO
void init_ds(int id, int* arr, int n) { }
int query_ds(int id, int l, int r) { return -1; }

int pos_in_path(int u) { return depth[u] - depth[hr[u]]; }

int query_hp(int u, int v) {
	// u es el de arriba
	assert(depth[u] < depth[v]);
	assert(hi[u] == hi[v]);
	query_ds(hi[u], pos_in_path(u), pos_in_path(v)+1);
}

void init_hp(int id, int u) {
	vector<int> costos;
	for (int v = u; heavy_child(v) != -1; v = heavy_child(v)) {
		hi[v] = id; hr[v] = u;
		costos.pb(vertex_cost(v));
	}
	init_ds(id, &costos[0], sz(costos));
}


HLD hld;


int query(int u, int v) {
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
