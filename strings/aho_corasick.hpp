/// Full Aho-Corasick automaton.
template<typename Char=char>
class AhoCorasick {
	using str = basic_string<Char>;
	/// Return a new state.
	int create_state() {
		terminal.emplace_back();
		next.emplace_back();
		return sz(terminal) - 1;
	}
public:
	// Lenghts of each string ending at each state.
	vector<vector<int>> terminal{{}};
	// Trie transitions in the automaton.
	vector<map<Char, int>> next{{}};
	// Suffix and dictionary links. A suffix link for node `v` points to its
	// longest proper suffix. A dictionary link for node `v` points to the first
	// terminal state that can be reached using suffix links.
	vector<int> suff, dict;
	// Strings inserted into the automaton.
	vector<str> words;
	/// Insert `word` into the automaton.
	void insert(const str& word) {
		assert(suff.empty());
		int curr = 0;
		fore(c, word) {
			if (!next[curr].count(c)) {next[curr][c] = create_state();}
			curr = next[curr].at(c);
		}
		terminal[curr].push_back(sz(words));
		words.push_back(word);
	}
	/// Compute the suffix and dictionary links after all words were inserted.
	///
	/// This is only done once, after which no more strings can be inserted.
	void complete_automaton() {
		assert(suff.empty());
		suff.resize(sz(terminal), -1);
		dict.resize(sz(terminal), -1);
		queue<int> q{{0}};
		while (!q.empty()) {
			const int curr = q.front();
			q.pop();
			fore(edge, next[curr]) {
				const auto [c, other] = edge;
				int link = suff[curr];
				while (link != -1 && !next[link].count(c)) {link = suff[link];}
				if (link != -1) {suff[other] = next[link].at(c);}
				else {suff[other] = 0;}
				if (!terminal[suff[other]].empty()) {dict[other] = suff[other];}
				else {dict[other] = dict[suff[other]];}
				q.push(other);
			}
		}
	}
	/// Return a vector `matches` such that `matches[i]` contains the start of
	/// each occurrence of `words[i]` in `text`.
	///
	/// This has to be run after all transitions have been computed.
	vector<vector<int>> match(const str& text) const {
		assert(!suff.empty());
		vector<vector<int>> matches(sz(words));
		fore(id, terminal[0]) {matches[id].push_back(0);}
		int curr = 0, read = 0;
		fore(c, text) {
			++read;
			while (curr != -1 && !next[curr].count(c)) {curr = suff[curr];}
			if (curr != -1) {curr = next[curr].at(c);}
			else {curr = 0;}
			for (int link = curr; link != -1; link = dict[link]) {
				fore(id, terminal[link]) {
					const int start = read - sz(words[id]);
					matches[id].push_back(start);
				}
			}
		}
		return matches;
	}
};
