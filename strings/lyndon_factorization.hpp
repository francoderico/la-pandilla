/// Return the Lyndon factorization of `word`.
///
/// A string is called simple if it is strictly smaller than any of its own
/// non-trivial suffixes, or alternatively, than any of its own non-trivial
/// cyclic shifts. The Lyndon factorization of `word` is a sequence of simple
/// strings in non-increasing order such that their concatenation is `word`.
/// This factorization always exists and is unique.
/// This function implements the Duval algorithm and returns a vector of
/// pairs consisting of a substring and its starting position, representing the
/// factors of `word`.
template<typename Char=char>
vector<pair<basic_string<Char>, int>> duval(const basic_string<Char>& word) {
	vector<pair<basic_string<Char>, int>> facts;
	const int n = sz(word);
	for (int i = 0; i < n;) {
		int j, k;
		for (j = i + 1, k = i; j < n && word[k] <= word[j]; ++j) {
			if (word[k] < word[j]) {k = i;} else {++k;}
		}
		for (const int m = j - k; i <= k; i += m) {
			facts.emplace_back(word.substr(i, m), i);
		}
	}
	return facts;
}

/// Return the smallest cyclic shift of `word` using an idea similar to Lyndon
/// factorization, along with its starting position.
template<typename Char=char>
pair<basic_string<Char>, int> smallest_cyclic_shift(
	const basic_string<Char>& word
) {
	const int n = sz(word);
	int idx = 0;
	for (int i = 0; i < n;) {
		idx = i;
		int j, k;
		for (j = i + 1, k = i; j < 2 * n && word[k % n] <= word[j % n]; ++j) {
			if (word[k % n] < word[j % n]) {k = i;} else {++k;}
		}
		for (const int m = j - k; i <= k; i += m) {}
	}
	basic_string<Char> ans = word.substr(idx, n - idx) + word.substr(0, idx);
	return {ans, idx};
}
