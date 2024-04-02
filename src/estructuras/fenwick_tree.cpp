struct Fenwick { // 0-indexed, query [0, i), update [i]
	int ft[MAXN+1]; // Uso: ft.u(idx, val); cout << ft.q(idx);
	int u(int i0, int x) { for (int i=i0+1; i<=MAXN; i+=i&-i) ft[i]+=x; }
	ll q(int i0){ ll x=0; for (int i=i0; i>0; i-=i&-i) x+=ft[i]; return x; }};

struct RangeFT { // 0-indexed, query [0, 1), update [l, r)
	Fenwick rate, err; // Uso: ft.u(l, r, val); cout << ft.q(l, r);
	void u(int l, int r, int x) { // range update
		rate.u(l, x); rate.u(r, -x); err.u(l, -x*l); err.u(r, x*r); }
	ll q(int i) { return rate.q(i) * i + err.q(i); } }; // prefix query
