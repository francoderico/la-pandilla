// https://www.spoj.com/problems/EC_P/

#include <bits/stdc++.h>
using namespace std;

#define forr(i,a,b) for(int i=int(a);i<int(b);++i)
#define forn(i,n) forr(i,0,n)
#define dforr(i,a,b) for(int i=(b)-1;i>=(a);--i)
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

const ll MAXN = 700+100;
const ll INF = 1e18+100;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;
const ld PI = acosl(-1);

int n;
vector<int> g[MAXN];
bool vis[MAXN], art[MAXN];  //art[i] = true sii i es de articulacion
int low[MAXN], tag[MAXN];
int parent[MAXN];	        //Inicializar en -1
int idx = 0;
bool M[MAXN][MAXN];
void dfs(int v){
	vis[v] = true;
	tag[v] = low[v] = idx ++;
	for(auto x : g[v]) if(x != parent[v]){
		if(not vis[x]){
			parent[x] = v;
			dfs(x);
			if(low[x] >= tag[v]) art[v] = true;
			low[v] = min(low[v], low[x]);
		}
		else low[v] = min(low[v], tag[x]); //NO es igual a la de arriba
		if(low[x] <= tag[v]) M[min(x, v)][max(x, v)] = false;
	}
}
// LLena el array art - considera a los nodos de grado 0 como false
void articulation(){
	forn(v, n) if(not vis[v]){
		dfs(v);
		int hijos = 0;
		for(auto x : g[v]) if(parent[x] == v) hijos ++;
		art[v] = hijos > 1;
	}
}


void clear(){
	forn(i, n){
		g[i].clear();
		vis[i] = art[i] = false;
		low[i] = tag[i] = 0;
		parent[i] = -1;
		forr(j, i, n) M[i][j] = false;
	}
	idx = 0;
}


void solve(){
	int m; cin >> n >> m;

	clear();

	forn(i, m){
		int a, b; cin >> a >> b; a --, b --;
		g[a].pb(b), g[b].pb(a);
		M[min(a, b)][max(a, b)] = true;
	}
	articulation();
	

	vector<pii> v;
	
	forn(i, n) forr(j, i, n) if(M[i][j]){
		v.pb({i, j});
	}

	int ans = sz(v);
	if(ans == 0){
		cout << "Sin bloqueos", nn;
		return;
	}

	cout << ans, nn;
	for(const auto &[a, b] : v) cout << a+1 << ' ' << b+1, nn;
}


//___________________________

int main()
{
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	
	int t; cin >> t; forr(c, 1, t+1){
		cout << "Caso #" << c, nn;
		solve();
	}
    
    return 0;
}