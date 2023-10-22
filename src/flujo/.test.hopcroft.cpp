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

struct Hopcroft{ // Matching maximo en bipartito en O(sqrt(n)*m)
	int n, m;
	vector<vector<int>> g;    // [0,n) -> [0,m)
	vector<int> mt, inv, ds;  // mt  : [0..n) -> [0..m) contiene el matching n-m
	                          // inv : [0..m) -> [0..n) contiene el matching inverso	
	void init(int n_, int m_) { n = n_, m = m_, g.resize(n_); }
	void add_edge(int u, int v) { g[u].pb(v); }
	bool bfs(){
		ds.assign(n, -1); queue<int> q;
		forn(i, n) if(mt[i] < 0) ds[i] = 0, q.push(i);
		bool r = false;
		while(not q.empty()){
			int x = q.front(); q.pop();
			for(auto y : g[x]){
				if(inv[y] >= 0 and ds[inv[y]] < 0) ds[inv[y]] = ds[x]+1, q.push(inv[y]);
				else if(inv[y] < 0) r = true;
			}
		}
		return r;
	}
	bool dfs(int x){
		for(auto y : g[x]) if(inv[y] < 0 or (ds[inv[y]] == ds[x]+1 and dfs(inv[y]))){
			inv[y] = x; mt[x] = y;
			return true;
		}
		ds[x] = 1<<30;
		return false;
	}
	int mm(){
		int r = 0;
		mt.assign(n, -1), inv.assign(m, -1);
		while(bfs()) forn(i, n) if(mt[i]<0) r += dfs(i);
		return r;
	}
};

void solve()
{
	int n, m, p; cin >> n >> m >> p;

	Hopcroft h; h.init(n, m);

	forn(_, p)
	{
		int a, b; cin >> a >> b; a --, b --;
		h.add_edge(a, b);
	}

	cout << h.mm(), nn;
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
