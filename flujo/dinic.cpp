//Max flow en O(V^2 E)

//dist: una vez que tiramos el flujo, me dice la distancia desde S, sin ponderar

//Las aristas e de la red residual tienen e.cap = 0 y e.f = -(flujo en la otra dirección).
//Por ejemplo, si la arista u-v termina tirando 3 de flujo, la arista v-u de la residual tiene -3.

//Min cut: nodes with dist>=0 (S y todos los alcanzables) vs nodes with dist == -1
//Matching máximo
//min vertex cover: left nodes with dist == -1 + right nodes with dist>0
//MAX independent set: complemento del mvc, o sea, left nodes with dist>0 + right nodes with dist == -1
//min edge cover: MM + una arista cualquiera por cada otro nodo (es imposible sii hay algún nodo sin aristas)
struct Dinic
{
	int nodes, src, dst;
	vector<int> dist, q, work;
	struct edge {int to, rev; ll f, cap;};
	vector<vector<edge>> g;
	
    Dinic(int x) : nodes(x), dist(x), q(x), work(x), g(x) {}
	
    void add_edge(int s, int t, ll cap)
    {
		g[s].pb((edge){t, sz(g[t]), 0, cap});
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
};

//Conjunto del min cut de s, sin incluir al propio s
vector<int> min_cut_s(Dinic& ne, int nodes)
{
	vector<int> ret;
	forn(x, nodes-2) if(ne.dist[x] > 0) ret.pb(x);
	return ret; 
}

//Conjunto del min cut de t, sin incluir al propio t
vector<int> min_cut_t(Dinic& ne, int nodes)
{
	vector<int> ret;
	forn(x, nodes-2) if(ne.dist[x] == -1) ret.pb(x);
	return ret; 
}

//MM = max_flow = min_cut
//Dado un grafo bipartito representado por la red ne
//con nodes nodos, me da las aristas del matching máximo, en O(m)
//nodos: [0..nodes-2)
//s: nodes-2
//t: nodes-1
vector<pii> mm_edges(Dinic& ne, int nodes)
{
	vector<pii> ret;
	int s = nodes-2;

	for(auto e : ne.g[s])	//x: todos los nodos izquierdos
	{
		int x = e.to;
		if(e.f == 1)		//La arista desde s está usada
		{
			for(auto d : ne.g[x]) if(d.f == 1)	//Busco la arista que salga de x y esté usada
			{
				ret.pb({x, d.to});
				break;
			}
		}
	}

	return ret;
}

//MM
vector<int> min_vertex_cover(Dinic& ne, int nodes)
{
	vector<int> ret;
	int s = nodes-2, t = nodes-1;

	for(auto e : ne.g[s])	//x: todos los nodos izquierdos
	{
		int x = e.to;
		if(ne.dist[x] == -1) ret.pb(x);		//x es del corte t
	}

	for(auto e : ne.g[t])	//x: todos los nodos derechos
	{
		int x = e.to;
		if(ne.dist[x] > 0)   ret.pb(x);		//x es del corte s
	}

	return ret;
}

//n - MM
//Complemento del mvc
vector<int> max_independent_set(Dinic& ne, int nodes)
{
	vector<int> ret;
	int s = nodes-2, t = nodes-1;

	for(auto e : ne.g[s])	//x: todos los nodos izquierdos
	{
		int x = e.to;
		if(ne.dist[x] > 0)   ret.pb(x);		//x es del corte s
	}

	for(auto e : ne.g[t])	//x: todos los nodos derechos
	{
		int x = e.to;
		if(ne.dist[x] == -1) ret.pb(x);		//x es del corte s
	}

	return ret;
}

//n - MM
vector<pii> min_edge_cover(Dinic& ne, int nodes)
{
	vector<pii> ret;
	int s = nodes-2, t = nodes-1; 

	forn(x, s) if(sz(ne.g[x]) == 1) return ret;		//No se puede, hay algún nodo sin aristas (solo está unido con s o con t)

	for(auto e : ne.g[s])	//x: todos los nodos izquierdos
	{
		int x = e.to;
		if(e.f == 1)		//La arista s-x está usada, o sea que x parte del MM: agrego su arista
		{
			for(auto d : ne.g[x]) if(d.f == 1)
			{
				ret.pb({x, d.to});
				break;
			}
		}
		else				//Si NO está usada, x NO es parte del MM: agrego una arista cualquiera
		{
			for(auto d : ne.g[x])
			{
				if(d.to != s)
				{
					ret.pb({x, d.to});
					break;
				}
			}
		}
	}
	
	for(auto e : ne.g[t])	//x: todos los nodos derechos
	{
		int x = e.to;
		if(e.f != -1)		//La arista x-t NO está usada, o sea que x NO parte del MM: agrego una arista cualquiera
		{
			for(auto d : ne.g[x])
			{
				if(d.to != t)
				{
					ret.pb({x, d.to});
					break;
				}
			}
		}
	}

	return ret;
}
