struct StrHash { // Hash polinomial con exponentes decrecientes.
	static constexpr ll ms[] = {1'000'000'007, 1'000'000'403};
	static constexpr ll b = 500'000'000;
	vector<ll> hs[2], bs[2];
	StrHash(string const& s) {
		int n = sz(s);
		forn(k, 2) {
			hs[k].resize(n+1), bs[k].resize(n+1, 1);
			forn(i, n) {
				hs[k][i+1] = (hs[k][i] * b + s[i]) % ms[k];
				bs[k][i+1] =  bs[k][i] * b         % ms[k];
			}
		}
	}
	ll get(int idx, int len) const { // Hashes en `s[idx, idx+len)`.
		ll h[2];
		forn(k, 2) {
			h[k] = hs[k][idx+len] - hs[k][idx] * bs[k][len] % ms[k];
			if (h[k] < 0) h[k] += ms[k];
		}
		return (h[0] << 32) | h[1];
	}
};
