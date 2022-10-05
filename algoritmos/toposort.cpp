


int topo_orden[MAXN];
int topo_idx = 0;

// =====

bool topo_vis[MAXN];
void dfs_topo(int u) {
	topo_vis[u] = true;
	for (auto v : g[u]) if (!topo_vis[u]) dfs_topo(u);
	topo_orden[topo_idx++] = u;
}
void toposort() {
	topo_idx = 0;
	memset(topo_vis, 0, sizeof(topo_vis));
	forn(u, n) if (!topo_vis[u]) dfs_topo(u);
	reverse(topo_orden, topo_orden+n);
}

// =====

// toposort minimo lexicograficamente
// para el maximo, sacar los "-"
// !!! LOS NODOS QUE PUEDEN ALCANZAR CICLOS NO APARECEN EN EL ORDEN !!!
// el orden termina teniendo topo_idx nodos nada mas
int indeg[MAXN];
void toposort_lex() {
	memset(indeg, 0, sizeof(indeg));
	forn(u, n) for(int v : G[u]) indeg[v]++;

	topo_idx = 0;
	priority_queue<int> pq;
	forn(u, n) if (indeg[u] == 0) pq.push(-u);
	while (not pq.empty()) {
		int u = -pq.top(); pq.pop();
		topo_orden[topo_idx++] = u;
		for (int v : g[u]) {
			if (--indeg[v] == 0)
				pq.push(-v);
		}
	}
	reverse(topo_orden, topo_orden+topo_idx);
}
