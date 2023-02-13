
struct EdmondKarp {
	int n = 0;
	int edge_counter = 0;
	vector<pii> graph[2][MAXN];
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

