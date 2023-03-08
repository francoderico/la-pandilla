/// Encapsulation of the Knuth-Morris-Pratt string matching algorithm.
///
/// It takes a single string, the pattern that will be used for running KMP.
/// Because the pattern's preprocessing is only done once, it allows us to
/// efficiently run KMP with multiple texts.
template<typename Char=char>
class Kmp{
	using str = basic_string<Char>;
public:
	const vector<int> pi;
	const str pattern;
	Kmp(const str& _pattern):
		pi(move(prefix_function(_pattern))), pattern(_pattern){}
	/// Return a vector with the start of each occurrence of `pattern` in `text`.
	vector<int> matches(const str& text) const {
		if (sz(pattern) > sz(text)) {return {};}
		vector<int> occs;
		const int m = sz(pattern), n = sz(text);
		if (m == 0) {occs.push_back(0);}
		int j = 0;
		forn(i, n) {
			while (j != 0 && text[i] != pattern[j]) {j = pi[j-1];}
			if (text[i] == pattern[j]) {++j;}
			if (j == m) {occs.push_back(i - j + 1);}
		}
		return occs;
	}
};
