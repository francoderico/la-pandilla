// https://www.spoj.com/problems/MATCHING/

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

//Matching maximo en bipartito en O(sqrt(V) E)
//Caso especial de Dinic pero mas rapido, menos memoria y mas corto
//Los vertices izquierdos estan numerados en [0, n), los derechos en [0, m)
int n, m;               //SETEAR
vector<int> g[MAXN];    // [0,n)->[0,m)
int mt[MAXN], mt2[MAXN], ds[MAXN];

bool bfs()
{
	queue<int> q;
	memset(ds, -1, sizeof(ds));
	forn(i, n) if(mt2[i]<0) ds[i] = 0, q.push(i);
	bool r = false;
	while(not q.empty())
    {
		int x = q.front(); q.pop();
		for(int y:g[x])
        {
			if(mt[y]>=0 and ds[mt[y]]<0) ds[mt[y]] = ds[x]+1, q.push(mt[y]);
			else if(mt[y]<0) r = true;
		}
	}
	return r;
}

bool dfs(int x)
{
	for(int y:g[x]) if(mt[y]<0 or (ds[mt[y]] == ds[x]+1 and dfs(mt[y])))
    {
		mt[y] = x; mt2[x] = y;
		return true;
	}
	ds[x] = 1<<30;
	return false;
}

int mm()
{
	int r = 0;
	memset(mt, -1, sizeof(mt)); memset(mt2, -1, sizeof(mt2));
	while(bfs())
    {
		forn(i, n) if(mt2[i]<0) r += dfs(i);
	}
	return r;
}



void solve()
{
    int p; cin >> n >> m >> p;

    forn(_, p)
    {
        int a, b; cin >> a >> b; a --, b --;
        g[a].pb(b);
    }

    cout << mm(), nn;
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
