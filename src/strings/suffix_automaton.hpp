/// Minimal DFA that accepts all suffixes of a string.
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
/// Any state `u` corresponds to all suffixes of `longest(u)` no shorter
/// than `minlen(u)`.
/// For state `u`, `link(u)` points to the state `v` such that `longest(v)`
/// is a suffix of `longest(u)` with `len(v) == minlen(u) - 1`. These links
///  form a tree with the root in `0` and an inclusion relationship between
/// all `endpos`.
template<class Char=char>class SuffixAutomaton {
	using str = basic_string<Char>;
	void extend(Char c, int& last) {
		txt.pb(c); int p = last; last = new_state();
		len[last] = len[p] + 1, firstpos[last] = len[p];
		do {next[p][c] = last, p = link[p];} while (p >= 0 && !next[p].count(c));
		if (p == -1) {link[last] = 0;} else {
			int q = next[p][c];
			if (len[q] == len[p] + 1) {link[last] = q;} else {
				int cl = copy_state(q);
				len[cl] = len[p] + 1; link[last] = link[q] = cl;
				do {next[p][c] = cl, p = link[p];} while (p >= 0 && next[p].at(c) == q);
			}
		}
	}
	int new_state() {
		next.pb({}), link.pb(-1), len.pb(0), firstpos.pb(-1);
		return size++;
	}
	int copy_state(int state) {
		next.pb(next[state]), link.pb(link[state]);
		len.pb(len[state]), firstpos.pb(firstpos[state]);
		return size++;
	}
	void dfs(int curr=0) {
		terminal_paths_from[curr] = term[curr];
		paths_from[curr] = 1;
		fore(edge, next[curr]) {
			int other = edge.snd;
			if (!paths_from[other]) {dfs(other);}
			terminal_paths_from[curr] += terminal_paths_from[other];
			paths_from[curr] += paths_from[other];
			substrings_from[curr] += substrings_from[other];
		}
		substrings_from[curr] += terminal_paths_from[curr];
	}
	void compute(int last) {
		term.resize(size);
		for (int curr = last; curr != -1; curr = link[curr]) {term[curr] = true;}
		inv_link.resize(size);
		forr(curr, 1, size) {inv_link[link[curr]].pb(curr);}
	}
public:
	vector<bool> term; // Terminal statuses.
	vector<vector<int>> inv_link; // Inverse suffix links.
	vector<map<Char, int>> next{{}}; // Automaton transitions.
	vector<int> len{0}; // len[u] = lengh of longest(u)
	vector<int> link{-1}; // Suffix links.
	vector<int> firstpos{-1}; // First endpos element of each state.
	// Number of paths starting at each state and ending in a terminal state.
	// For `0`, this is the number of suffixes (including the empty suffix).
	vector<int> terminal_paths_from;
	// Number of paths starting at each state. For `0`, this is the number of
	// distinct substrings (including the empty substring).
	vector<ll> paths_from;
	// Number of substrings starting at each state. For `0`, this is the number
	// of substrings counting repetitions (including the empty substring
	// repeated `n+1` times, where `n` is the length of the original string).
	vector<ll> substrings_from;
	int size = 1; // Number of states.
	str txt; // Original string.
	SuffixAutomaton(str const& _txt) {
		int last = 0;
		fore(c, _txt) {extend(c, last);}
		compute(last); terminal_paths_from.resize(size);
		paths_from.resize(size); substrings_from.resize(size); dfs();
	}
	pair<int, int> run(str const& pat) const {
		int curr = 0, read = 0; // curr = last visited state
		for (
			auto it = pat.begin();
			it != pat.end() && next[curr].count(*it);
			curr = next[curr].at(*(it++))
		) {++read;} // read = number of traversed transitions
		return {curr, read};
	}
	bool is_suff(str const& pat) const
		{auto [state, read] = run(pat); return term[state] && read == sz(pat);}
	bool is_substr(str const& pat) const {return run(pat).snd == sz(pat);}
	int num_occs(str const& pat) const {
		auto [state, read] = run(pat);
		return read == sz(pat) ? terminal_paths_from[state] : 0;
	}
	int fst_occ(str const& pat) const {
		int m = sz(pat); auto [state, read] = run(pat);
		return read == m ? firstpos[state] + 1 - m : -1;
	}
	vector<int> all_occs(str const& pat) const {
		vector<int> occs; int m = sz(pat); auto [node, read] = run(pat);
		if (read == m) {
			stack<int> st{{node}};
			while (!st.empty()) {
				int curr = st.top(); st.pop();
				occs.pb(firstpos[curr] + 1 - m);
				fore(child, inv_link[curr]) {st.push(child);}
			}
		}
		// sort(all(occs)); occs.erase(unique(all(occs)), occs.end());
		return occs; // unsorted and nonunique by default
	}
};
