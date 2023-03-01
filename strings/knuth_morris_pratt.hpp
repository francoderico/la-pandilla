template<typename Char=char>
class knuth_morris_pratt{
	using str = basic_string<Char>;
public:
	const vector<int> pi;
	const str pattern;
	knuth_morris_pratt(const str& _pattern):
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
