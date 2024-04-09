template<class Char=char>vector<int> pfun(basic_string<Char>const& w) {
	int n = sz(w), j = 0; vector<int> pi(n);
	forr(i, 1, n) {
		while (j != 0 && w[i] != w[j]) {j = pi[j - 1];}
		if (w[i] == w[j]) {++j;}
		pi[i] = j;
	} // pi[i] = lengh of longest proper suffix of w[0..i] that is also prefix
	return pi;
}
template<class Char=char>vector<int> zfun(const basic_string<Char>& w) {
	int n = sz(w), l = 0, r = 0; vector<int> z(n);
	forr(i, 1, n) {
		if (i <= r) {z[i] = min(r - i + 1, z[i - l]);}
		while (i + z[i] < n && w[z[i]] == w[i + z[i]]) {++z[i];}
		if (i + z[i] - 1 > r) {l = i, r = i + z[i] - 1;}
	} // z[i] = lengh of longest prefix of w that also begins at index i
	return z;
}
