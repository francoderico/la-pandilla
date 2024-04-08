// https://codeforces.com/contest/884/problem/F

#include <bits/stdc++.h>
using namespace std;

#define forr(i,a,b) for(int i=int(a);i<int(b);++i)
#define forn(i,n) forr(i,0,n)
#define dforr(i,a,b) for(int i=int(b)-1;i>=int(a);--i)
#define dforn(i,n) dforr(i,0,n)
#define fore(e,c) for(const auto &e : (c))
#define db(v) cerr<<#v" = "<<(v)<<'\n'
#define nn cout<<'\n'
#define sz(v) (int(v.size()))
#define all(v) begin(v), end(v)
#define pb push_back
#define pp pop_back
#define fst first
#define snd second

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

const ll MAXN = 110;
const ll INF = 1e18+100;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;
const ld PI = acosl(-1);

typedef ll tf;          typedef ll tc;
const tf INFFLOW = 1e9; const tc INFCOST = 1e9;
struct MCF { // O(n^2 * m^2), no se banca ciclos de costo negativo
	int n;
	vector<tc> prio, pot; vector<tf> curflow; vector<int> prevedge, prevnode;
	priority_queue<pair<tc, int>, vector<pair<tc, int>>,
	               greater<pair<tc, int>>> q;
	struct edge{int to, rev; tf f, cap; tc cost;};
	vector<vector<edge>> g; vector<tf> dd; tc dc = 0;
	MCF(int n_) : n(n_), prio(n_+2), pot(n_+2), curflow(n_+2),
	              prevedge(n_+2), prevnode(n_+2), g(n_+2), dd(n_+2) {}
	void add_edge(int s, int t, tc cost, tf cap, tf mincap = 0){
		// assert(0 <= mincap and mincap <= cap);
		dd[s] += mincap; dd[t] -= mincap; dc += mincap*cost;
		g[s].pb((edge){t, sz(g[t]),   0, cap-mincap, cost});
		g[t].pb((edge){s, sz(g[s])-1, 0, 0,         -cost});
	}
	pair<tf, tc> get_flow(int s, int t){
		tf flow = 0; tc cost = 0;
		while(1){
			q.push({0, s});
			fill(all(prio), INFCOST); 
			prio[s] = 0; curflow[s] = INFFLOW;
			while(not q.empty()){
				auto [d, u] = q.top();
				q.pop();
				if(d != prio[u]) continue;
				forn(i, sz(g[u])){
					auto& [v, _, f, cap, c] = g[u][i];
					if(cap <= f) continue;
					tc nprio = prio[u] + c + pot[u] - pot[v];
					if(prio[v] > nprio){
						prio[v] = nprio;
						q.push({nprio, v});
						prevnode[v] = u; prevedge[v] = i;
						curflow[v] = min(curflow[u], cap-f);
					}
				}
			}
			if(prio[t] == INFCOST) break;
			forn(i, n) pot[i] += prio[i];
			tf df = min(curflow[t], INFFLOW-flow);
			flow += df;
			for(int v = t; v != s; v = prevnode[v]){
				auto& [_, rev, f, cap, c] = g[prevnode[v]][prevedge[v]];
				f += df; g[v][rev].f -= df;
				cost += df*c;
			}
		}
		return {flow, cost};
	}
	pair<tf, tc> get_flow_min_cap(int s, int t){
		// cost(aristas en ciclo) = f*c, como todas
		add_edge(t, s, 0, INFFLOW); ll w = 0;
		forn(i, n){
			if     (dd[i] > 0) add_edge(i, n+1, 0,  dd[i]), w += dd[i];
			else if(dd[i] < 0) add_edge(n, i,   0, -dd[i]);
		}
		auto [f, c] = get_flow(n, n+1);
		if(f != w) return {-1, -1};
		forn(i, n) if(dd[i] != 0) g[i].pp();
		auto [ff, cc] = get_flow(s, t); g[s].pp(), g[t].pp();
		return {ff, c + cc + dc};
	}
};


int b[MAXN];
unordered_map<char, int> cant;

//El flujo maximo va a ser n, y va a representar donde ubicamos cada letra.
//El costo va a representar lo que perdemos de beauty, resulta ans = suma(b[i]) - cost.
//En cada posicion puedo poner 1 letra, con costo 0 si es igual a la que habia ahi originalmente, y b[i]
//si es distinta.
//Ponemos un nodo por cada letra del alfabeto, y tiramos la arista (s, letra, cant de esa letra, 0).
//Si tenemos, por ejemplo, 5 letras 'a', no podemos poner una en la posicion i y otra en n/2-i-1 porque quedaria palindromo.
//Entonces metemos un nodo v en el medio para kimitar esto, y para cada letra tiramos (letra, v, 1, 0), y para las 2 posiciones
//i y n-i-1 tiramos (v, i, 1, costo), con costo 0 si es igual a la que habia ahi originalmente, y b[i] si es distinta.
//Y para cada posicion i tiramos (i, t, 1, 0).
void solve()
{
    int n; cin >> n;
    string a; cin >> a;
	int suma = 0;
    forn(i, n) cin >> b[i], suma += b[i];

    forn(i, n) cant[a[i]] ++;

	MCF net(sz(cant) + n/2*sz(cant) + n + 2);
	
	int s = sz(cant) + n/2*sz(cant) + n, t = s + 1;
    
	int u = 0;
    for(auto [letra, c] : cant)
    {
        net.add_edge(s, u, 0, c);

		forn(i, n/2)
		{
			int v = sz(cant) + n/2*u        +   i;
			
			net.add_edge(u, v, 0, 1);

			int w = sz(cant) + n/2*sz(cant) + 2*i;

			net.add_edge(v, w,   letra == a[i]     ? 0 : b[i],     1);
			net.add_edge(v, w+1, letra == a[n-i-1] ? 0 : b[n-i-1], 1);
		}

		u ++;
    }

	forn(i, n/2)
	{
		int w = sz(cant) + n/2*sz(cant) + 2*i;
		net.add_edge(w,   t, 0, 1);
		net.add_edge(w+1, t, 0, 1);
	}

	auto [flow, cost] = net.get_flow(s, t);
	assert(flow == n);
	cout << suma - cost, nn;
}

int main(){
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    
    return 0;
}
