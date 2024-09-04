#define RB(x) ((x) < n ? r[x] : 0)
void csort(vector<int>& sa, vector<int>& r, int k) {
	int n = sz(sa);
	vector<int> f(max(255, n)), t(n);
	forn(i, n) ++f[RB(i+k)];
	int sum = 0;
	forn(i, max(255, n)) f[i] = (sum += f[i]) - f[i];
	forn(i, n) t[f[RB(sa[i]+k)]++] = sa[i];
	sa = t;
}
vector<int> compute_sa(string& s){ // O(n*log2(n))
	int n = sz(s) + 1, rank;
	vector<int> sa(n), r(n), t(n);
	iota(all(sa), 0);
	forn(i, n) r[i] = s[i];
	for (int k = 1; k < n; k *= 2) {
		csort(sa, r, k), csort(sa, r, 0);
		t[sa[0]] = rank = 0;
		forr(i, 1, n) {
			if(r[sa[i]] != r[sa[i-1]] || RB(sa[i]+k) != RB(sa[i-1]+k)) ++rank;
			t[sa[i]] = rank;
		}
		r = t;
		if (r[sa[n-1]] == n-1) break;
	}
	return sa; // sa[i] = i-th suffix of s in lexicographical order
}
vector<int> compute_lcp(string& s, vector<int>& sa){
	int n = sz(s) + 1, L = 0;
	vector<int> lcp(n), plcp(n), phi(n);
	phi[sa[0]] = -1;
	forr(i, 1, n) phi[sa[i]] = sa[i-1];
	forn(i,n) {
		if (phi[i] < 0) { plcp[i] = 0; continue; }
		while(s[i+L] == s[phi[i]+L]) ++L;
		plcp[i] = L;
		L = max(L - 1, 0);
	}
	forn(i, n) lcp[i] = plcp[sa[i]];
	return lcp; // lcp[i] = longest common prefix between sa[i-1] and sa[i]
}
