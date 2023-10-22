// Devuelve {x, y} tales que a*x + b*y = gcd
pll extended_euclid(ll a, ll b){
	if(b == 0) return {1, 0};
	auto [y, x] = extended_euclid(b, a%b);
	y -= (a/b)*x;
	if(a*x + b*y < 0) x = -x, y = -y;
	return {x, y};
}
// Genera las soluciones de a*x + b*y = r, con r multiplo del gcd
pair<pll, pll> diophantine(ll a, ll b, ll r){ //assert(r%d == 0);
	ll d = gcd(a, b);
	a /= d; b /= d; r /= d;
	auto [x, y] = extended_euclid(a, b);
	return {{x*r, y*r}, {-b, a}};	// Soluciones: ans.fst + k * ans.snd para todo k
}
ll mod(ll a, ll m) { return (a%m + m) % m; }
ll mod(__int128 a, ll m) { return (a%m + m) % m; }
// Dados {a, b, m} que son a * x = b (mod m), devuelve {x, mod}, con mod | m
pll sol(tuple<ll, ll, ll> c){
	auto [a, b, m] = c; ll d = gcd(a, m);
	if(d == 1) return {mod(b*inv(a, m), m), m};
	if(b%d) return {-1, -1};	// No hay solucion
	return sol(make_tuple(a/d, b/d, m/d));
}
// Dado un vector de condiciones {ai, bi, mi}, que son ai * x = bi (mod mi),
// devuelve (x, mod) donde mod es el lcm de todos los modulos, o (-1, -1) si es inconsistente.
// Asume que lcm entra en ll (se puede cambiar todo a __int128 si no, PERO NO A ull).
pll crt(vector<tuple<ll, ll, ll>> cond){
	ll x1 = 0, m1 = 1;
	for(auto t : cond){
		auto [x2, m2] = sol(t);
		if((x1 - x2) % gcd(m1, m2) != 0) return {-1, -1};
		if(m1 == m2) continue;
		ll k = diophantine(m2, -m1, x1-x2).fst.snd;
		ll l = lcm(m1, m2);
		x1 = mod(__int128(m1)*k + x1, l);
		m1 = l;
	}
	return sol(make_tuple(1, x1, m1));
}
// Uso:
// cond.pb({mod(a, m), mod(b, m), m});
// auto [x, mod] = crt(cond);