/// Simple trie working as a multiset of strings with extra stuff.
///
/// The trie can be thought as an automaton that accepts a collection of
/// strings and where every simple path starting from the initial state
/// corresponds to a prefix of some string in the multiset.
template<typename Char=char>
class Trie {
	using str = basic_string<Char>;
	// Deleted states that can be reused.
	vector<int> available;
	/// Return a new state.
	int create_state() {
		if (!available.empty()) {
			const int state = available.back();
			available.pop_back();
			return state;
		}
		next.emplace_back();
		terminal.push_back(0);
		elements.push_back(0);
		return sz(terminal) - 1;
	}
public:
	// Transitions in the automaton.
	vector<map<Char, int>> next{{}};
	// Number of terminal paths ending at and passing through each state.
	vector<int> terminal{0}, elements{0};
	/// Run `word` through the automaton, returning the last visited state and a
	/// vector with all the previous visited states in the path.
	pair<int, vector<int>> run(const str& word) const {
		int curr = 0;
		vector<int> path;
		path.reserve(sz(word));
		for (
			auto it = word.begin();
			it != word.end() && next[curr].count(*it);
			curr = next[curr].at(*(it++))
		) {path.push_back(curr);}
		return {curr, path};
	}
	/// Insert `word` into the automaton.
	void insert(const str& word) {
		int curr = 0;
		vector<int> path;
		path.reserve(sz(word));
		fore(c, word) {
			path.push_back(curr);
			if (!next[curr].count(c)) {next[curr][c] = create_state();}
			curr = next[curr].at(c);
		}
		++terminal[curr], ++elements[curr];
		fore(node, path) {++elements[node];}
	}
	/// Erase one occurrence of `word` from the automaton.
	void erase(const str& word) {
		auto [state, path] = run(word);
		if (terminal[state] && sz(path) == sz(word)) {
			--terminal[state], --elements[state];
			fore(node, path) {--elements[node];}
			while (state && !elements[state]) {
				available.push_back(state);
				state = path.back(), path.pop_back();
				const Char c = word[sz(path)];
				next[state].erase(c);
			}
		}
	}
	/// Return the number of occurrences of `word` in the automaton.
	int count(const str& word) const {
		const auto [state, path] = run(word);
		return sz(path) == sz(word) ? terminal[state] : 0;
	}
};
