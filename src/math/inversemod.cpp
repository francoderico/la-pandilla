ll inv[MAXN]; // Precalcula todos los inversos hasta MAXN
void calc(){
	inv[1] = 1;
	forr(i, 2, MAXN) inv[i] = MOD - (MOD/i) * inv[MOD%i] % MOD;
}
// Solo si MAXN es muy grande o MOD no es fijo. Mas rapido que el de phi.
ll inv(ll a, ll m){ //assert(gcd(a, m) == 1);
	auto [x, _] = extended_euclid(a, m);
	return ((x % m) + m) % m; //a*x + m*y = 1 => a*x=1(mod m)
}
// Solo si phi ya esta codeado o si pide orden o similar.
ll inv(ll a, ll m){
	return expmod(a, phi(m)-1, m);  //Si m NO es primo (sacar a mano)
	return expmod(a, m-2, m);	      //Si m es primo
}