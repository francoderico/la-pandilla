vector<int> g[MAXN];
bool vis[MAXN], art[MAXN];  	//art[i] = true sii i es de articulación
int low[MAXN], tag[MAXN];
int parent[MAXN];   		//Inicializar en -1
int idx = 0;

void dfs(int v)
{
    vis[v] = true;
    tag[v] = low[v] = idx ++;

    for(auto x : g[v]) if(x != parent[v])
    {
        if(not vis[x])
        {
            parent[x] = v;

            dfs(x);

            if(low[x] >= tag[v]) art[v] = true;
            low[v] = min(low[v], low[x]);
        }
        else
        {
            low[v] = min(low[v], tag[x]);
        }
    }
}

void articulation(int v)    //Uso: forn(i, n) if(not vis[i]) articulation(i);
{
    dfs(v);
    
    int hijos = 0;
    for(auto x : g[v]) if(parent[x] == v) hijos ++;

    if(hijos > 1) art[v] = true;
    else          art[v] = false;
}
