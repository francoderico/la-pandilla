ll gcd(ll a, ll b) { return a ? gcd(b%a, a) : b; }

ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }

// Devuelve {x, y} tales que a*x + b*y = gcd
pll extended_euclid(ll a, ll b)
{
	if(b == 0) return {1, 0};
	
	pll c = extended_euclid(b, a%b);
	
	ll x = c.snd;
	ll y = c.fst - (a/b)*c.snd;
	
	if(a*x + b*y < 0) x = -x, y = -y;
	
	return {x, y};
}

// Genera las soluciones de a*x + b*y = r, con r múltiplo del gcd
pair<pll, pll> diophantine(ll a, ll b, ll r)
{
	ll d = gcd(a, b);
	//assert(r%d == 0);
	a /= d; b /= d; r /= d;
	
	pll p = extended_euclid(a, b);
	p.fst *= r; p.snd *= r;
	return {p, {-b, a}};	// Soluciones: ans.fst + k * ans.snd para todo k
}

ll mod(ll a, ll m) { return (a%m + m) % m; }
ll mod(__int128 a, ll m) { return (a%m + m) % m; }

ll inv(ll a, ll m)
{
	//assert(gcd(a, m) == 1);
	ll x = extended_euclid(a, m).fst;   //a*x + m*y = 1 => a*x = 1 (mod m)
	return mod(x, m);
}

// Dados {a, b, m} que son a * x = b (mod m),
// devuelve {x, mod}, con mod | m
pll sol(tuple<ll, ll, ll> c)
{
	ll a = get<0>(c), b = get<1>(c), m = get<2>(c);
	ll d = gcd(a, m);

	if(d == 1) return {mod(b*inv(a, m), m), m};
	
	if(b%d) return {-1, -1};	// Imposible
	
	return sol(make_tuple(a/d, b/d, m/d));
}


// Dado un vector de condiciones {ai, bi, mi}, que son ai * x = bi (mod mi),
// devuelve (x, mod) donde mod es el lcm de todos los modulos., o (-1, -1) si es inconsistente.
// Asume que lcm entra en ll (se puede cambiar todo a __int128 si no, PERO NO A ull).
pll crt(vector<tuple<ll, ll, ll>> cond)
{
	ll x1 = 0, m1 = 1, x2, m2;

	for(auto t : cond)
	{
		tie(x2, m2) = sol(t);
		
		if((x1 - x2) % gcd(m1, m2)) return {-1, -1};
		if(m1 == m2) continue;
		
		ll k = diophantine(m2, -m1, x1-x2).fst.snd;
		ll l = lcm(m1, m2);
		
		x1 = mod(__int128(m1)*k + x1, l);
		m1 = l;
	}

	return sol(make_tuple(1, x1, m1));
}

// Uso:
// c.pb(make_tuple(mod(a, m), mod(b, m), m);
// pll ans = crt(c);