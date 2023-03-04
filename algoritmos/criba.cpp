// ==== REQUISITOS ================
// #include <bitset>
// const int MAXN = 100000000;

bitset<MAXN/2> marked;
int ix_sieve(int i) { return (i-3)/2; }

// para todo n impar (3<=n<MAXN), inicializa marked tal que
// `marked[ix_sieve(n)]==false` sii n es primo
void init_sieve() {
	for (int p = 3; p*p < MAXN; p += 2)
		if (!marked[ix_sieve(p)])
			for (int x = p*p; x < MAXN; x += 2*p)
				marked[ix_sieve(x)] = 1;
}

// devuelve true sii n es primo (0<=n<MAXN)
bool query_sieve(int n) {
	if (n < 2) return false;
	if (n == 2) return true;
	if (n%2 == 0) return false;
	return !marked[ix_sieve(n)];
}
