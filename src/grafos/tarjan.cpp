vector<int> g[MAXN];     bool vis[MAXN];
int low[MAXN], scc[MAXN];  //Inicializar en -1
int idx = 0, cant = 0;
stack<int> s;
void dfs(int v){
	vis[v] = true;
	int tag = low[v] = idx ++;
	s.push(v);
	for(auto x : g[v]){
		if(vis[x] and scc[x] > -1) continue;
		if(not vis[x]) dfs(x);
		low[v] = min(low[v], low[x]);
	}
	if(low[v] == tag){
		while(1){
			int x = s.top(); s.pop();
			scc[x] = cant;
			if(x == v) break;
		}
		cant ++;
	}
}