vector<ll> BM(vector<ll>& x){    // x tiene 2n terminos de la rec lineal
	vector<ll> ls,cur; ll lf,le;  // BM devuelve los coeficientes de la rec
	forn(i, sz(x)){
		ll t = 0;
		forn(j, sz(cur)) t = (t + x[i-j-1]*cur[j]) % MOD;
		if((t-x[i])%MOD == 0) continue;
		if(cur.empty()){ cur.resize(i+1); lf=i; le=(t-x[i])%MOD; continue; }
		ll k = -(x[i]-t)*expmod(le,MOD-2)%MOD;
		vector<ll> c(i-lf-1); c.pb(k);
		forn(j, sz(ls)) c.pb(-ls[j]*k%MOD);
		if(sz(c) < sz(cur)) c.resize(sz(cur));
		forn(j, sz(cur)) c[j] = (c[j]+cur[j])%MOD;
		if(i-lf+sz(ls) >= sz(cur)) ls=cur, lf=i, le=(t-x[i])%MOD;
		cur = c;
	}
	forn(i, sz(cur)) cur[i] = (cur[i]%MOD+MOD)%MOD;
	return cur;
}