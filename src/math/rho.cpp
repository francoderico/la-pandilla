ll gcd(ll a, ll b) {return a ? gcd(b%a, a) : b;}

ll mulmod(ll b, ll a, ll m)
{
	// Si el producto entra en ll, quitar el casteo
	return __int128(a)*b % m;
}

ll expmod(ll b, ll e, ll m)
{
	ll res = 1;

	while (e)
	{
		if (e%2) res = mulmod(res, b, m);
		b = mulmod(b, b, m);
		e /= 2;
	}

	return res;
}

bool rabin(ll n)	// true sii n es primo
{
	if (n < 2) return false;
	const int primes[] = {2, 3, 5, 13, 19, 73, 193, 407'521, 299'210'837};
	
	fore(p, primes) if (n % p == 0) return n == p;
	
	int s = 0;
	ll d = n - 1;
	while (d%2 == 0) d /= 2, s ++;

	const int bases[] = {2, 325, 9'375, 28'178, 450'775, 9'780'504, 1'795'265'022};
	
	const auto is_witness = [n,d,s](const ll a)
	{
		ll x = expmod(a%n, d, n);

		if (x == 1 or x == n-1) return false;

		forr(r, 1, s)
		{
			x = mulmod(x, x, n);
			if(x == n-1) return false;
			if(x == 1)   return true;
		}

		return true;
	};
	
	fore(a,bases) if(is_witness(a)) return false;
	return true;
}

ll rho(ll n)
{
	if(!(n&1)) return 2;
	ll x = 2, y = 2, d = 1;
	ll c = rand()%n + 1;
	while(d == 1)
	{
		// Si se necesita mas velocidad, agregar addmod en estas 3 lineas
		x = (mulmod(x, x, n)+c) % n;
		y = (mulmod(y, y, n)+c) % n;
		y = (mulmod(y, y, n)+c) % n;
		if(x >= y) d = gcd(x-y, n);
		else d = gcd(y-x, n);
	}
	return d == n ? rho(n) : d;
}

// La unica funcion que tengo que llamar.
// Ojo que no se puede hacer clear adentro porque es recursiva
// O((log n)^3)
void fact(ll n, map<ll, int> &F)
{
	if(n == 1) return;
	if(rabin(n)) {F[n] ++; return;}
	ll q = rho(n); fact(q, F); fact(n/q, F);
}
