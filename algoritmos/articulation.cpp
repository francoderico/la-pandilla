vector<int> g[MAXN];
bool vis[MAXN], art[MAXN];  	//art[i] = true sii i es de articulación
int low[MAXN], tag[MAXN];
int parent[MAXN];   		//Inicializar en -1
int idx = 0;

void dfs(int v)
{
    vis[v] = true;
    tag[v] = low[v] = idx ++;
    int hijos = 0;

    for(auto x : g[v])
    {
        if(not vis[x])
        {
            parent[x] = v;
            if(parent[v] == -1) hijos ++;

            dfs(x);
            
            if(low[x] >= tag[v]) art[v] = true;
            low[v] = min(low[v], low[x]);
        }
        else if(v != parent[x])
        {
            low[v] = min(low[v], tag[x]);
        }
    }

    //Caso especial de la raíz
    //Si tiene más de un hijo en el DFS tree, es de articulación.
    if(parent[v] == -1)
    {
        if(hijos > 1) art[v] = true;
        else          art[v] = false;
    }
}

