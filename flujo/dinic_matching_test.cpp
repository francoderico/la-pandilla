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

struct Dinic
{
	int nodes, src, dst;
	vector<int> dist, q, work;
	struct edge {int to, rev; ll f, cap;};
	vector<vector<edge>> g;
	
    Dinic(int x) : nodes(x), dist(x), q(x), work(x), g(x) {}
	
    void add_edge(int s, int t, ll cap)
    {
		g[s].pb((edge){t, sz(g[t]), 0, cap});
		g[t].pb((edge){s, sz(g[s])-1, 0, 0});
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



Dinic net(2*MAXN+2);

void solve()
{
    int n, m, p; cin >> n >> m >> p;
    int s = n+m, t = n+m+1;

    forn(a, n) net.add_edge(s, a, 1);
    forr(b, n, n+m) net.add_edge(b, t, 1);

    forn(_, p)
    {
        int a, b; cin >> a >> b; a --, b --; b += n;
        net.add_edge(a, b, INF);
    }


    cout << net.max_flow(s, t), nn;
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
