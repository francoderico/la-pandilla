ll phi(ll n, map<ll, int> &F){ // Retorna los coprimos menores a n
	ll ret = n;
	for(const auto &[p, _] : F) ret -= ret / p;
	return ret;
}
// O(factorizar + lg^2 n)
// Orden de a (mod m), es decir, el menor k tal que a^k = 1 (mod m)
// Existe sii gcd(a, m) = 1. Es un divisor de phi(m)
ll orden(ll a, ll m){ // assert(gcd(a, m) == 1);
	map<ll, int> F; fact(m, F);
	ll ph = phi(m, F); ll ret = ph;
	F.clear(); fact(ph, F);
	for(auto [p, e] : F) while(e > 0 and expmod(a, ret/p, m) == 1)
		ret /= p, e --;
	return ret;
}
