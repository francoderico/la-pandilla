// ==== REQUISITOS ==================
// const int MAXN = ...;
// vector<int> g[MAXN];
// struct Mono { ... };
// Mono operator+(Mono a, Mono b) { ... }
// struct Segtree { ... };

struct Hld {
	Segtree st;
	// raiz del heavy path, tiempo de entrada en dfs, distancia a la raiz (en #aristas)
	int root[MAXN], pos[MAXN], depth[MAXN];
	// hijo en el heavy path, padre en el rooteo
	int child[MAXN], parent[MAXN];
	int dfs_time;

	void init(int u, Mono* valor, int n) {
		fill(child, child+n, -1);
		depth[u] = dfs_time = 0;
		parent[u] = -1;
		dfs1(u); dfs2(u, u);
		vector<Mono> preorden(n);
		forn(i,n) preorden[pos[i]] = valor[i];
		st.init(&preorden[0], n);
	}

	void update(int u, Mono x) {
		st.update(pos[u], x);
	}

	Mono query(int u, int v) {
		Mono result = Mono::zero();
		for (; root[u] != root[v]; u = parent[root[u]]) {
			if (depth[root[u]] < depth[root[v]]) swap(u, v);
			result = result + st.query(pos[root[u]], pos[u]+1);
		}
		if (depth[u] < depth[v]) swap(u, v);
		// v es el LCA de los u y v iniciales
		result = result + st.query(pos[v], pos[u]+1);
		return result;
	}

	int dfs1(int u) {
		int tree_size = 1, child_size;
		int max_child_size = -1;
		for(auto v:g[u])if(v!=parent[u]) {
			parent[v] = u; depth[v] = depth[u]+1;
			tree_size += (child_size = dfs1(v));
			if (child_size > max_child_size)
				max_child_size = child_size, child[u] = v;
		}
		return tree_size;
	}

	void dfs2(int u, int r) {
		pos[u] = dfs_time++; root[u] = r;
		if (child[u] != -1) dfs2(child[u], r);
		for (auto v:g[u]) if (v!=parent[u] && v!=child[u])
			dfs2(v,v);
	}

};
