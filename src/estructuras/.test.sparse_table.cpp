// https://codeforces.com/problemset/problem/1237/D
#include <bits/stdc++.h>
using namespace std;
#define forr(i,a,b) for(int i = int(a); i < int(b); ++i)
#define forn(i,n) forr(i,0,n)
#define dforr(i,a,b) for(int i = int(b)-1; i >=int(a); --i)
#define dforn(i,n) dforr(i,0,n)
#define all(v) begin(v), end(v)
#define pb push_back

#define OPER min
#define ZERO INT_MAX
struct SparseTable {
	vector<vector<int>> st;
	void init(int* a, int n) {
		int K = 31-__builtin_clz(2*n-1);
		st.assign(K, vector<int>(n));
		forn(i, n) st[0][i] = a[i];
		forr(k,1,K) forn(i,n-(1<<k)+1)
			st[k][i] = OPER(st[k-1][i], st[k-1][i+(1<<(k-1))]);
	}
	int query(int l, int r) {
		if (l >= r) return ZERO;
		int k = 31-__builtin_clz(r-l);
		return OPER(st[k][l], st[k][r-(1<<k)]);
	}
};

void solve() {

	int n;
	cin >> n;

	vector<int> a(n);
	forn(i, n) cin >> a[i];

	int Mv = *max_element(all(a));
	int mv = *min_element(all(a));
	if (mv < (Mv+1)/2) {
		// OK, caso normal
	} else {
		// Siempre infinito
		forn(i, n) cout << "-1" << " \n"[i==n-1];
		return;
	}

	vector<int> p(n);
	iota(all(p), 0);
	sort(all(p), [&](int i, int j) {
		return a[i] < a[j];
	});

	forn(i, n) a.pb(a[i]);
	SparseTable st;
	st.init(&a[0], 2*n);

	vector<int> sm(2*n, 2*n);
	dforn(i, 2*n) {
		int j = i+1;
		while (j<2*n and a[j] <= a[i]) {
			j = sm[j];
		}
		sm[i] = j;
	}

	auto min_query = [&](int l, int r) {
		return st.query(l, r);
	};

	vector<int> dp(2*n);
	dforn(ii, n) {
		int i = p[ii];
		int j = sm[i];
		if (min_query(i+1, j) < (a[i]+1)/2) {
			int lo = i+1, hi = j;
			while (hi-lo > 1) {
				int mi = (hi+lo) / 2;
				if (min_query(i+1, mi) < (a[i]+1)/2) hi = mi;
				else                                 lo = mi;
			}
			dp[i] = lo;
		} else {
			dp[i] = dp[j];
		}
		dp[i+n] = dp[i] + n;
	}

	forn(i, n) {
		cout << dp[i]-i << " \n"[i==n-1];
	}

}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
}
