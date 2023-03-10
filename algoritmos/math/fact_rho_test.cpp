// https://codeforces.com/problemset/problem/154/B

#include <bits/stdc++.h>
using namespace std;

#define forr(i,a,b) for(int i=int(a);i<int(b);++i)
#define forn(i,n) forr(i,0,n)
#define dforr(i,a,b) for(int i=int(b)-1;i>=int(a);--i)
#define dforn(i,n) dforr(i,0,n)
#define fore(e,c) for(const auto &e : (c))
#define db(v) cerr<<#v" = "<<(v)<<'\n'
#define nn cout<<'\n'
#define sz(v) (int(v.size()))
#define all(v) begin(v), end(v)
#define pb push_back
#define pp pop_back
#define fst first
#define snd second

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

const ll MAXN = 2e5+100;
const ll INF = 1e18+100;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;
const ld PI = acosl(-1);


ll gcd(ll a, ll b) {return a ? gcd(b%a, a) : b;}

ll mulmod(ll b, ll a, ll m)
{
	return __int128(a)*b % m;
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

// Auxiliar, no llamar
void divisores_aux(const map<ll, int> &F, vector<ll> &divs, map<ll, int>::iterator it, ll n = 1)
{
    if(it == F.begin()) divs.clear();
    if(it == F.end()) { divs.pb(n); return; }
    ll p = it->fst, k = it->snd; ++it;
    forn(_, k+1) divisores_aux(F, divs, it, n), n *= p;
}

// Obtiene los divisores a partir de la factorizacion.
// NO ESTA ORDENADO
void divisores(map<ll, int> &F, vector<ll> &divs)
{
    divisores_aux(F, divs, F.begin());
}


bool on[MAXN];
int cant[MAXN];
map<ll, int> F;
vector<ll> divs;

void add(int k)
{
	if(on[k])
	{
		cout << "Already on", nn;
		return;
	}

	F.clear();
	fact(k, F);
	divisores(F, divs);

	for(auto d : divs) if(d != 1)
	{
		if(cant[d] > 0)
		{
			cout << "Conflict with " << cant[d], nn;
			return;
		}
	}

	on[k] = true;

	for(auto d : divs) if(d != 1)
	{
		cant[d] = k;
	}

	cout << "Success", nn;
}

void erase(int k)
{
	if(not on[k])
	{
		cout << "Already off", nn;
		return;
	}

	F.clear();
	fact(k, F);
	divisores(F, divs);

	on[k] = false;

	for(auto d : divs) if(d != 1)
	{
		cant[d] = 0;
	}

	cout << "Success", nn;
}

void solve()
{
	int n, m; cin >> n >> m;

	forn(_, m)
	{
		string sgn; cin >> sgn;
		int k; cin >> k;
		if(sgn == "+") add(k);
		else           erase(k);
	}
}

int main(){
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
}