// https://matcomgrader.com/problem/9553/looking-for-the-risk-factor/
#include<bits/stdc++.h>
using namespace std;

#define forr(i,a,b) for(int i = int(a);i<int(b);++i)
#define forn(i,n) forr(i,0,n)
#define dforr(i,a,b) for(int i=int(b)-1;i>=int(a);--i)
#define dforn(i,n) dforr(i,0,n)
#define fore(e,c) for(const auto&e : (c))
#define db(v) cerr<<#v<<" = "<<(v)<<'\n'
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

const ll MAXN = 1e5+100;
const ll INF = 1e18+100;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;
const ld PI = acosl(-1);

int criba[MAXN];

void crear_criba()
{
    forr(i, 2, MAXN) if(not criba[i]) for(ll j = 1LL*i*i; j < MAXN; j += i) criba[j] = i;
}

int max_p(int n)
{
    int ans = 0;

    while(criba[n]) ans = max(ans, criba[n]), n /= criba[n];
    if(n > 1) ans = max(ans, n);

    return ans;
}

#define oper(a, b) a+b
#define NEUT 0

struct STree
{
    vector<int> st, L, R; int n, rt;
    STree(int n): st(1, NEUT), L(1, 0), R(1, 0), n(n), rt(0){}
    int new_node(int v, int l = 0, int r = 0)
    {
        int ks=sz(st);
        st.pb(v); L.pb(l), R.pb(r);
        return ks;
    }

    int init(int s, int e, int *a)
    {
        if(s+1 == e) return new_node(a[s]);
        int m = (s+e)/2, l = init(s, m, a), r = init(m, e, a);
        return new_node(oper(st[l], st[r]), l, r);
    }

    int upd(int k, int s, int e, int p, int v)
    {
        int ks =new_node(st[k], L[k], R[k]);
        if(s+1 == e) {st[ks]= v; return ks;}
        int m = (s+e)/2, ps;
        if(p < m) ps = upd(L[ks], s, m, p, v), L[ks]=ps;
        else ps=upd(R[ks], m, e, p, v), R[ks] = ps;
        st[ks] = oper(st[L[ks]], st[R[ks]]);
        return ks;
    }

    int query(int k, int s, int e, int a, int b)
    {
        if(e <= a or b <= s) return NEUT;
        if(a <= s and e <= b) return st[k];
        int m = (s+e)/2;
        return oper(query(L[k], s, m, a, b), query(R[k], m, e, a, b));
    }

    int init(int *a) {return init(0, n, a);}
    int upd(int k, int p, int v) {return rt=upd(k, 0, n, p, v);}
    int upd(int p, int v) { return upd(rt, p, v);}
    int query(int k, int a, int b){return query(k, 0, n, a, b);}
};


STree t(MAXN);
int node[MAXN];

void solve() {
    crear_criba();

    int root;
    forn(i, MAXN) root = t.upd(i, 0);

    node[1] = root;
    forr(i, 2, MAXN)
    {
        int idx = max_p(i);
        int prev_val = t.query(node[i-1], idx, idx+1);
        node[i] = t.upd(idx, prev_val+1);
    }

    int q; cin >> q;
    forn(_, q)
    {
        int n, k; cin >> n >> k;

        cout << t.query(node[n], 0, k+1), nn;
    }
}


int main() {
	// freopen("input.txt", "r", stdin);
	// freopen("output.txt", "w", stdout);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
}
