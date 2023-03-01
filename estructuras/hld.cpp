// ==== REQUISITOS ==================
// const int MAXN = ...;
// vector<int> g[MAXN];
// struct Mono { ... };
// Mono operator+(Mono a, Mono b) { ... }
// struct Segtree { ... };

struct Hld {
	Segtree st;
	int root[MAXN];   // raiz del heavy path
	int child[MAXN];  // hijo en el heavy path
	int pos[MAXN];    // tiempo de entrada en dfs
	int depth[MAXN];  // distancia a la raiz (en #aristas)
	int parent[MAXN]; // padre en el rooteo
	int dfs_time;

	void init(int u, Mono* valor, int n) {
		fill(child, child+n, -1);
		depth[u] = dfs_time = 0;
		parent[u] = -1;
		dfs1(u);
		dfs2(u, u);
		vector<Mono> preorden(n);
		forn(i,n) preorden[pos[i]] = valor[i];
		init_ds(&preorden[0], n);
	}

	void update(int u, Mono x) {
		update_ds(pos[u], x);
	}

	Mono query(int u, int v) {
		Mono result = Mono::zero();
		for (; root[u] != root[v]; u = parent[root[u]]) {
			if (depth[root[u]] < depth[root[v]]) swap(u, v);
			result = result + query_ds(pos[root[u]], pos[u]+1);
		}
		if (depth[u] < depth[v]) swap(u, v);
		result = result + query_ds(pos[v], pos[u]+1);
		return result;
	}

	void init_ds(Mono* valores, int n) { st.init(valores, n); }
	Mono query_ds(int l, int r) { return st.query(l, r); }
	void update_ds(int i, Mono x) { st.update(i, x); }

	int dfs1(int u) {
		int tree_size = 1;
		int max_child_size = -1;
		for(auto v:g[u])if(v!=parent[u]) {
			parent[v] = u; depth[v] = depth[u]+1;
			dfs1(v);
			int child_size = dfs1(v);
			tree_size += child_size;
			if (child_size > max_child_size) {
				max_child_size = child_size;
				child[u] = v;
			}
		}
		return tree_size;
	}

	void dfs2(int u, int r) {
		pos[u] = dfs_time++;
		root[u] = r;
		if (child[u] != -1) dfs2(child[u], r);
		for (auto v:g[u]) if (v!=parent[u] && v!=child[u])
			dfs2(v,v);
	}

};
