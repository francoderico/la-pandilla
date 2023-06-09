// https://codeforces.com/gym/101667/problem/E
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
#define LINEA cerr << "=================== " << __LINE__ << " =====================\n";
#define RAYA cerr << "========================================\n";

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<ll> vll;

const ll MAXN = 1e2+100;
const ll MAXM = 5e2+100;
const ll INF = 1000;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;
const ld PI = acosl(-1);

struct Edge { int u,v,w; };
bool operator<(Edge e1, Edge e2) { return e1.w < e2.w; }

Edge edges[MAXM];

struct EdmondKarp {

	int n = 0;
	int edge_counter = 0;

	vector<pii> graph[2][MAXN]; // (dest, id arista)
	vector<int> cap[2];
	vector<int> base_cap;

	void init(int n_in) {
		n = n_in;
		edge_counter = 0;
		forn(dir, 2) {
			forn(u, MAXN)
				graph[dir][u].clear();
			cap[dir].clear();
		}
		base_cap.clear();
	}

	void add_edge(int u, int v, int c) {
		int id = edge_counter++;
		base_cap.pb(c);
		graph[0][u].pb({v, id});
		graph[1][v].pb({u, id});
	}

	int bfs(int const s, int const t) {
		vector<bool> visited(n, false);
		vector<tuple<int,int,int>> ant(n, {-1,-1,-1});
		queue<int> q;
		q.push(s); visited[s] = true;
		while (not q.empty()) {
			int u = q.front(); q.pop();
			forn(dir, 2) for (auto [v, id] : graph[dir][u]) {
				if (visited[v]) continue;
				if (cap[dir][id] <= 0) continue;
				visited[v] = true;
				ant[v] = {u, id, dir};
				q.push(v);
			}
		}
		if (!visited[t]) return 0;
		int flow = INT_MAX;
		for (int pos = t; pos != s;) {
			auto [next, id, dir] = ant[pos];
			flow = min(flow, cap[dir][id]);
			pos = next;
		}
		for (int pos = t; pos != s;) {
			auto [next, id, dir] = ant[pos];
			cap[ dir][id] -= flow;
			cap[!dir][id] += flow;
			pos = next;
		}
		return flow;
	}

	int max_flow(int s, int t) {
		cap[1].assign(edge_counter, 0);
		cap[0] = base_cap;
		int total_flow = 0;
		while (1) {
			int change = bfs(s, t);
			if (change <= 0) break;
			total_flow += change;
		}
		return total_flow;
	}

};


EdmondKarp flujo;
int n, m;
ostream&operator<<(ostream&o,pii p){return o<<"["<<p.fst<<", "<<p.snd<<"]";}

int main(){
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

	cin >> n >> m;

	forn(id, m) {
		int u,v,w;
		cin >> u >> v >> w; --u;--v;
		edges[id] = {u,v,w};
	}

	sort(edges, edges+m);

	flujo.init(n);

	int suma = 0;
	int id_lo = 0;
	forn(id, m) {
		auto [u,v,w] = edges[id];

		int cutoff = w;

		for (; id_lo < m; id_lo++) {
			auto [u,v,w] = edges[id_lo];
			if (w >= cutoff) break;
			flujo.add_edge(u,v,1);
			flujo.add_edge(v,u,1);
		}

		suma += flujo.max_flow(v, u);
	}
	cout << suma << '\n';

    return 0;
}
