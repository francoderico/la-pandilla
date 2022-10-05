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




struct Mono {
	int val;
	static Mono zero() { return { -1 }; } // neutro de la suma
};
Mono operator+ (Mono a, Mono b) {
	return {max(a.val, b.val)};
} // asociativo

struct Segtree {
	static constexpr int log2n = 17; // TODO
	static constexpr int len = 1<<log2n, sze = 1<<(log2n+1);
	vector<Mono> data;
	Segtree() : data(sze) { }

	// inicia con los valores dados O(n+len)
	void init(Mono* a, int n) {
		forn(i, sze) data[i] = Mono::zero();
		forn(i, n) data[i+len] = a[i];
		dforr(i, 1, len) data[i] = data[i*2] + data[i*2+1];
	}

	// point update O(log(len))
	void update(int i, Mono x) {
		i += len; data[i] = x;
		while (i /= 2) data[i] = data[i*2] + data[i*2+1];
	}

	// range query O(log(len))
	Mono query(int l, int r) { ql = l; qr = r; return q_(1, 0, len); }

private:
	int ql, qr;
	Mono q_(int i, int l, int r) {
		if (r <= ql || qr <= l) return Mono::zero();
		if (ql <= l && r <= qr) return data[i];
		int m = (l+r)/2;
		return q_(i*2,l,m) + q_(i*2+1,m,r);
	}
};

Segtree st;

int n, q;

int a[MAXN];
Mono d[MAXN];

void solve() {
	forn(i,n) cin >> a[i];
	forn(i,n-1) d[i] = {abs(a[i] - a[i+1])};
	st.init(d, n-1);

	forn(_, q) {
		int t, j, H;
		cin >> t >> j >> H;

		// cerr << "================\n"; db(t); db(j); db(H); 

		--j;
		if (t == 1) {
			a[j] = H;
			forr(i,max(j-1, 0),min(j+1, n-1)) {
				d[i] = {abs(a[i] - a[i+1])};
				st.update(i, d[i]);
			}
		} else {

			int lo = 0, hi = n-j;
			while (hi-lo > 1) {
				int mi = (lo+hi)/2;
				int h  = st.query(j, j + mi).val;
				if (h > H) {
					hi = mi;
				} else {
					lo = mi;
				}
			}
			int casas_der = lo;

			lo = 0; hi = j+1;
			while (hi-lo > 1) {
				int mi = (lo+hi)/2;
				int h  = st.query(j - mi, j).val;
				if (h > H) {
					hi = mi;
				} else {
					lo = mi;
				}
			}
			int casas_izq = lo;

			int tot = casas_izq + 1 + casas_der;
			cout << tot << '\n';
		}
	}

	cout << flush;
}


int main(){
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

	while (cin >> n >> q) {
		solve();
	}

    
    return 0;
}
