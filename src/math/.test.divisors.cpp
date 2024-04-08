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

const int MAXP = 1e5+100;
int criba[MAXP];

// 0 si es primo (o si es 1), algun primo que lo divide si no.
void crear_criba()
{
	for(int i = 2; i*i < MAXP; i ++) if(! criba[i]) for(int j = i*i; j < MAXP; j += i) criba[j] = i;
}

// n <= sz(criba) (1e7)
// O(log n)
void fact(ll n, map<ll, int> &F)
{
	F.clear();
	while(criba[n]) F[criba[n]] ++, n /= criba[n];
	if(n > 1) F[n] ++;
}

void divs_aux(const map<ll, int>& F, vector<ll>& D,
                    map<ll, int>::iterator it, ll n = 1){
	if(it == F.end()) { D.pb(n); return; }
	auto [p, k] = *(it ++);
	forn(_, k+1) divs_aux(F, D, it, n), n *= p;
}
void divs(map<ll, int>& F, vector<ll>& D){	// NO ESTA ORDENADO
	divs_aux(F, D, F.begin());
}


bool on[MAXN];
int cant[MAXN];
map<ll, int> F;
vector<ll> D;

void add(int k)
{
	if(on[k])
	{
		cout << "Already on", nn;
		return;
	}

	fact(k, F);
	D.clear(); divs(F, D);

	for(auto d : D) if(d != 1)
	{
		if(cant[d] > 0)
		{
			cout << "Conflict with " << cant[d], nn;
			return;
		}
	}

	on[k] = true;

	for(auto d : D) if(d != 1)
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
	D.clear(); divs(F, D);

	on[k] = false;

	for(auto d : D) if(d != 1)
	{
		cant[d] = 0;
	}

	cout << "Success", nn;
}

void solve()
{
	crear_criba();

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