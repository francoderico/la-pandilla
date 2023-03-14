//Max flow en O(V^2 E)

//dist: una vez que tiramos el flujo, me dice la distancia desde S, sin ponderar

//Las aristas e de la red residual tienen e.cap = 0 y e.f = -(flujo en la otra direccion).
//Por ejemplo, si la arista u-v termina tirando 3 de flujo, la arista v-u de la residual tiene -3.

struct Dinic
{
	int nodes, src, dst;
	vector<int> dist, q, work;
	struct edge {int to, rev; ll f, cap;};		// Se puede agregar un bool is_back, y solo hay que modificar add_edge
	vector<vector<edge>> g;
	vector<ll> dd;
	
	Dinic(int x) : nodes(x), dist(x+2), q(x+2), work(x+2), g(x+2), dd(x+2) {}
	
	void add_edge(int s, int t, ll cap, ll mincap = 0)
	{
		mincap = max(mincap, 0LL);
		// assert(mincap<=cap);
		dd[s] += mincap;
		dd[t] -= mincap;
		g[s].pb((edge){t, sz(g[t]),   0, cap-mincap});
		g[t].pb((edge){s, sz(g[s])-1, 0, 0});
	}
	
	bool dinic_bfs()
	{
		fill(all(dist), -1); dist[src] = 0;
		int qt = 0; q[qt++] = src;
		for(int qh = 0; qh<qt; qh++)
		{
			int u = q[qh];
			forn(i, sz(g[u]))
			{
				edge &e = g[u][i]; int v = g[u][i].to;
				if(dist[v]<0 and e.f<e.cap) dist[v] = dist[u]+1, q[qt++] = v;
			}
		}
		return dist[dst] >= 0;
	}
	
	ll dinic_dfs(int u, ll f)
	{
		if(u == dst)return f;
		for(int &i = work[u]; i<sz(g[u]); i++)
		{
			edge &e = g[u][i];
			if(e.cap <= e.f)continue;
			int v = e.to;
			if(dist[v] == dist[u]+1)
			{
				ll df = dinic_dfs(v, min(f, e.cap-e.f));
				if(df > 0){e.f += df; g[v][e.rev].f -= df; return df;}
			}
		}
		return 0;
	}
	
	ll max_flow(int _src, int _dst)
	{
		src = _src; dst = _dst;
		ll result = 0;
		while(dinic_bfs())
		{
			fill(all(work), 0);
			while(ll delta = dinic_dfs(src, INF)) result += delta;
		}
		return result;
	}

	ll max_flow_min_cap(int s, int t)
	{
		add_edge(t, s, INF);
		
		ll w = 0;
		
		nodes += 2;

		forn(i, nodes)
		{
			if(dd[i] > 0) add_edge(i, nodes-1, dd[i]), w += dd[i];
			else if(dd[i]<0) add_edge(nodes-2, i, -dd[i]);
		}

		if(max_flow(nodes-2, nodes-1) != w) return -1;
		
		nodes -= 2;
		
		forn(i, nodes) if(dd[i]) g[i].pp();

		return max_flow(s,t);
	}
};
