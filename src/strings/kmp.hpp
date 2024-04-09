template<class Char=char>struct Kmp {
	using str = basic_string<Char>;
	vector<int> pi; str pat;
	Kmp(str const& _pat): pi(move(pfun(_pat))), pat(_pat) {}
	vector<int> matches(str const& txt) const {
		if (sz(pat) > sz(txt)) {return {};}
		vector<int> occs; int m = sz(pat), n = sz(txt);
		if (m == 0) {occs.push_back(0);}
		int j = 0;
		forn(i, n) {
			while (j != 0 && txt[i] != pat[j]) {j = pi[j-1];}
			if (txt[i] == pat[j]) {++j;}
			if (j == m) {occs.push_back(i - j + 1);}
		}
		return occs;
	}
};
