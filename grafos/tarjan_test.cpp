//https://www.spoj.com/problems/WEBISL/

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

const ll MAXN = 2e5+100;
const ll INF = 1e18+100;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;
const ld PI = acosl(-1);



vector<int> g[MAXN];
bool vis[MAXN];
int low[MAXN];
int scc[MAXN];  //Inicializar en -1
int idx = 0, cant = 0;
stack<int> s;

void dfs(int v)
{
    vis[v] = true;
    int tag = low[v] = idx ++;
    s.push(v);

    for(auto x : g[v])
    {
        if(vis[x] and scc[x] > -1) continue;

        if(not vis[x]) dfs(x);

        low[v] = min(low[v], low[x]);
    }

    if(low[v] == tag)
    {
        while(1)
        {
            int x = s.top(); s.pop();
            scc[x] = cant;
            if(x == v) break;
        }

        cant ++;
    }
}


int mi[MAXN];

void solve()
{
    int n, m; cin >> n >> m;
    forn(i, m)
    {
        int a, b; cin >> a >> b;
        g[a].pb(b);
    }

    forn(i, n) scc[i] = -1;

    forn(i, n) if(not vis[i]) dfs(i);

    forn(i, n) mi[i] = -1;

    forn(i, n)
    {
        if(mi[scc[i]] != -1) scc[i] = mi[scc[i]];
        else                 mi[scc[i]] = i, scc[i] = i;
    }

    forn(i, n) cout << scc[i], nn;
}




//___________________________

int main()
{
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    solve();
    
    return 0;
}
