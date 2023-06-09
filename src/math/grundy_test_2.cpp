// https://codeforces.com/contest/1411/problem/G

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

const ll MAXN = 1e5+100;
const ll INF = 1e18+100;
const ll MOD = 998244353;
const ld EPS = 1e-9;
const ld PI = acosl(-1);

ll expmod(ll b, ll e)
{
	if(b <= 1) return b;
	if(e == 0) return 1;
	ll q = expmod(b, e/2), p = q*q % MOD;
	return e%2 == 0 ? p : p*b % MOD;
}

ll inv(ll b)
{
	return expmod(b, MOD-2);
}

ll addmod(ll a, ll b)
{
	ll r = a+b;
	return r < MOD ? r : r-MOD;
}

ll submod(ll a, ll b)
{
	ll r = a-b;
	return r >= 0 ? r : r+MOD;
}

// Reduce la matriz mod MOD
ll reduce(vector<vector<ll>> &a)    // returns determinant (solo tiene sentido si m == n)
{
	int m = sz(a), n = sz(a[0]);
	int i = 0, j = 0;
	ll r = 1;

	while(i < m and j < n)
	{
		int h = i;

		forr(k, i+1, m) if(a[k][j] > a[h][j]) h = k;
		
		if(a[h][j] == 0)
		{
			j ++;
			r = 0;
			continue;
		}

		if(h != i)
		{
			r = submod(0, r);
			swap(a[i], a[h]);
		}

		r = r * a[i][j] % MOD;

		dforr(k, j, n) a[i][k] = a[i][k] * inv(a[i][j]) % MOD;
		
		forr(k, 0, m)
		{
			if(k == i) continue;
			dforr(l_, j, n) a[k][l_] = submod(a[k][l_], a[k][j]*a[i][l_]%MOD);
		}

		i ++; j ++;
	}

	return r;
}


const int MAXG = 512;
bool vis[MAXN];
int grundy[MAXN];
vector<int> g[MAXN];

void dfs(int v)
{
	vis[v] = true;

	vector<bool> reach(MAXG, 0);

	for(auto x : g[v])
	{
		if(not vis[x]) dfs(x);
		reach[grundy[x]] = true;
	}
	
	forn(i, MAXG) if(not reach[i])
	{
		grundy[v] = i;
		return;
	}
}

void solve()
{
	int n, m; cin >> n >> m;
	forn(i, m)
	{
		int a, b; cin >> a >> b; a --, b --;
		g[a].pb(b);
	}

	forn(i, n) if(not vis[i]) dfs(i);

	ll q = inv(n+1);

	vector<vector<ll>> a;

	forn(x, MAXG)
	{
		vector<ll> p(MAXG+1, 0);
		p[x] = submod(0, 1);

		forn(i, n) p[x^grundy[i]] = addmod(p[x^grundy[i]], q);

		if(x > 0) p[MAXG] = submod(0, q);

		a.pb(p);
	}

	reduce(a);

	cout << a[0][MAXG], nn;
}

int main(){
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	
	return 0;
}
