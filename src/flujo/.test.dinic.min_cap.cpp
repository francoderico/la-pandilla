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

struct Dinic{ // O(n^2 * m)
	int n, src, dst;
	vector<int> dist, q, work; // dist: distancias desde S, sin ponderar
	struct edge {int to, rev; ll f, cap; int id;};
	vector<vector<edge>> g; vector<ll> dd;
	Dinic(int n_) : n(n_), dist(n_+2), q(n_+2), work(n_+2), g(n_+2), dd(n_+2) {} // Deja espacio para el min_cap
	void add_edge(int s, int t, ll cap, ll mincap = 0, int id = -1){
		// assert(0 <= mincap and mincap <= cap);
		mincap = max(mincap, 0LL);
		if(mincap>cap){puts("-1");exit(0);}
		dd[s] += mincap; dd[t] -= mincap;
		g[s].pb((edge){t, sz(g[t]),   0, cap-mincap, id});
		g[t].pb((edge){s, sz(g[s])-1, 0, 0, -1}); // Residual: cap=0 y flujo negativo
	}
	bool dinic_bfs(){
		fill(all(dist), -1); dist[src] = 0;
		int qt = 0; q[qt++] = src;
		for(int qh = 0; qh < qt; qh ++){
			int u = q[qh];
			fore(e, g[u]){
				int v = e.to;
				if(dist[v] < 0 and e.f < e.cap) dist[v] = dist[u]+1, q[qt++] = v;
			}
		}
		return dist[dst] >= 0;
	}	
	ll dinic_dfs(int u, ll f){
		if(u == dst) return f;
		for(int &i = work[u]; i < sz(g[u]); i ++){
			edge &e = g[u][i];
			if(e.cap <= e.f) continue;
			int v = e.to;
			if(dist[v] == dist[u]+1){
				ll df = dinic_dfs(v, min(f, e.cap - e.f));
				if(df > 0){
					e.f += df; g[v][e.rev].f -= df;
					return df;
				}
			}
		}
		return 0;
	}
	ll max_flow(int _src, int _dst){
		src = _src; dst = _dst;
		ll result = 0;
		while(dinic_bfs()){
			fill(all(work), 0);
			while(ll delta = dinic_dfs(src, INF)) result += delta;
		}
		return result;
	}
	ll max_flow_min_cap(int s, int t){
		add_edge(t, s, INF);
		ll w = 0;
		forn(i, n+1){
			if     (dd[i] > 0) add_edge(i, n+1,  dd[i]), w += dd[i];
			else if(dd[i] < 0) add_edge(n, i,   -dd[i]);
		}
		ll f = max_flow(n, n+1);
		if(f != w) return -1;
		forn(i, n) if(dd[i] != 0) g[i].pp();
		ll ff = max_flow(s, t); g[s].pp(), g[t].pp();
		return ff;
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
