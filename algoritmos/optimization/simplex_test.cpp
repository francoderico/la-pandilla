// https://codeforces.com/gym/101242/problem/I

#include <bits/stdc++.h>

using namespace std;

#define all(c) (c).begin(),(c).end()
#define fore(e,c) for(const auto&e:(c))
#define forr(i,l,r) for(int i=int(l);i<int(r);++i)
#define forn(i,n) forr(i,0,n)
#define sz(c) (int((c).size()))

typedef long double ld;
using pii = pair<int, int>;

const ld EPS = 1e-9;

#include "simplex.hpp"

const int inf = 1'000'000'007;

vector<pii> dijkstra(
	const vector<vector<int>>& mat,
	const vector<vector<int>>& adj,
	const int o
) {
	const int n = sz(adj);
	vector<pii> dist(n, {inf, -1});
	priority_queue<pii, vector<pii>, greater<pii>> pq;
	dist[o].first = 0, pq.emplace(0,o);
	while (!pq.empty()) {
		const auto [du, u] = pq.top();
		pq.pop();
		if (du != dist[u].first) {continue;}
		fore(v, adj[u]) {
			const int w = mat[u][v];
			if (du + w < dist[v].first) {
				dist[v] = {du + w, u};
				pq.emplace(dist[v].first, v);
			}
		}
	}
	return dist;
}

void solve() {
	cout<<fixed<<setprecision(numeric_limits<ld>::max_digits10);
	int n;
	cin>>n;
	vector<vector<int>> mat(n, vector<int>(n)), adj(n);
	forn(i, n) {
		forn(j, n) {
			cin>>mat[i][j];
		}
	}
	vector<pii> edges;
	map<pii, int> ids;
	forn(u, n) {
		forn(v, n) {
			if (u == v) {continue;}
			if (mat[u][v] == -1) {continue;}
			adj[u].push_back(v);
			ids[{u, v}] = sz(edges);
			edges.emplace_back(u, v);
		}
	}
	vector<vector<pii>> dists(n);
	forn(o, n) {dists[o] = dijkstra(mat, adj, o);}
	int r;
	cin>>r;
	vector<tuple<int, int, double>> trip(r);
	forn(k, r) {
		int s, d;
		double t;
		cin>>s>>d>>t;
		trip[k] = {s, d, t};
	}
	const int vars = sz(edges);
	const int rows = 2 * (vars + r);
	vector<vector<double>> a(rows, vector<double>(vars));
	vector<double> b(rows);
	forn (var, vars) {
		const int i = 2 * var, j = i + 1;
		a[i][var] = 1., b[i] = 2.;
		a[j][var] = -1., b[j] = -1.;
	}
	forn(idx, r) {
		const int i = 2 * (vars + idx), j = i + 1;
		const auto [u, v, t] = trip[idx];
		for (
			int old = v, curr = dists[u][old].second;
			curr != -1;
			old = curr, curr = dists[u][old].second
		) {
			const int edge = ids[{curr, old}];
			a[i][edge] = mat[curr][old];
			a[j][edge] = -mat[curr][old];
		}
		b[i] = t;
		b[j] = -t;
	}
	int q;
	cin>>q;
	forn(_, q) {
		int u, v;
		cin>>u>>v;
		cout<<u<<' '<<v<<' ';
		if (vars == 0) {
			cout<<0.<<' '<<0.<<'\n';
			continue;
		}
		vector<double> c(vars);
		for (
			int old = v, curr = dists[u][old].second;
			curr != -1;
			old = curr, curr = dists[u][old].second
		) {
			const int edge = ids[{curr, old}];
			c[edge] = mat[curr][old];
		}
		cout<<simplex(a, b, c, 1e-5).first<<' ';
		forn(i, vars) {c[i] = -c[i];}
		cout<<-simplex(a, b, c, 1e-5).first<<'\n';
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	solve();
}
