/// Simple binary trie working as a multiset of bit sequences of fixed length
/// with extra stuff.
///
/// The binary trie can be thought of as an automaton that accepts a collection
/// of binary sequences of fixed length and where every simple path starting
/// from the initial state corresponds to a "prefix" of some sequence in the
/// multiset. In this context, a prefix of length `N` means the `N` most
/// significant bits in the sequence.
template<unsigned Bits=64U>
class BinaryTrie {
	using seq = bitset<Bits>;
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
	vector<array<int, 2>> next{{}};
	// Number of terminal paths ending at and passing through each state.
	vector<int> terminal{0}, elements{0};
	/// Run `bits` through the automaton, returning the last visited state and a
	/// vector with all the previous visited states in the path.
	pair<int, vector<int>> run(const seq& bits) const {
		int curr = 0;
		vector<int> path;
		path.reserve(Bits);
		dforn(i, Bits) {
			path.push_back(curr);
			const bool bit = bits[i];
			if (next[curr][bit]) {curr = next[curr][bit];}
			else {break;}
		}
		return {curr, path};
	}
	/// Insert `bits` into the automaton.
	void insert(const seq& bits) {
		int curr = 0;
		dforn(i, Bits) {
			++elements[curr];
			const bool bit = bits[i];
			if (!next[curr][bit]) {next[curr][bit] = create_state();}
			curr = next[curr][bit];
		}
		++terminal[curr], ++elements[curr];
	}
	/// Erase one occurrence of `bits` from the automaton.
	void erase(const seq& bits) {
		auto [state, path] = run(bits);
		if (terminal[state]) {
			--terminal[state], --elements[state];
			fore(node, path) {--elements[node];}
			while (state && !elements[state]) {
				available.push_back(state);
				state = path.back(), path.pop_back();
				const bool bit = bits[Bits - sz(path) - 1];
				next[state][bit] = 0;
			}
		}
	}
	/// Return the number of occurrences of `bits` in the automaton.
	int count(const seq& bits) const {return terminal[run(bits).fst];}
	/// Return the minimum and maximum possible xor values that can be obtained
	/// by xoring the `bits` with each sequence in the automaton.
	pair<seq, seq> min_max_xor(const seq& bits) const {
		assert(elements[0]);
		pair<seq, seq> xors;
		xors.snd.set();
		pair<int, int> currs;
		dforn(i, Bits) {
			const bool bit = bits[i], alt = !bit;
			if (next[currs.fst][bit]) {currs.fst = next[currs.fst][bit];}
			else {currs.fst = next[currs.fst][alt], xors.fst[i] = true;}
			if (next[currs.snd][alt]) {currs.snd = next[currs.snd][alt];}
			else {currs.snd = next[currs.snd][bit], xors.snd[i] = false;}
		}
		return xors;
	}
};
