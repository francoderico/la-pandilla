vector<int> g[MAXN];
bool vis[MAXN], art[MAXN];  //art[i] = true sii i es de articulacion
int low[MAXN], tag[MAXN], parent[MAXN]; //Inicializar en -1
int idx = 0;
void dfs(int v){
	vis[v] = true;
	tag[v] = low[v] = idx ++;
	for(auto x : g[v]) if(x != parent[v]){
		if(not vis[x]){
			parent[x] = v;
			dfs(x);
			if(low[x] >= tag[v]) art[v] = true;
			low[v]  = min(low[v], low[x]);
		}
		else low[v] = min(low[v], tag[x]); //NO es igual a la de arriba
		if(low[x] <= tag[v]) /* La arista v-x NO es bridge - inicialmente todas lo son */
	}
}
void articulation(){// LLena el array art - considera a los nodos de grado 0 como false
	forn(v, n) if(not vis[v]){
		dfs(v);
		int hijos = 0;
		for(auto x : g[v]) if(parent[x] == v) hijos ++;
		art[v] = hijos > 1;
	}
}
