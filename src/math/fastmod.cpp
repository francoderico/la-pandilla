uint64_t mul128_u64(__uint128_t lowbits, uint64_t d) {
	__uint128_t bottom_half = (lowbits & UINT64_C(0xFFFFFFFFFFFFFFFF)) * d;
	bottom_half >>= 64;
	__uint128_t top_half = (lowbits >> 64) * d;
	__uint128_t both_halves = bottom_half + top_half;
	both_halves >>= 64;
	return (uint64_t)both_halves;
}
__uint128_t computeM(uint64_t d) {
	if (d < 0) d = -d;
	__uint128_t M = UINT64_C(0xFFFFFFFFFFFFFFFF);
	M <<= 64;
	M |= UINT64_C(0xFFFFFFFFFFFFFFFF);
	M /= d;
	M += 1;
	M += ((d & (d - 1)) == 0 ? 1 : 0);
	return M;
}
// computa (a % d) dado M precalculado
// d tiene que estar en valor absoluto. ejemplo:
// __uint128_t M = computeM(MOD);
// forn(i, n) c[i] = fastmod(a[i] + b[i], M, MOD);
int64_t fastmod(int64_t a, __uint128_t M, int64_t positive_d) {
	__uint128_t lowbits = M * a;
	int64_t highbits = (int64_t)mul128_u64(lowbits, positive_d);
	return highbits - ((positive_d - 1) & (a >> 63));
}