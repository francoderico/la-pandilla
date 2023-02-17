// https://codeforces.com/problemset/problem/884/F

#include <bits/stdc++.h>
using namespace std;

#define forr(i,a,b) for(int i=int(a);i<int(b);++i)
#define forn(i,n) forr(i,0,n)
#define dforr(i,a,b) for(int i=int(b)-1;i>=int(a);--i)
#define dforn(i,n) dforr(i,0,n)
#define db(v) cerr<<#v" = "<<(v)<<'\n'
#define vecp(v) cerr<<#v<<" = "; for(auto ee:v)cerr<<ee<<' '; cerr<<'\n'
#define nn cout<<'\n'
#define sz(v) (int(v.size()))
#define all(v) v.begin(), v.end()
#define pb push_back
#define pp pop_back
#define fst first
#define snd second

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<ll> vll;

const ll MAXN = 110;
const ll INF = 1e18+100;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;
const ld PI = acosl(-1);

//De todos los flujos máximos, me da el de costo mínimo en O(n^2 m^2)
typedef ll tf;
typedef ll tc;
const tf INFFLOW = 1e9;
const tc INFCOST = 1e9;
struct MCF
{
	int n;
	vector<tc> prio, pot; vector<tf> curflow; vector<int> prevedge, prevnode;
	priority_queue<pair<tc, int>, vector<pair<tc, int>>, greater<pair<tc, int>>> q;
	struct edge{int to, rev; tf f, cap; tc cost;};
	vector<vector<edge>> g;
	MCF(int n) : n(n), prio(n), curflow(n), prevedge(n), prevnode(n), pot(n), g(n) {}
    
	void add_edge(int s, int t, tf cap, tc cost)
    {
		g[s].pb((edge){t, sz(g[t]), 0, cap, cost});
		g[t].pb((edge){s, sz(g[s])-1, 0, 0, -cost});
	}
    
	pair<tf, tc> get_flow(int s, int t)
    {
		tf flow = 0; tc flowcost = 0;
		while(1)
        {
			q.push({0, s});
			fill(all(prio), INFCOST); 
			prio[s] = 0; curflow[s] = INFFLOW;
			while(!q.empty())
            {
				auto cur = q.top();
				tc d = cur.fst;
				int u = cur.snd;
				q.pop();
				if(d != prio[u]) continue;
				for(int i = 0; i < sz(g[u]); ++i)
                {
					edge &e = g[u][i];
					int v = e.to;
					if(e.cap <= e.f) continue;
					tc nprio = prio[u] + e.cost + pot[u] - pot[v];
					if(prio[v] > nprio)
                    {
						prio[v] = nprio;
						q.push({nprio, v});
						prevnode[v] = u; prevedge[v] = i;
						curflow[v] = min(curflow[u], e.cap-e.f);
					}
				}
			}
			if(prio[t] == INFCOST) break;
			forn(i, n) pot[i] += prio[i];
			tf df = min(curflow[t], INFFLOW-flow);
			flow += df;
			for(int v = t; v != s; v = prevnode[v])
            {
				edge &e = g[prevnode[v]][prevedge[v]];
				e.f += df; g[v][e.rev].f -= df;
				flowcost += df*e.cost;
			}
		}
		return {flow,flowcost};
	}
};


int b[MAXN];
unordered_map<char, int> cant;

//El flujo máximo va a ser n, y va a representar dónde ubicamos cada letra.
//El costo va a representar lo que perdemos de beauty, resulta ans = suma(b[i]) - cost.
//En cada posición puedo poner 1 letra, con costo 0 si es igual a la que había ahí originalmente, y b[i]
//si es distinta.
//Ponemos un nodo por cada letra del alfabeto, y tiramos la arista (s, letra, cant de esa letra, 0).
//Si tenemos, por ejemplo, 5 letras 'a', no podemos poner una en la posición i y otra en n/2-i-1 porque quedaría palíndromo.
//Entonces metemos un nodo v en el medio para kimitar esto, y para cada letra tiramos (letra, v, 1, 0), y para las 2 posiciones
//i y n-i-1 tiramos (v, i, 1, costo), con costo 0 si es igual a la que había ahí originalmente, y b[i] si es distinta.
//Y para cada posición i tiramos (i, t, 1, 0).
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
        net.add_edge(s, u, c, 0);

		forn(i, n/2)
		{
			int v = sz(cant) + n/2*u        +   i;
			
			net.add_edge(u, v, 1, 0);

			int w = sz(cant) + n/2*sz(cant) + 2*i;

			net.add_edge(v, w,   1, letra == a[i]     ? 0 : b[i]);
			net.add_edge(v, w+1, 1, letra == a[n-i-1] ? 0 : b[n-i-1]);
		}

		u ++;
    }

	forn(i, n/2)
	{
		int w = sz(cant) + n/2*sz(cant) + 2*i;
		net.add_edge(w,   t, 1, 0);
		net.add_edge(w+1, t, 1, 0);
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
