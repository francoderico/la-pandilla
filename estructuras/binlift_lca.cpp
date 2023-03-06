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
// 0 <= t < 2**LOG2N
int query_blift(int x, int t) {
	dforn(k, LOG2N) {
		if (t & (1<<k)) {
			x = bl[k][x];
		}
	}
	return x;
}

/* Uso:

vector<int> next(n);
... inicializa next ...

init_blift(&next[0], n);

// j = next[next[...[i]...]]; (9 veces)
int j = query_blift(i, 9);

*/

// == FIN BINARY LIFTING =============

int padre[MAXN]; // padre en el arbol
int depth[MAXN]; // distancia a la raiz (en #aristas)

void dfs_lca(int u) {
	for(auto v:g[u])if(v!=padre[u]){
		padre[v] = u;
		depth[v] = depth[u] + 1;
		dfs_lca(v);
	}
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

/* Uso:

init_lca(nodo_raiz, n);
int w = query_lca(u, v);

*/
