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

const int MAXP = 320;
int criba[MAXP];

// 0 si es primo (o si es 1), algun primo que lo divide si no.
void crear_criba()
{
	for(int i = 2; i*i < MAXP; i ++) if(! criba[i]) for(int j = i*i; j < MAXP; j += i) criba[j] = i;
}

// Requiere criba
vector<int> primos;
void buscar_primos()	//¡¡crear_criba() primero!!
{
	forr(i, 2, MAXP) if(! criba[i]) primos.pb(i);
}

// n <= MAXP^2
// O(sz(p)) (cantidad de primos)
void fact(ll n, map<ll, int> &F)
{
	F.clear();
	for(auto &p : primos) while(n%p == 0) F[p] ++, n /= p;
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
	crear_criba();
	buscar_primos();

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