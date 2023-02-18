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
const ll LOG2N = 14;

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
int ancestor[MAXN][14];
int depth[MAXN];
int owned_edge[MAXN]; // which edge this vertex owns
int vertex_cost(int v) {
	if (owned_edge[v] == -1) return INT_MAX; // TODO: elemento neutro
	return edge_cost[owned_edge[v]];
}

void root(int u, int p) {
	for (auto [v,id] : g[u]) if (v!=p) {
		ancestor[v][0] = u;
		depth[v] = depth[u]+1;
		owned_edge[v] = id;
		edge_owner[id] = v;
		root(v, u);
	}
}

void init_binary_lifting() {
	forr(k,1,LOG2N) forn(u,n)
		ancestor[u][k] = ancestor[ancestor[u][k-1]][k-1];
}

int jump(int u, int x) {
	dforn(k, LOG2N)
		if (x & (1<<k))
			u = ancestor[u][k];
	return u;
}

int lca(int u, int v) {
	if (depth[u] > depth[v]) swap(u,v);
	assert(depth[u] <= depth[v]);
	v = jump(v, depth[v]-depth[u]);
	if (u == v) return u;
	dforn(k, LOG2N) {
		if (ancestor[u][k] != ancestor[v][k]) {
			u = ancestor[u][k];
			v = ancestor[v][k];
		}
	}
	assert(ancestor[u][0] == ancestor[v][0]);
	return ancestor[u][0];
}

void init_hld(int u) {
	depth[u] = 0;
	ancestor[u][0] = u;
	owned_edge[u] = -1;
	root(u, -1);
	init_binary_lifting();
}

int query_hld(int u, int v) {
	int w = lca(u, v);
}

int query(int u, int v) {
	if (u == v) return INT_MAX; // TODO: elemento neutro
	int w = lca(u, v);
	if (w == v) swap(u, v);
	if (w == u) {
		assert(depth[v] - depth[u] >= 1);
		return query_hld(v, jump(v, depth[v]-depth[u]-1));
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
