ll gcd(ll a, ll b) {return a ? gcd(b%a, a) : b;}

ll mulmod(ll b, ll a, ll m)
{
	if(!a) return 0;
	ll q = mulmod(b, a/2, m); q = (q+q)%m;
	return a&1 ? (b+q)%m : q;
}

ll expmod(ll b, ll e, ll m)
{
	if(!e) return 1;
	ll q = expmod(b, e/2, m); q = mulmod(q, q, m);
	return e&1 ? mulmod(b, q, m) : q;
}

bool es_primo_prob(ll n, int a)
{
	if(n == a) return true;
	ll s = 0, d = n-1;
	while(d%2 == 0) s ++, d /= 2;
	
	ll x = expmod(a, d, n);
	if((x == 1) || (x+1 == n)) return true;
	
	forr(_, 0, s-1)
	{
		x = mulmod(x, x, n);
		if(x == 1) return false;
		if(x+1 == n) return true;
	}
	return false;
}

bool rabin(ll n)	//true iff n is prime
{
	if(n == 1) return false;
	int ar[] = {2,3,5,7,11,13,17,19,23};
	forr(i, 0, 9) if(!es_primo_prob(n, ar[i])) return false;
	return true;
}

ll rho(ll n)
{
	if(!(n&1)) return 2;
	ll x = 2, y = 2, d = 1;
	ll c = rand()%n + 1;
	while(d == 1)
	{
		x = (mulmod(x, x, n)+c) % n;
		y = (mulmod(y, y, n)+c) % n;
		y = (mulmod(y, y, n)+c) % n;
		if(x >= y) d = gcd(x-y, n);
		else d = gcd(y-x, n);
	}
	return d == n ? rho(n) : d;
}

// La única función que tengo que llamar.
// Ojo que no se puede hacer clear adentro porque es recursiva
// O((log n)^3)
void fact(ll n, map<ll, int> &F)
{
	if(n == 1) return;
	if(rabin(n)) {F[n] ++; return;}
	ll q = rho(n); fact(q, F); fact(n/q, F);
}