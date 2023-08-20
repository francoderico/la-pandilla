// https://codeforces.com/gym/101205/problem/C

#include <bits/stdc++.h>
using namespace std;

#define forr(i,a,b) for(int i = int(a); i < int(b); ++i)
#define forn(i,n) forr(i,0,n)
#define dforr(i,a,b) for(int i = int(b)-1; i >= int(a); --i)
#define dforn(i,n) dforr(i,0,n)
#define fore(e,c) for(const auto& e : (c))
#define db(v) cerr<<#v" = "<<(v)<<"\n"
#define nn cout<<"\n"
#define sz(v) (int((v).size()))
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

const ll MAXN = 20;
const ll INF = 1e9+100;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;
const ld PI = acosl(-1);

int n, m;

// REQUISITO: int n; // numero de nodos
struct Floyd { int g[MAXN][MAXN];
	void init() { forn(i, n) forn(j, n) g[i][j] = i==j ? 0 : INF; }
	void add_edge(int u, int v, int w) { g[u][v] = min(g[u][v], w); }
	void run() { // hace que g[u][v] sea = distancia u->v
		forn(i, n) forn(j, n) forn(k, n) if (max(g[j][i], g[i][k]) < INF)
			g[j][k] = min(g[j][k], g[j][i] + g[i][k]);
	}
	bool in_neg_cycle(int u) { return g[u][u] < 0; }
};

Floyd floyd;

bool has(int mask, int idx) {
	return (mask & (1 << idx)) != 0;
}

int popcnt(int x) { return __builtin_popcount(x); }
int ctz(int x) { return __builtin_ctz(x); }

// int dp[MAXN][MAXN][1<<MAXN];
int dp[MAXN][MAXN][620000];


void solve() {
	int test_id = 1;

	while (cin >> n >> m) {
		cout << "Case " << test_id++ << ": ";

	floyd.init();

	forn(i, m) {
		int u, v, x; cin >> u >> v >> x;
		floyd.add_edge(u,v,x);
		floyd.add_edge(v,u,x);
	}

	floyd.run();

	if (n == 3) {
		cout << floyd.g[0][1] + floyd.g[1][2] + floyd.g[2][1] + floyd.g[1][0] << "\n";
		continue;
	}

	vector<int> elems(1<<n);
	forn(i, 1<<n) elems[i] = i;
	sort(all(elems), [](int i, int j) {
		return popcnt(i) < popcnt(j);
	});

	vector<int> invelems(1<<n);
	forn(i, 1<<n) invelems[elems[i]] = i;

	forn(i, 1<<n) {
		if (popcnt(elems[i]) > (n-1)/2+1) { break; }
		forn(u, n) forn(v, n) dp[u][v][i] = INF;
	}

	forn(u, n) dp[u][u][invelems[1<<u]] = 0;

	forn(i, 1<<n) { int m = elems[i];

		if (m == 0) continue;
		if (popcnt(m) > (n-1)/2+1) { break; }

		for (int mu = m; mu; mu -= mu&-mu) { int u = ctz(mu);
		for (int mv = m; mv; mv -= mv&-mv) { int v = ctz(mv);
		for (int mw = m; mw; mw -= mw&-mw) { int w = ctz(mw);

			if (u == v || v == w) continue;

			int m_ = m - (1<<v);
			int j = invelems[m_];

			// db(j);

			dp[u][v][i] = min(dp[u][v][i], dp[u][w][j] + floyd.g[w][v]);

		}
		}
		}

	}

//	forn(u, n) {
//		forn(v, n) {
//			forn(m, 1<<n) {
//				cerr << dp[u][v][m] << " ";
//			}
//			cerr << "\n";
//		}
//		cerr << "=====\n";
//	}

	int cant = (n-2)/2;
	int hotel_full = ((1<<(n-2))-1)<<1;

	ll ans = INT_MAX;

	forn(M, 1<<(n-2)) {
		int A = M << 1;
		if (popcnt(A) != cant) continue;

		// db(A);

		int B = A ^ hotel_full;

		ll ida = INT_MAX;
		ll vue = INT_MAX;

		for (int mu = A; mu; mu -= mu&-mu) { int u = ctz(mu);
		for (int mv = B; mv; mv -= mv&-mv) { int v = ctz(mv);
			ida = min(ida, (ll) dp[  0][u][invelems[A|(1<<    0)]] + floyd.g[u][v] + dp[v][n-1][invelems[B|(1<<(n-1))]]);
			vue = min(vue, (ll) dp[n-1][u][invelems[A|(1<<(n-1))]] + floyd.g[u][v] + dp[v][  0][invelems[B|(1<<    0)]]);
		}
		}

		ans = min(ans, ida + vue);
	}

	cout << ans << "\n";
	}

}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
}
