// https://codeforces.com/gym/100962/problem/A

#include <bits/stdc++.h>
using namespace std;

#define forr(i,a,b) for(int i=int(a);i<int(b);++i)
#define forn(i,n) forr(i,0,n)
#define dforr(i,a,b) for(int i=int(b)-1;i>=int(a);--i)
#define dforn(i,n) dforr(i,0,n)
#define db(v) cerr<<#v" = "<<(v)<<'\n'
#define vecp(v) cerr<<#v<<" = "; for(auto ee:v)cerr<<ee<<' '; cerr<<'\n'
#define nn cout<<'\n'
#define sz(v) (int(v.size()))
#define all(v) v.begin(), v.end()
#define pb push_back
#define pp pop_back
#define fst first
#define snd second

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<ll> vll;

const ll MAXN = 2e5+100;
const ll INF = 1e18+100;
const ll MOD = 1e9+7;
//const ld EPS = 1e-9;
const ld PI = acosl(-1);


const double EPS = 1e-4;

double reduce(vector<vector<double>> &a){  // returns determinant (solo tiene sentido si m == n)
	int m = sz(a), n = sz(a[0]);
	int i = 0, j = 0;
	double r = 1.0;
	while(i < m and j < n){
		int h = i;
		forr(k, i+1, m) if(abs(a[k][j]) > abs(a[h][j])) h = k;
		if(abs(a[h][j]) < EPS){
			j ++;
			r = 0.0;
			continue;
		}
		if(h != i){
			r = -r;
			swap(a[i], a[h]);
		}
		r *= a[i][j];
		dforr(k, j, n) a[i][k] /= a[i][j];
		forr(k, 0, m){
			if(k == i) continue;
			dforr(l_, j, n) a[k][l_] -= a[k][j] * a[i][l_];
		}
		i ++; j ++;
	}
	return r;
}


vector<int> dep_variables(vector<vector<double>> &a)
{
	vector<int> ret;
	int m = sz(a), n = sz(a[0]);

	forn(i, m)
	{
		forn(j, n) if(abs(a[i][j]) > EPS) {ret.pb(j); break;}
	}

	return ret;
}

void solve()
{
	int m, n; cin >> m >> n;
	vector<vector<double>> a(m, vector<double>(n));
	forn(i, m) forn(j, n) cin >> a[i][j];

	reduce(a);
	vector<int> r = dep_variables(a);
	
	cout << sz(r), nn;
}


int main(){
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	
	return 0;
}
