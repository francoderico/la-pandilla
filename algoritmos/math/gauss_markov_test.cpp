// https://acm.timus.ru/problem.aspx?space=1&num=1766

#include <bits/stdc++.h>
using namespace std;

#define forr(i,a,b) for(int i=int(a);i<int(b);++i)
#define forn(i,n) forr(i,0,n)
#define dforr(i,a,b) for(int i=int(b)-1;i>=int(a);--i)
#define dforn(i,n) dforr(i,0,n)
#define db(v) cerr<<#v" = "<<(v)<<endl
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

const ll MAXN = 110;
const ll INF = 1e18+100;
const ll MOD = 1e9+7;
const ld EPS = 1e-12;
const ld PI = acosl(-1);


// Matriz m x n (m filas, n columnas)
ld reduce(vector<vector<ld>> &a)  // returns determinant (solo tiene sentido si m == n)
{
	int m = sz(a), n = sz(a[0]);
	int i = 0, j = 0;
	ld r = 1.;

	while(i < m and j < n)
	{
		int h = i;

		forr(k, i+1, m) if(abs(a[k][j]) > abs(a[h][j])) h = k;
		
		if(abs(a[h][j]) < EPS)
		{
			j ++;
			r = 0.;
			continue;
		}

		if(h != i)
		{
			r = -r;
			swap(a[i], a[h]);
		}

		r *= a[i][j];

		dforr(k, j, n) a[i][k] /= a[i][j];
		
		forr(k, 0, m)
		{
			if(k == i) continue;
			dforr(l_, j, n) a[k][l_] -= a[k][j] * a[i][l_];
		}

		i ++; j ++;
	}

	return r;
}

//Dada una matriz de Markov A (todas las columnas suman 1) de nxn,
//encuentra un vector estocastico v tal que Av = v (un autovector estocastico de autovalor 1).
//Para esto resuelve (A-I)v = 0 y de las infinitas soluciones posibles agarra el estocastico.
vector<ld> markov(vector<vector<ld>> &a)
{
	//assert(sz(a) > 0 and sz(a) == sz(a[0]));
	int m = sz(a);
	forn(i, m) a[i][i] += -1., a[i].pb(0.);	//Restamos I y agregamos el ti al que queremos llegar (0)

	reduce(a);

	ld escala = 1.;

    forn(i, m-1) escala += -a[i][m-1];

	vector<ld> v(m);
    v[m-1] = 1/escala;

    dforn(i, m-1) v[i] = -a[i][m-1] * v[m-1];

	return v;
}

//¡OJO! TIENE QUE SER 8
const int N = 8;

int node(int i, int j)
{
    return i*N + j;
}

int t[N][N];
int suma[N][N];

void solve()
{
    forn(i, N) forn(j, N) cin >> t[i][j];

    vector<int> x = {0, 1, 1, 1, 0, -1, -1, -1};
    vector<int> y = {-1, -1, 0, 1, 1, 1, 0, -1};

    forn(i, N) forn(j, N)
    {
        forn(mv, sz(x))
        {
            int ii = i + y[mv], jj = j + x[mv];
            if(ii >= 0 and ii < N and jj >= 0 and jj < N) suma[i][j] += t[ii][jj];
        }
    }

    vector<vector<ld>> a;

    forn(i, N) forn(j, N)
    {
        vector<ld> v(N*N, 0);

        forn(mv, sz(x))
        {
            int ii = i + y[mv], jj = j + x[mv];

            if(ii >= 0 and ii < N and jj >= 0 and jj < N) v[node(ii, jj)] += ld(t[i][j]) / suma[ii][jj];
        }

        a.pb(v);
    }
	
	vector<ld> ans = markov(a);

    forn(i, N)
    {
        forn(j, N) cout << ans[node(i, j)] << ' ';
        nn;
    }
}

int main(){
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);


	cout << fixed << setprecision(12);
	solve();

	return 0;
}