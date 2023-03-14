// https://codeforces.com/contest/704/problem/D

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

const ll MOD = 1e9+7;
const ld EPS = 1e-9;
const ld PI = acosl(-1);

#define MAXN 200050
#define INF (1LL<<60)

//Max flow en O(V^2 E)

//dist: una vez que tiramos el flujo, me dice la distancia desde S, sin ponderar

//Las aristas e de la red residual tienen e.cap = 0 y e.f = -(flujo en la otra direccion).
//Por ejemplo, si la arista u-v termina tirando 3 de flujo, la arista v-u de la residual tiene -3.

struct Dinic
{
	int nodes, src, dst;
	vector<int> dist, q, work;
	struct edge {int to, rev; ll f, cap, id;};		//Se puede agregar un bool is_back, y solo hay que modificar add_edge
	vector<vector<edge>> g;
	vector<ll> dd;
	
    Dinic(int x) : nodes(x), dist(x+2), q(x+2), work(x+2), g(x+2), dd(x+2) {}
	
    void add_edge(int s, int t, ll cap, ll mincap = 0, int id = -1)
    {
		mincap = max(mincap, 0LL);
		if(mincap>cap){puts("-1");exit(0);}
		assert(mincap<=cap);
		dd[s] += mincap;
		dd[t] -= mincap;
		g[s].pb((edge){t, sz(g[t]),   0, cap-mincap, id});
		g[t].pb((edge){s, sz(g[s])-1, 0, 0, -1});
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

	ll max_flow_min_cap(int s, int t)
	{
		add_edge(t, s, INF);
		
		ll w = 0;
		
		nodes += 2;

		forn(i, nodes)
		{
			if(dd[i] > 0) add_edge(i, nodes-1, dd[i]), w += dd[i];
			else if(dd[i]<0) add_edge(nodes-2, i, -dd[i]);
		}


		if(max_flow(nodes-2, nodes-1) != w) return -1;
		
		nodes -= 2;
		
		forn(i, nodes) if(dd[i]) g[i].pp();

		return max_flow(s,t);
	}
};


int n,m,rr,bb;
int x[100005],y[100005],qx[100005],qy[100005];
vector<int> xs,ys;
int a[100005],b[100005];
char ans[100005];


void solve()
{
	scanf("%d%d%d%d",&n,&m,&rr,&bb);
	forr(i,0,n)scanf("%d%d",x+i,y+i),xs.pb(x[i]),ys.pb(y[i]);
	sort(xs.begin(),xs.end());xs.erase(unique(xs.begin(),xs.end()),xs.end());
	sort(ys.begin(),ys.end());ys.erase(unique(ys.begin(),ys.end()),ys.end());
	forr(i,0,n){
		x[i]=lower_bound(xs.begin(),xs.end(),x[i])-xs.begin();
		y[i]=lower_bound(ys.begin(),ys.end(),y[i])-ys.begin();
		qx[x[i]]++;qy[y[i]]++;
	}
	forr(i,0,n)a[i]=b[i]=1<<29;
	while(m--){
		int t,l,d;
		scanf("%d%d%d",&t,&l,&d);
		if(t==1){
			int k=lower_bound(xs.begin(),xs.end(),l)-xs.begin();
			if(k<sz(xs)&&xs[k]==l)a[k]=min(a[k],d);
		}
		else {
			int k=lower_bound(ys.begin(),ys.end(),l)-ys.begin();
			if(k<sz(ys)&&ys[k]==l)b[k]=min(b[k],d);
		}
	
	}

	Dinic net(2+sz(xs)+sz(ys));

	forr(i,0,sz(xs))net.add_edge(0,2+i,(qx[i]+a[i])/2,(qx[i]-a[i]+1)/2);
	forr(i,0,sz(ys))net.add_edge(2+sz(xs)+i,1,(qy[i]+b[i])/2,(qy[i]-b[i]+1)/2);
	forr(i,0,n)net.add_edge(2+x[i],2+sz(xs)+y[i],1,0,i);
	
	//puts("holis");
	int r=net.max_flow_min_cap(0,1);
	if(r<0){puts("-1");return;}
	if(r<(n+1)/2){
		assert(0);
		//printf(" %d %d\n",r,dd[0]);
	}
	printf("%lld\n",1LL*r*min(rr,bb)+1LL*(n-r)*max(rr,bb));
	forr(i,0,sz(xs))for(auto e:net.g[2+i])if(e.id>=0){
		if(e.f){
			if(rr<bb)ans[e.id]='r';
			else ans[e.id]='b';
		}
		else {
			if(rr<bb)ans[e.id]='b';
			else ans[e.id]='r';
		}
	}
	puts(ans);
}

int main(){
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

	//ios::sync_with_stdio(false);
	//cin.tie(nullptr);

	solve();
}
