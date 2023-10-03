// Min cut: nodes with dist>=0 (S y todos los alcanzables) vs nodes with dist == -1
// Matching maximo
// min vertex cover: left nodes with dist == -1 + right nodes with dist>0
// MAX independent set: complemento del mvc, o sea, left nodes with dist>0 + right nodes with dist == -1
// min edge cover: MM + una arista cualquiera por cada otro nodo (es imposible sii hay algun nodo sin aristas)
// Feasible (red fuertemente conexa con restricciones de minimo y maximo en cada arista)

// Conjunto del min cut de s, sin incluir al propio s
vector<int> min_cut_s(Dinic& ne, int nodes){
	vector<int> ret;
	forn(x, nodes-2) if(ne.dist[x] > 0) ret.pb(x);
	return ret; 
}

// Conjunto del min cut de t, sin incluir al propio t
vector<int> min_cut_t(Dinic& ne, int nodes){
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
vector<pii> mm_edges(Dinic& ne, int nodes){
	vector<pii> ret;
	int s = nodes-2;
	for(auto e : ne.g[s]){	//x: todos los nodos izquierdos
		int x = e.to;
		if(e.f == 1){		//La arista desde s esta usada
			for(auto d : ne.g[x]) if(d.f == 1){	//Busco la arista que salga de x y este usada
				ret.pb({x, d.to});
				break;
			}
		}
	}
	return ret;
}



//------------------------------------------------------



//MM
vector<int> min_vertex_cover(Dinic& ne, int nodes){
	vector<int> ret;
	int s = nodes-2, t = nodes-1;
	for(auto e : ne.g[s]){	//x: todos los nodos izquierdos
		int x = e.to;
		if(ne.dist[x] == -1) ret.pb(x);		//x es del corte t
	}
	for(auto e : ne.g[t]){	//x: todos los nodos derechos
		int x = e.to;
		if(ne.dist[x] > 0)   ret.pb(x);		//x es del corte s
	}
	return ret;
}



//------------------------------------------------------



//n - MM
//Complemento del mvc
vector<int> max_independent_set(Dinic& ne, int nodes){
	vector<int> ret;
	int s = nodes-2, t = nodes-1;
	for(auto e : ne.g[s]){	//x: todos los nodos izquierdos
		int x = e.to;
		if(ne.dist[x] > 0)   ret.pb(x);		//x es del corte s
	}
	for(auto e : ne.g[t]){	//x: todos los nodos derechos
		int x = e.to;
		if(ne.dist[x] == -1) ret.pb(x);		//x es del corte s
	}
	return ret;
}



//------------------------------------------------------



//n - MM
vector<pii> min_edge_cover(Dinic& ne, int nodes){
	vector<pii> ret;
	int s = nodes-2, t = nodes-1; 
	forn(x, s) if(sz(ne.g[x]) == 1) return ret;		//No se puede, hay algun nodo sin aristas (solo esta unido con s o con t)
	for(auto e : ne.g[s]){	//x: todos los nodos izquierdos
		int x = e.to;
		if(e.f == 1){		//La arista s-x esta usada, o sea que x parte del MM: agrego su arista
			for(auto d : ne.g[x]) if(d.f == 1){
				ret.pb({x, d.to});
				break;
			}
		}
		else{				//Si NO esta usada, x NO es parte del MM: agrego una arista cualquiera
			for(auto d : ne.g[x]){
				if(d.to != s){
					ret.pb({x, d.to});
					break;
				}
			}
		}
	}
	
	for(auto e : ne.g[t]){	//x: todos los nodos derechos
		int x = e.to;
		if(e.f != -1){		//La arista x-t NO esta usada, o sea que x NO parte del MM: agrego una arista cualquiera
			for(auto d : ne.g[x]){
				if(d.to != t){
					ret.pb({x, d.to});
					break;
				}
			}
		}
	}
	
	return ret;
}
