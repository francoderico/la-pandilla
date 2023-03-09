// https://matcomgrader.com/problem/9549/highway-decommission/
#include<bits/stdc++.h>
using namespace std;

#define forr(i,a,b) for(int i = int(a);i<int(b);++i)
#define forn(i,n) forr(i,0,n)
#define dforr(i,a,b) for(int i=int(b)-1;i>=int(a);--i)
#define dforn(i,n) dforr(i,0,n)
#define fore(e,c) for(const auto&e : (c))
#define db(v) cerr<<#v<<" = "<<(v)<<'\n'
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

const ll MAXN = 1e4+100;
const ll INF = 1e18+100;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;
const ld PI = acosl(-1);

struct edge{
	int v;
	ll len,cost;
};

int n,m;
vector<edge> g1[MAXN];
vector<int> g2[MAXN];


struct path { int u; ll d; };
bool operator<(path a, path b) { return a.d > b.d; }
 
vector<ll> dijkstra(int s) {
    vector<ll> D(n, INF); // vector<int> P(n, -1);
    priority_queue<path> pq;
    pq.push({s, 0}); D[s] = 0; // P[s] = s;
    while (not pq.empty()) {
        path p = pq.top(); pq.pop();
        auto u = p.u; auto du = p.d;
        if (du > D[u]) continue;
        for (auto e : g1[u]) {
            int v = e.v; ll dv = du + e.len;
            if (dv >= D[v]) continue;
            pq.push({v, dv}); D[v] = dv; // P[v] = u;
        }
    }
    return D; // return P;
}

vector<int> orden_topo;

#if 1
bool topo_vis[MAXN];
void dfs_topo(int u) {
	topo_vis[u] = true;
	fore (v, g2[u]) if (!topo_vis[v]) dfs_topo(v);
	orden_topo.pb(u);
}
vector<int> toposort() {
	orden_topo.clear();
	memset(topo_vis, 0, sizeof(topo_vis));
	forn(u, n) if (!topo_vis[u]) dfs_topo(u);
	reverse(all(orden_topo));
	return orden_topo;
}
#else
int indeg[MAXN];
vector<int> toposort() {
	orden_topo.clear();
	memset(indeg, 0, sizeof(indeg));
	forn(u, n) for(int v : g2[u]) indeg[v]++;
	priority_queue<int> pq;
	forn(u, n) if (indeg[u] == 0) pq.push(-u);
	while (not pq.empty()) {
		int u = -pq.top(); pq.pop();
		orden_topo.pb(u);
		fore(v, g2[u]) if (--indeg[v] == 0) pq.push(-v);
	}
	return orden_topo;
}
#endif

void solve() {
    cin>>n>>m;
    forn(i,m){
        int u,v;
        ll l,c;
        cin>>u>>v>>l>>c,--u,--v;
		g1[u].pb({v,l,c});
		g1[v].pb({u,l,c});
    }

	vector<ll> dist = dijkstra(0);

	forn(u,n) {
		fore(e, g1[u]) {
			auto v = e.v;
			if (dist[u] + e.len == dist[v]) {
				g2[u].pb(v);
			}
		}
	}

	vector<int> orden = toposort();

	vector<int> inv_orden(n);
	forn(i, n) inv_orden[orden[i]] = i;

	ll ans=0;
    bool first = true;
	fore(v, orden) {
        if (first) { first = false; continue; }

		ll mejor = INF;
		fore(e, g1[v]) { int u = e.v;
			if (dist[u] + e.len != dist[v]) continue;
			mejor = min(mejor, e.cost);
		}
		ans += mejor;
	}

    cout<<ans<<'\n';
}


int main() {
	// freopen("input.txt", "r", stdin);
	// freopen("output.txt", "w", stdout);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
}
