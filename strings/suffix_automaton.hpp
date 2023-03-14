/// Full suffix automaton.
///
/// A suffix automaton is a minimal deterministic finite automaton with initial
/// state `0` that accepts all the suffixes of a given string.
/// Apart from being an automaton, it has some additional properties:
/// - Any path starting at `0` forms a substring.
/// - Every substring corresponds to a path starting at `0`.
/// - Each state corresponds to the set of all substrings that have the same
///   ending positions in the string, that is, each state `u` represents an
///   equivalence class according to their ending positions `endpos(u)`.
/// Given a state `u`, we can define the following concepts:
/// - `longest(u)`: longest substring corresponding to `u`.
/// - `len(u)`: length of `longest(u)`.
/// - `shortest(u)`: shortest substring corresponding to `u`.
/// - `minlen(u)`: length of `shortest(u)`.
/// It turns out that any state `u` corresponds to all suffixes of `longest(u)`
/// no shorter than `minlen(u)`.
/// Apart from the usual automaton transitions, the suffix automaton has some
/// extra structure. In particular, for each state `u`, there's a suffix link
/// `link(u)` that points to the state `v` such that `longest(v)` is a suffix
/// of `longest(u)` with `len(v) == minlen(u) - 1`. These links form a tree
/// with the root in `0` and an inclusion relationship between all `endpos`.
template<typename Char=char>
class SuffixAutomaton {
	using str = basic_string<Char>;
	/// Reserve enough memory beforehand.
	///
	/// Calling this in the constructor is optional, buy may be more efficient.
	void reserve_memory(const int n) {
		text.reserve(n);
		const int max_size = max(n + 1, 2 * n - 1);
		next.reserve(max_size);
		link.reserve(max_size);
		len.reserve(max_size);
		firstpos.reserve(max_size);
	}
	/// Push chacarter `c` into the automaton.
	void extend(const Char c, int& last) {
		text.push_back(c);
		int p = last;
		last = push_new_state();
		len[last] = len[p] + 1;
		firstpos[last] = len[p];
		do {next[p][c] = last, p = link[p];} while (p != -1 && !next[p].count(c));
		if (p == -1) {link[last] = 0;}
		else {
			const int q = next[p][c];
			if (len[q] == len[p] + 1) {link[last] = q;}
			else {
				const int cl = push_copy_state(q);
				len[cl] = len[p] + 1;
				link[last] = link[q] = cl;
				do {next[p][c] = cl, p = link[p];} while (p != -1 && next[p].at(c) == q);
			}
		}
	}
	/// Create a brand new state.
	int push_new_state() {
		next.emplace_back();
		link.push_back(-1);
		len.push_back(0);
		firstpos.push_back(-1);
		return size++;
	}
	/// Create a copy of the given state.
	int push_copy_state(const int state) {
		next.push_back(next[state]),
		link.push_back(link[state]);
		len.push_back(len[state]);
		firstpos.push_back(firstpos[state]);
		return size++;
	}
	/// Calculate some data for each state doing DFS in the automaton DAG.
	void count_paths() {
		terminal_paths_from.resize(size);
		paths_from.resize(size);
		substrings_from.resize(size);
		automaton_dfs();
	}
	/// Calculate some data for state `curr` doing DFS in the automaton DAG.
	void automaton_dfs(const int curr=0) {
		terminal_paths_from[curr] = terminal[curr];
		paths_from[curr] = 1;
		fore(edge, next[curr]) {
			const int other = edge.snd;
			if (!paths_from[other]) {automaton_dfs(other);}
			terminal_paths_from[curr] += terminal_paths_from[other];
			paths_from[curr] += paths_from[other];
			substrings_from[curr] += substrings_from[other];
		}
		substrings_from[curr] += terminal_paths_from[curr];
	}
	/// Calculate the terminal states and the inverse suffix links.
	void complete_states(const int last) {
		terminal.resize(size);
		for (int curr = last; curr != -1; curr = link[curr]) {
			terminal[curr] = true;
		}
		inv_link.resize(size);
		for (int curr = 1; curr < size; ++curr) {
			inv_link[link[curr]].push_back(curr);
		}
	}
public:
	// Terminal statuses.
	vector<bool> terminal;
	// Inverse suffix links. If there is a suffix link from `u` to `v`, then there
	// is an inverse suffix link from `v` to `u`.
	vector<vector<int>> inv_link;
	// Transitions in the automaton.
	vector<map<Char, int>> next{{}};
	// Length of the longest substring corresponding to each state.
	vector<int> len{0};
	// Suffix links.
	vector<int> link{-1};
	// First ending position of the substrings corresponding to each state.
	vector<int> firstpos{-1};
	// Number of paths starting at each state and ending in a terminal state. For
	// state `0`, this is the number of suffixes (including the empty suffix).
	vector<int> terminal_paths_from;
	// Number of paths starting at each state. For state `0`, this is the number
	// of distinct substrings (including the empty substring).
	vector<ll> paths_from;
	// Number of substrings starting at each state. For state `0`, this is the
	// number of substrings counting repetitions (including the empty substring
	// repeated `n + 1` times, where `n` is the length of the original string).
	vector<ll> substrings_from;
	// Number of states.
	int size = 1;
	// Original string.
	str text;
	SuffixAutomaton(const str& _text) {
		reserve_memory(sz(_text));
		int last = 0;
		fore(c, _text) {extend(c, last);}
		complete_states(last);
		count_paths();
	}
	/// Run `pattern` through the automaton, returning the last visited state and
	/// the number of transitions that were traversed, that is, the length of the
	/// longest prefix of `pattern` accepted by the automaton.
	pair<int, int> run_pattern(const str& pattern) const {
		int curr = 0, read = 0;
		for (
			auto it = pattern.begin();
			it != pattern.end() && next[curr].count(*it);
			curr = next[curr].at(*(it++))
		) {++read;}
		return {curr, read};
	}
	/// Determine if `pattern` is a suffix of `text`.
	bool is_suffix(const str& pattern) const {
		const auto [state, read] = run_pattern(pattern);
		return terminal[state] && read == sz(pattern);
	}
	/// Determine if `pattern` is a substring of `text`.
	bool is_substring(const str& pattern) const {
		return run_pattern(pattern).snd == sz(pattern);
	}
	/// Return the number of occurrences of `pattern` in `text`.
	int number_occurrences(const str& pattern) const {
		const auto [state, read] = run_pattern(pattern);
		return read == sz(pattern) ? terminal_paths_from[state] : 0;
	}
	/// Return the start position of the first occurrence of `pattern` in `text`.
	int first_occurrence(const str& pattern) const {
		const int m = sz(pattern);
		const auto [state, read] = run_pattern(pattern);
		return read == m ? firstpos[state] + 1 - m : -1;
	}
	/// Return the starting positions of `pattern` in `text` in increasing order.
	vector<int> all_occurrences(const str& pattern) const {
		vector<int> occs;
		const int m = sz(pattern);
		const auto [node, read] = run_pattern(pattern);
		if (read == m) {
			stack<int, vector<int>> st{{node}};
			while (!st.empty()) {
				const int curr = st.top();
				st.pop();
				occs.push_back(firstpos[curr] + 1 - m);
				fore(child, inv_link[curr]) {st.push(child);}
			}
		}
		sort(all(occs));
		occs.erase(unique(all(occs)), occs.end());
		return occs;
	}
	/// Return the kth non-empty suffix of `text` in lexicographical order and the
	/// position where it starts in `text`.
	pair<str, int> kth_suffix(int k) const {
		++k;
		int start = 0, m = 0, curr = 0;
		while ((k -= terminal[curr]) >= 0) {
			fore(edge, next[curr]) {
				const int other = edge.snd;
				const int step = terminal_paths_from[other];
				if (k >= step) {k -= step;}
				else {
					start = firstpos[curr = other] - (m++);
					break;
				}
			}
		}
		return {text.substr(start, m), start};
	}
	/// Return the kth non-empty distinct substring of `text` in lexicographical
	/// order and the position where it starts in `text`.
	pair<str, int> kth_distinct_substring(ll k) const {
		++k;
		int start = 0, m = 0, curr = 0;
		while ((k -= 1) >= 0) {
			fore(edge, next[curr]) {
				const int other = edge.snd;
				const ll step = paths_from[other];
				if (k >= step) {k -= step;}
				else {
					start = firstpos[curr = other] - (m++);
					break;
				}
			}
		}
		return {text.substr(start, m), start};
	}
	/// Return the kth non-empty substring of `text` in lexicographical order
	/// counting repetitions and the position where it starts in `text`.
	pair<str, int> kth_substring(ll k) const {
		k += sz(text) + 1;
		int start = 0, m = 0, curr = 0;
		while ((k -= terminal_paths_from[curr]) >= 0) {
			fore(edge, next[curr]) {
				const int other = edge.snd;
				const ll step = substrings_from[other];
				if (k >= step) {k -= step;}
				else {
					start = firstpos[curr = other] - (m++);
					break;
				}
			}
		}
		return {text.substr(start, m), start};
	}
	/// Return the longest common substring of `word` and `text` and the position
	/// where it starts in `text`.
	pair<str, int> longest_common_substring(const str& word) const {
		int start = 0, curr_len = 0, best_len = 0,curr = 0;
		fore(c, word) {
			while (curr && !next[curr].count(c)) {curr_len = len[curr = link[curr]];}
			if (next[curr].count(c)) {curr = next[curr].at(c), ++curr_len;}
			if (curr_len > best_len) {
				start = firstpos[curr] + 1 - (best_len = curr_len);
			}
		}
		return {text.substr(start, best_len), start};
	}
};
