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
		if (r <= l) return ZERO;
		int k = 31-__builtin_clz(r-l);
		return OPER(st[k][l], st[k][r-(1<<k)]);
	}
};
