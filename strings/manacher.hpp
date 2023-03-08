/// Return two vectors `odd` and `even` such that `odd[i]` is the number of
/// substring palindromes of odd length centered at position `i` and `even[i]`
/// is the number of substring palindromes of even length centered at positions
/// `i` and `i+1`.
template<typename Char=char>
pair<vector<int>, vector<int>> manacher(
	const basic_string<Char>& word
) {
	if (word.empty()) {return {{}, {}};}
	const int n = sz(word);
	vector<int> odd(n), even(n - 1);
	int l, r;
	l = r = 0;
	forn(i, n) {
		int k = (r <= i) ? 1 : min(odd[l + r - i - 1], r - i);
		while (0 <= i - k && i + k < n && word[i - k] == word[i + k]) {++k;}
		odd[i] = k;
		if (r < i + k) {l = i - k + 1, r = i + k;}
	}
	l = r = 0;
	forn(i, n - 1) {
		const int j = i + 1;
		int k = (r <= j) ? 0 : min(even[l + r - i - 2], r - j);
		while (0 <= i - k && j + k < n && word[i - k] == word[j + k]) {++k;}
		even[i] = k;
		if (r < j + k) {l = i - k + 1, r = j + k;}
	}
	return {odd, even};
}
