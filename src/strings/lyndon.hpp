vector<pii> lyndon(string const& s) {
	vector<pii> fs; int n = sz(s);
	for (int i = 0, j, k; i < n;) {
		for (k = i, j = i+1; j < n && s[k] <= s[j]; ++j)
			if (s[k] < s[j]) k = i; else ++k;
		for(int m = j-k; i <= k; i += m) fs.emplace_back(i, m);
	} // Unica secuencia no-creciente de strings menores a sus rotaciones.
	return fs; // Retorna substrings de la forma {comienzo, largo}.
}
int minrot(string const& s) { // Ultimo comienzo de la minima rotacion.
	auto fs = lyndon(s+s); int n = sz(s), start = 0;
	fore(f, fs) if (f.fst < n) start = f.fst; else break;
	return start;
}
