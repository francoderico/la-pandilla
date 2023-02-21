// https://www.spoj.com/problems/XMAX/

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
const ld EPS = 1e-9;
const ld PI = acosl(-1);


const int N = 64;

// Reduce la matriz mod 2
void reduce(vector<bitset<N>> &a)
{
	int m = sz(a), n = sz(a[0]);
	int i = 0, j = 0;

	while(i < m and j < n)
    {
		int h = i;

		forr(k, i+1, m) if(a[k][j] > a[h][j]) h = k;
		
        if(a[h][j] == 0)
        {
            j ++;
            continue;
        }

		if(h != i)
        {
            swap(a[i], a[h]);
        }
        
		forr(k, 0, m)
        {
			if(k == i or a[k][j] == 0) continue;
            dforr(l_, j, n) a[k][l_] = a[k][l_]^a[i][l_];
		}

		i ++; j ++;
	}
}


void solve()
{
    int m; cin >> m;
    int n = 64;

    vector<bitset<N>> a;

    forn(i, m)
    {
        ull x_; cin >> x_;
        bitset<N> x = x_;
        bitset<N> y;
        forn(i, N) y[i] = x[N-1-i];
        a.pb(y);
    }

    reduce(a);

    bitset<N> ans_, ans;
 
    forn(i, m) ans_ ^= a[i];
 
    forn(j, N) ans[j] = ans_[N-1-j];
    
    cout << ans.to_ullong(), nn;
}

int main(){
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    
    return 0;
}
