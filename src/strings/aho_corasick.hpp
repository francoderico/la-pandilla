template<class Char=char>struct AhoCorasick {
	using str = basic_string<Char>;
	int state() { term.pb({}), next.pb({}); return sz(term) - 1; }
	vector<vector<int>> term{{}}; // term[u] = lengths of each word ending at u
	vector<map<Char, int>> next{{}}; // next[u] = transitions from u
	vector<int> suff; // suff[u] = longest proper suffix of u
	vector<int> dict; // dict[u] = 1st terminal state reached with suffix links
	vector<str> words;
	AhoCorasick() {}
	AhoCorasick(vector<str>const& ws) { fore(w, ws) {insert(w);} compute(); }
	void insert(str const& w) {
		int curr = 0;
		fore(c, w) {
			if (!next[curr].count(c)) {next[curr][c] = state();}
			curr = next[curr].at(c);
		}
		term[curr].push_back(sz(words)), words.push_back(w);
	}
	void compute() { /// Only call once after all words have been inserted.
		suff.resize(sz(term), -1); dict.resize(sz(term), -1);
		queue<int> q{{0}};
		while (!q.empty()) {
			int curr = q.front(); q.pop();
			fore(edge, next[curr]) {
				auto [c, other] = edge; int link = suff[curr];
				while (link >= 0 && !next[link].count(c)) {link = suff[link];}
				if (link >= 0) {suff[other] = next[link].at(c);} else {suff[other] = 0;}
				if (!term[suff[other]].empty()) {dict[other] = suff[other];}
				else {dict[other] = dict[suff[other]];}
				q.push(other);
			}
		}
	}
	vector<vector<int>> match(str const& txt) const {
		vector<vector<int>> ms(sz(words));
		fore(id, term[0]) {ms[id].push_back(0);}
		int curr = 0, read = 0;
		fore(c, txt) {
			++read;
			while (curr != -1 && !next[curr].count(c)) {curr = suff[curr];}
			if (curr != -1) {curr = next[curr].at(c);}
			else {curr = 0;}
			for (int link = curr; link != -1; link = dict[link]) {
				fore(id, term[link]) {
					int start = read - sz(words[id]);
					ms[id].push_back(start);
				}
			}
		}
		return ms; // ms[i] = start of each occurrence of words[i] in txt
	}
};
