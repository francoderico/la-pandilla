/// Return a vector `pi` of length `sz(word)` such that `pi[i]` is the length
/// of the longest proper suffix of `word[0..i]` that is also its prefix for
/// `0 <= i < sz(word)`.
template<typename Char=char>
vector<int> prefix_function(const basic_string<Char>& word) {
	const int n = sz(word);
	vector<int> pi(n);
	int j = 0;
	forr(i, 1, n) {
		while (j != 0 && word[i] != word[j]) {j = pi[j - 1];}
		if (word[i] == word[j]) {++j;}
		pi[i] = j;
	}
	return pi;
}

/// Return a vector `z` of length `sz(word)` such that `z[0] = 0` and `z[i]`
/// is the length of the longest prefix of `word` that also begins at position
/// `i` for `0 < i < sz(word)`.
template<typename Char=char>
vector<int> z_function(const basic_string<Char>& word) {
	const int n = sz(word);
	vector<int> z(n);
	int l = 0, r = 0;
	forr(i, 1, n) {
		if (i <= r) {z[i] = min(r - i + 1, z[i - l]);}
		while (i + z[i] < n && word[z[i]] == word[i + z[i]]) {++z[i];}
		if (i + z[i] - 1 > r) {l = i, r = i + z[i] - 1;}
	}
	return z;
}
