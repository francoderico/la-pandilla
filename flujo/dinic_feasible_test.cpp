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

const ll MAXN = 210;
const ll MAXM = MAXN*MAXN;
const ll INF = 1e18+100;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;
const ld PI = acosl(-1);

//Max flow en O(V^2 E)

//dist: una vez que tiramos el flujo, me dice la distancia desde S, sin ponderar

//Las aristas e de la red residual tienen e.cap = 0 y e.f = -(flujo en la otra dirección).
//Por ejemplo, si la arista u-v termina tirando 3 de flujo, la arista v-u de la residual tiene -3.

//Min cut: nodes with dist>=0 (S y todos los alcanzables) vs nodes with dist == -1
//Matching máximo
//min vertex cover: left nodes with dist == -1 + right nodes with dist>0
//MAX independent set: complemento del mvc, o sea, left nodes with dist>0 + right nodes with dist == -1
//min edge cover: MM + una arista cualquiera por cada otro nodo (es imposible sii hay algún nodo sin aristas)
struct Dinic
{
	int nodes, src, dst;
	vector<int> dist, q, work;
	struct edge {int to, rev; ll f, cap; bool is_back;};
	vector<vector<edge>> g;
	
    Dinic(int x) : nodes(x), dist(x), q(x), work(x), g(x) {}
	
    void add_edge(int s, int t, ll cap)
    {
		g[s].pb((edge){t, sz(g[t]), 0, cap, false});
		g[t].pb((edge){s, sz(g[s])-1, 0, 0, true});
	}
	
    bool dinic_bfs()
    {
		fill(all(dist), -1); dist[src] = 0;
		int qt = 0; q[qt++] = src;
		for(int qh = 0; qh<qt; qh++)
        {
			int u = q[qh];
			forn(i, sz(g[u]))
            {
				edge &e = g[u][i]; int v = g[u][i].to;
				if(dist[v]<0 and e.f<e.cap) dist[v] = dist[u]+1, q[qt++] = v;
			}
		}
		return dist[dst] >= 0;
	}
	
    ll dinic_dfs(int u, ll f)
    {
		if(u == dst)return f;
		for(int &i = work[u]; i<sz(g[u]); i++)
        {
			edge &e = g[u][i];
			if(e.cap <= e.f)continue;
			int v = e.to;
			if(dist[v] == dist[u]+1)
            {
				ll df = dinic_dfs(v, min(f, e.cap-e.f));
				if(df > 0){e.f += df; g[v][e.rev].f -= df; return df;}
			}
		}
		return 0;
	}
	
    ll max_flow(int _src, int _dst)
    {
		src = _src; dst = _dst;
		ll result = 0;
		while(dinic_bfs())
        {
			fill(all(work), 0);
			while(ll delta = dinic_dfs(src, INF)) result += delta;
		}
		return result;
	}

};


ll M[MAXN];             //suma(l entrantes) - suma(l salientes)   --  se llena en feasible
int a[MAXM], b[MAXM];   //aristas a[i]-b[i]
ll l[MAXM], u[MAXM];    //con capacidad mínima l[i] y máxima u[i]
ll mando[MAXM];         //Cuánto flujo mando por cada arista
map<pii, int> ind;      //Para cada arista u-v, me da su i tal que a[i] = u y b[i] = v


//Chequea si una SCC de flujo, sin s ni t, con restricciones de capacidades mínimas y máximas en cada arista
//tiene algún flujo válido, y lo reconstruye en el array mando
//n = cantidad de nodos
//m = cantidad de aristas
bool feasible(Dinic& ne, int n, int m)
{
    forn(i, m)
    {
        ne.add_edge(a[i], b[i], u[i]-l[i]); //Agregamos la arista con capacidad u-l
        M[a[i]] -= l[i];
        M[b[i]] += l[i];

        ind[{a[i], b[i]}] = i;
    }

    int s = n, t = n+1, nodes = n+2;
    
    forn(i, n)
    {
        if(M[i] > 0) ne.add_edge(s, i, M[i]);
        if(M[i] < 0) ne.add_edge(i, t, -M[i]);
    }
    
    ne.max_flow(s, t);
    
    for(auto e : ne.g[s]) if(e.f < e.cap) return false;

    forn(i, n)
    {
        for(auto e : ne.g[i])
        {
            int j = e.to;
            if(j == s or j == t or e.is_back) continue;
            
            mando[ind[{i, j}]] = l[ind[{i, j}]] + e.f;
        }
    }
    
    return true;
}

Dinic net(MAXN+2);

void solve()
{
    int n, m; cin >> n >> m;

    forn(i, m)
    {
        cin >> a[i] >> b[i]; a[i] --, b[i] --;
        cin >> l[i] >> u[i];
    }

    if(feasible(net, n, m))
    {
        cout << "YES", nn;

        forn(i, m) cout << mando[i], nn;
    }
    else
    {
        cout << "NO", nn;
    }
}

int main(){
    freopen("cooling.in", "r", stdin);
    freopen("cooling.out", "w", stdout);

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    
    return 0;
}