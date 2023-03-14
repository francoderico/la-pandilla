//Matching máximo en bipartito en O(sqrt(V) E)
//Caso especial de Dinic pero más rápido, menos memoria y más corto
//Los vértices izquierdos están numerados en [0, n), los derechos en [0, m)
int n, m;               //SETEAR
vector<int> g[MAXN];    // [0,n)->[0,m)
int mt[MAXN], mt2[MAXN], ds[MAXN];  //mt2[0..n) contiene el matching n-m
                                    //mt[0..m)  contiene el matching m-n

bool bfs()
{
	queue<int> q;
	memset(ds, -1, sizeof(ds));
	forn(i, n) if(mt2[i]<0) ds[i] = 0, q.push(i);
	bool r = false;
	while(not q.empty())
	{
		int x = q.front(); q.pop();
		for(int y:g[x])
		{
			if(mt[y]>=0 and ds[mt[y]]<0) ds[mt[y]] = ds[x]+1, q.push(mt[y]);
			else if(mt[y]<0) r = true;
		}
	}
	return r;
}

bool dfs(int x)
{
	for(int y:g[x]) if(mt[y]<0 or (ds[mt[y]] == ds[x]+1 and dfs(mt[y])))
	{
		mt[y] = x; mt2[x] = y;
		return true;
	}
	ds[x] = 1<<30;
	return false;
}

int mm()
{
	int r = 0;
	memset(mt, -1, sizeof(mt)); memset(mt2, -1, sizeof(mt2));
	while(bfs())
	{
		forn(i, n) if(mt2[i]<0) r += dfs(i);
	}
	return r;
}

//TIRAR mm() ANTES
//MM = max_flow = min_cut
vector<pii> mm_edges()
{
	vector<pii> ret;

	forn(x, n)	//x: todos los nodos izquierdos
	{
		if(mt2[x] != -1)
		{
			ret.pb({x, mt2[x]+n});
		}
	}

	return ret;
}
