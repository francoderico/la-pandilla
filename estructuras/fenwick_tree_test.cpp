// https://codeforces.com/gym/104064/problem/E

#include <bits/stdc++.h>
using namespace std;

#define forr(i,a,b) for(int i=int(a);i<int(b);++i)
#define forn(i,n) forr(i,0,n)
#define dforr(i,a,b) for(int i=int(b)-1;i>=int(a);--i)
#define dforn(i,n) dforr(i,0,n)
#define db(v) cerr<<#v" = "<<(v)<<'\n'
#define vecp(v) cerr<<#v<<" = "; for(auto ee:v)cerr<<ee<<' '; cerr<<endl
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

const ll MAXN = 3e5+100;
const int MAXSZ = 200'000;
const ll INF = 1e18+100;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;
const ld PI = acosl(-1);


int n;
int g[MAXN], h[MAXN];
map<int, vector<int>> init_pos, end_pos;
int pos[MAXN];


struct Node
{
    int pre, nxt;
    int i;
    int stu;
};

struct Student
{
    int val;
    int i;
    int pos;
    int goal;
};

bool cmp(Student &s, Student &t)
{
    if(s.val <  t.val) return true;
    if(s.val == t.val) return s.pos < t.pos;
    return false;
}

vector<Node> node_v;
vector<Student> stu_v;
vector<pii> ans_v;

void build_queue()
{
    stack<Student> st;

    for(const auto &[x, u] : init_pos)
    {
        vector<int> &v = end_pos[x];

        forn(i, sz(u))
        {
            Student s = {x, -1, u[i], v[i]};

            if(i+1 < sz(u) and v[i] >= u[i+1])
            {
                st.push(s);
            }
            else
            {
                stu_v.pb(s);
                while(not st.empty()) stu_v.pb(st.top()), st.pop();
            }
        }

    }

    forn(i, n) node_v.pb({i-1, i+1, i, i});

    forn(i, n)
    {
        Student &s = stu_v[i];
        node_v[s.pos].stu = i;
        s.i = i;
    }

    node_v[n-1].nxt = -1;
}

void up(Student &s)
{
    Node &a = node_v[s.pos];
    assert(a.nxt != -1);
    Node &b = node_v[a.nxt];
    Student &t = stu_v[b.stu];

    ans_v.pb({a.i, b.i});

    s.pos = b.i, b.stu = s.i;
    t.pos = a.i, a.stu = t.i;
}

void down(Student &s)
{
    Node &a = node_v[s.pos];
    assert(a.pre != -1);
    Node &b = node_v[a.pre];
    Student &t = stu_v[b.stu];

    ans_v.pb({a.i, b.i});

    s.pos = b.i, b.stu = s.i;
    t.pos = a.i, a.stu = t.i;
}

void del(Student &s)
{
    Node &a = node_v[s.pos];

    if(a.pre != -1)
    {
        Node &b = node_v[a.pre];
        b.nxt = a.nxt;
    }

    if(a.nxt != -1)
    {
        Node &b = node_v[a.nxt];
        b.pre = a.pre;
    }
}

struct Fenwick
{
    int n;
    vector<int> tree;
    Fenwick(int n_) : n(n_), tree(n_+1, 0) {}

    void upd(int i, int x)  //Le sumo x al elemento en posición i
    {
        for(; i <= n; i += i & -i) tree[i] += x;
    }

    int query(int b)        //Devuelve la suma de los elementos en [1..b] (recordar que está indexado en 1).
    {
        int s = 0;
        
        for(int i = b; i; i -= i & -i) s += tree[i];
        
        return s;
    }
};


void solve()
{
    cin >> n;
    forn(i, n) cin >> g[i], init_pos[g[i]].pb(i);
    forn(i, n) cin >> h[i], end_pos[h[i]].pb(i);

    ll ans = 0;

    Fenwick kill_u(n), kill_v(n);

    for(const auto &[x, u] : init_pos)
    {
        vector<int> &v = end_pos[x];

        forn(i, sz(u)) pos[u[i]] = v[i];

        forn(i, sz(u))
        {
            ans += abs(v[i] - kill_v.query(v[i]+1) - (u[i] - kill_u.query(u[i]+1)));
            kill_u.upd(u[i]+1, 1);
            kill_v.upd(v[i]+1, 1);
        }
    }

    cout << ans, nn;

    build_queue();

    for(auto &stu : stu_v)
    {
        if(sz(ans_v) >= MAXSZ) break;

        while(node_v[stu.pos].i < stu.goal) up(stu);
        while(node_v[stu.pos].i > stu.goal) down(stu);

        del(stu);
    }

    forn(i, min(sz(ans_v), MAXSZ)) cout << ans_v[i].fst+1 << ' ' << ans_v[i].snd+1, nn;
}

int main(){
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    
    return 0;
}

