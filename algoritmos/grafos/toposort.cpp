
// ==== REQUISITOS ====
// int n;
// vector<int> g[MAXN];

vector<int> orden_topo;

// =====

bool topo_vis[MAXN];
void dfs_topo(int u) {
	topo_vis[u] = true;
	fore (v, g[u]) if (!topo_vis[v]) dfs_topo(v);
	orden_topo.pb(u);
}
vector<int> toposort() {
	orden_topo.clear();
	memset(topo_vis, 0, sizeof(topo_vis));
	forn(u, n) if (!topo_vis[u]) dfs_topo(u);
	reverse(all(orden_topo));
	return orden_topo;
}

// =====

// toposort minimo lexicograficamente
// para el maximo, sacar los "-" en push() y top()
// !!! LOS NODOS QUE PUEDEN ALCANZAR CICLOS NO APARECEN EN EL ORDEN !!!
int indeg[MAXN];
vector<int> toposort_lex() {
	orden_topo.clear();
	memset(indeg, 0, sizeof(indeg));
	forn(u, n) for(int v : g[u]) indeg[v]++;
	priority_queue<int> pq;
	forn(u, n) if (indeg[u] == 0) pq.push(-u);
	while (not pq.empty()) {
		int u = -pq.top(); pq.pop();
		orden_topo.pb(u);
		fore(v, g[u]) if (--indeg[v] == 0) pq.push(-v);
	}
	return orden_topo;
}
