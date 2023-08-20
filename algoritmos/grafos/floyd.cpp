// REQUISITO: int n; // numero de nodos
struct Floyd { ll g[MAXN][MAXN];
	void init() { forn(i, n) forn(j, n) g[i][j] = i==j ? 0 : INF; }
	void add_edge(int u, int v, ll w) { g[u][v] = min(g[u][v], w); }
	void run() { // hace que g[u][v] sea = distancia u->v
		forn(i, n) forn(j, n) forn(k, n) if (max(g[j][i], g[i][k]) < INF)
			g[j][k] = min(g[j][k], g[j][i] + g[i][k]);
	}
	bool in_neg_cycle(int u) { return g[u][u] < 0; }
};
