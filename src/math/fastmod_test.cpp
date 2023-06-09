// https://codeforces.com/contest/167/problem/E

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

typedef int64_t ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<ll> vll;

const ll MAXN = 610;
const ll INF = 1e18+100;
const ld EPS = 1e-9;
const ld PI = acosl(-1);

uint64_t mul128_u64(__uint128_t lowbits, uint64_t d) {
	__uint128_t bottom_half = (lowbits & UINT64_C(0xFFFFFFFFFFFFFFFF)) * d;
	bottom_half >>= 64;
	__uint128_t top_half = (lowbits >> 64) * d;
	__uint128_t both_halves = bottom_half + top_half;
	both_halves >>= 64;
	return (uint64_t)both_halves;
}

__uint128_t computeM(uint64_t d) {
	if (d < 0) d = -d;
	__uint128_t M = UINT64_C(0xFFFFFFFFFFFFFFFF);
	M <<= 64;
	M |= UINT64_C(0xFFFFFFFFFFFFFFFF);
	M /= d;
	M += 1;
	M += ((d & (d - 1)) == 0 ? 1 : 0);
	return M;
}

__uint128_t M;

// computa (a % d) dado M precalculado
// d tiene que estar en valor absoluto
// ejemplo:
//
// __uint128_t M = computeM(MOD);
// forn(i, n) c[i] = fastmod(a[i] + b[i], MOD);
int64_t fastmod(int64_t a, int64_t positive_d) {
	__uint128_t lowbits = M * a;
	int64_t highbits = (int64_t)mul128_u64(lowbits, positive_d);
	return highbits - ((positive_d - 1) & (a >> 63));
}

ll MOD;

ll expmod(ll b, ll e)
{
	if(b <= 1) return b;
	if(e == 0) return 1;
	ll q = expmod(b, e/2), p = fastmod(q*q, MOD);
	return e%2 == 0 ? p : fastmod(p*b, MOD);
}

ll inv(ll b)
{
	return expmod(b, MOD-2);
}

ll addmod(ll a, ll b)
{
	return fastmod(a+b, MOD);
}

ll submod(ll a, ll b)
{
	return fastmod((fastmod(a-b, MOD)+MOD), MOD);
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

		r = fastmod(r * a[i][j], MOD);

		dforr(k, j, n) a[i][k] = fastmod(a[i][k] * inv(a[i][j]), MOD);
		
		forr(k, 0, m)
		{
			if(k == i) continue;
			dforr(l_, j, n) a[k][l_] = submod(a[k][l_], fastmod(a[k][j]*a[i][l_], MOD));
		}

		i ++; j ++;
	}

	return r;
}


vector<int> g[MAXN];
bool vis[MAXN];
int idg[MAXN], odg[MAXN];
ll formas[MAXN][MAXN];
int n, m;

void dfs(int v)
{
	vis[v] = true;
	formas[v][v] = 1;

	for(auto x : g[v])
	{
		if(not vis[x]) dfs(x);
		forn(i, n) formas[v][i] = addmod(formas[v][i], formas[x][i]);
	}
}

void solve()
{
	cin >> n >> m;
	cin >> MOD;
	M = computeM(MOD);

	forn(_, m)
	{
		int a, b; cin >> a >> b; a --, b --;
		g[a].pb(b);
		odg[a] ++;
		idg[b] ++;
	}

	forn(i, n) if(not vis[i]) dfs(i);

	vector<vector<ll>> a;

	forn(i, n) if(idg[i] == 0)
	{
		vector<ll> v;

		forn(j, n) if(odg[j] == 0) v.pb(formas[i][j]);
		
		a.pb(v);
	}

	ll r = reduce(a);

	cout << r, nn;
}

int main(){
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	
	return 0;
}
