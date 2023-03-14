// Min cut: nodes with dist>=0 (S y todos los alcanzables) vs nodes with dist == -1
// Matching maximo
// min vertex cover: left nodes with dist == -1 + right nodes with dist>0
// MAX independent set: complemento del mvc, o sea, left nodes with dist>0 + right nodes with dist == -1
// min edge cover: MM + una arista cualquiera por cada otro nodo (es imposible sii hay algun nodo sin aristas)
// Feasible (red fuertemente conexa con restricciones de minimo y maximo en cada arista)

// Conjunto del min cut de s, sin incluir al propio s
vector<int> min_cut_s(Dinic& ne, int nodes)
{
	vector<int> ret;
	forn(x, nodes-2) if(ne.dist[x] > 0) ret.pb(x);
	return ret; 
}

// Conjunto del min cut de t, sin incluir al propio t
vector<int> min_cut_t(Dinic& ne, int nodes)
{
	vector<int> ret;
	forn(x, nodes-2) if(ne.dist[x] == -1) ret.pb(x);
	return ret; 
}



//------------------------------------------------------



// MM = max_flow = min_cut
// Dado un grafo bipartito representado por la red ne
// con nodes nodos, me da las aristas del matching maximo, en O(m)
// nodos: [0..nodes-2)
// s: nodes-2
// t: nodes-1
vector<pii> mm_edges(Dinic& ne, int nodes)
{
	vector<pii> ret;
	int s = nodes-2;

	for(auto e : ne.g[s])	//x: todos los nodos izquierdos
	{
		int x = e.to;
		if(e.f == 1)		//La arista desde s esta usada
		{
			for(auto d : ne.g[x]) if(d.f == 1)	//Busco la arista que salga de x y este usada
			{
				ret.pb({x, d.to});
				break;
			}
		}
	}

	return ret;
}



//------------------------------------------------------



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



//------------------------------------------------------



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



//------------------------------------------------------



//n - MM
vector<pii> min_edge_cover(Dinic& ne, int nodes)
{
	vector<pii> ret;
	int s = nodes-2, t = nodes-1; 

	forn(x, s) if(sz(ne.g[x]) == 1) return ret;		//No se puede, hay algun nodo sin aristas (solo esta unido con s o con t)

	for(auto e : ne.g[s])	//x: todos los nodos izquierdos
	{
		int x = e.to;
		if(e.f == 1)		//La arista s-x esta usada, o sea que x parte del MM: agrego su arista
		{
			for(auto d : ne.g[x]) if(d.f == 1)
			{
				ret.pb({x, d.to});
				break;
			}
		}
		else				//Si NO esta usada, x NO es parte del MM: agrego una arista cualquiera
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
		if(e.f != -1)		//La arista x-t NO esta usada, o sea que x NO parte del MM: agrego una arista cualquiera
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



//------------------------------------------------------



// Feasible (red fuertemente conexa con restricciones de minimo y maximo en cada arista)
ll demand[MAXN];        // Si el nodo i requiere que salga 2 de flujo mas de lo que entra seteo demand[i] = -2, si requiere que salga 2 menos de lo que entra (se come el flujo) seteo demand[i] = 2
ll M[MAXN];             // dif[i] - (suma(l entrantes) - suma(l salientes)).   -- se llena en feasible
int a[MAXM], b[MAXM];   // aristas a[i]-b[i]
ll l[MAXM], u[MAXM];    // con capacidad minima l[i] y maxima u[i]
ll mando[MAXM];         // Cuanto flujo mando por cada arista        -- se llena en feasible
map<pii, int> ind;      // Para cada arista u-v, me da su i tal que a[i] = u y b[i] = v      -- se llena en feasible

// Chequea si una red de flujo fuertemente conexa, sin s ni t, con restricciones de capacidades
// minimas y maximas en cada arista tiene algun flujo valido, y lo reconstruye en el array mando
// n = cantidad de nodos
// m = cantidad de aristas
bool feasible(Dinic& ne, int n, int m)
{
	forn(i, n) M[i] = demand[i];

	forn(i, m)
	{
		ne.add_edge(a[i], b[i], u[i]-l[i]); //Agregamos la arista con capacidad u-l
		M[a[i]] += l[i];
		M[b[i]] -= l[i];

		ind[{a[i], b[i]}] = i;
	}

	int s_ = n, t_ = n+1, nodes = n+2;
	
	forn(i, n)
	{
		if(M[i] < 0) ne.add_edge(s_, i, -M[i]);
		if(M[i] > 0) ne.add_edge(i, t_,  M[i]);
	}

	ne.max_flow(s_, t_);
	
	for(auto e : ne.g[s_]) if(e.f < e.cap) return false;

	forn(i, n)
	{
		for(auto e : ne.g[i])
		{
			int j = e.to;
			if(j == s_ or j == t_ or e.is_back) continue;
			
			mando[ind[{i, j}]] = l[ind[{i, j}]] + e.f;
		}
	}
	
	return true;
}
