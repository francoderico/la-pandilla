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

int marked[MAXN/2];
int ix_sieve(int i) { return (i-3)/2; }

// para todo n impar (3<=n<MAXN), inicializa marked tal que
// `marked[ix_sieve(n)]` es:
// - 0 si n es primo
// - el menor divisor primo de n si no
void init_sieve() {
	for (int p = 3; p*p < MAXN; p += 2)
		if (!marked[ix_sieve(p)])
			for (int x = p*p; x < MAXN; x += 2*p)
				if (!marked[ix_sieve(x)])
					marked[ix_sieve(x)] = p;
}

// devuelve 0 sii n es primo o 1
// caso contrario, devuelve el menor divisor primo de n
int query_sieve(int n) {
	if (n <= 2) return 0;
	if (n%2 == 0) return 2;
	return marked[ix_sieve(n)];
}

// n <= sz(criba) (1e7)
// O(log n)
void fact(ll n, map<ll, int> &F)
{
	F.clear();
	while(int p = query_sieve(n)) F[p] ++, n /= p;
	if(n > 1) F[n] ++;
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
	init_sieve();

	int n, m; cin >> n >> m;

	forn(_, m)
	{
		string sgn; cin >> sgn;
		int k; cin >> k;
		if(sgn == "+") add(k);
		else		   erase(k);
	}
}

int main(){
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
}