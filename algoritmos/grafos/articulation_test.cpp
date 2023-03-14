// https://www.spoj.com/problems/SUBMERGE/

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

const ll MAXN = 1e4+100;
const ll INF = 1e18+100;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;
const ld PI = acosl(-1);

int n, m;
vector<int> g[MAXN];
bool vis[MAXN], art[MAXN];  	//art[i] = true sii i es de articulacion
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

    art[v] = hijos > 1;
}


void solve()
{
    forn(i, n) g[i].clear(), tag[i] = low[i] = vis[i] = art[i] = 0, parent[i] = -1;
    idx = 0;

    forn(i, m)
    {
        int a, b; cin >> a >> b; a --, b --;
        g[a].pb(b), g[b].pb(a);
    }
    
    articulation(0);

    int ans = 0;
    forn(i, n) if(art[i]) ans ++;
    cout << ans, nn;
}




//___________________________

int main()
{
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    

    cin >> n >> m;
    while(n or m)
    {
        solve();
        cin >> n >> m;
    }
    
    return 0;
}
