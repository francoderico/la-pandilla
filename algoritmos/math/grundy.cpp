// Dado un DAG, guarda en grundy[i] el grundy del juego si comienza en el nodo i
// O(m log m)

bool vis[MAXN];
int grundy[MAXN];
vector<int> g[MAXN];

void dfs(int v)
{
	vis[v] = true;

	vector<int> s;

	for(auto x : g[v])
	{
		if(not vis[x]) dfs(x);
		s.pb(grundy[x]);
	}
	
	sort(all(s));
	auto en = unique(all(s));
	
	int sz = en-s.begin();

	forn(i, sz) if(s[i] > i)
	{
		grundy[v] = i;
		return;
	}

	grundy[v] = sz;
}



//------------------------------------------------------


// Otro enfoque, en O(n*MAXG + m)
// MAXG es la menor potencia de 2 mayor a sqrt(m).
// Es decir, 1 mas que el maximo xor de grundys alcanzable.
const int MAXG = 512;
bool vis[MAXN];
int grundy[MAXN];
vector<int> g[MAXN];

void dfs(int v)
{
	vis[v] = true;

	vector<bool> reach(MAXG, 0);

	for(auto x : g[v])
	{
		if(not vis[x]) dfs(x);
		reach[grundy[x]] = true;
	}
	
	forn(i, MAXG) if(not reach[i])
	{
		grundy[v] = i;
		return;
	}
}